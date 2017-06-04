/*
 *  mips.cpp
 *  MIPSc++
 *
 *  Created by Ricardo Jacobi on 18/4/15.
 *  Copyright 2015 Universidade de Brasilia. All rights reserved.
 *
 */
#include <iostream>
#include "globals.h"
#include "noc_common.h"
#include "shell_mips.h"
#include "mips.h"


void mips_v0::init() {

    pc = ri = hi = lo = 0;
    for (int i=0; i<32; breg[i++]=0);

}

// busca instrucao na memoria e escreve no registrador de instrucoes ri
void mips_v0::fetch () {
    while (pc<DATA_SEGMENT_START){
        wait (e1_evt);
        if ( debug >=0 ) cout<<"in fetch"<<endl;
        ri = pshell->lw(pc, 0);   // mem[PC >> 2]
        pc = pc + 4;
        e2_evt.notify();
    }
}

void mips_v0::decode () {
    while (pc<DATA_SEGMENT_START){
        wait (e2_evt);
        if ( debug >=0 ) printf("in decode");
        opcode	= (ri >> 26) & 0x3F;
        rs	= (ri >> 21) & 0x1F;
        rt	= (ri >> 16) & 0x1F;
        rd	= (ri >> 11) & 0x1F;
        shamt	= (ri >> 6) & 0x1F;
        funct	= ri & 0x3F;
        kte16	= ri & 0xFFFF;
        kte26	= ri & 0x03FFFFFF;
        e3_evt.notify();
    }
	//if (pc < 10)
    debug_decode();
}


void mips_v0::debug_decode() {
    printf("in debug_decode: ");
    if ( debug >=0 ) cout << "PC = " << dec << pc << endl;
    if ( debug >=0 ) cout << "opcode = 0x"	<< hex << opcode	<<	
                         " rs = 0x"		<< hex << rs		<<
                         " rt = 0x"		<< hex << rt		<<
                         " rd = 0x"		<< hex << rd		<<
                         " shamt = 0x"	<< hex << shamt		<<
                         " funct = 0x"	<< hex << funct		<<endl;
}

void mips_v0::dump_breg() {
    for (int i=0; i<32; i++) {
        printf("BREG[%2d] = \t%+.8d \t\t\t%.8X\n", i, breg[i], breg[i]);
    }
}

void mips_v0::execute () {
    while (pc<DATA_SEGMENT_START){
        wait (e3_evt);
        if ( debug >=0 ) printf("in execute");

        int64_t u;
        int32_t c, aux;
	
        breg[0] = 0;

        switch (opcode) {
            case FUN:
                switch (funct) {
                    case SYSCALL: // emula as chamadas do MARS
                        switch (breg[V0]) {
                            case 1:	cout << breg[A0]; break;
                            case 2:                   break;
                            case 3:				      break;
                            case 4:	
                                for (aux = 0; (c = pshell->lb(breg[A0],aux)) != 0; aux++)
                                    if ( debug >=0 ) { cout << c;
                                        cout << endl; 
                                    }
                                                            
                                break;
                            case 5:	cin >> breg[V0]; break;
                            case 6:                  break;
                            case 10: 
                                if ( debug >=0 ) cout << "\n\n Encerrou programa com syscall exit! \n";
                                sc_stop();
                                break;
                            case DBREG:
                                dump_breg();
                                break;
                            default:break;
                        }
                    case SLL:  breg[rd] = breg[rt] << shamt;			break;
                    case SRL:  breg[rd] = (uint32_t)breg[rt] >> shamt;	break;
                    case SRA:  breg[rd] = breg[rt] >> shamt;			break;
                    case JR:   pc = breg[rs];							break;
                    case MULT:	
                        u = (int64_t)breg[rs]*breg[rt];
                        hi = (u >> 32); 
                        lo = (int32_t)u;
                        break;
                    case DIV:  
                        lo = breg[rs]/breg[rt]; 
                        hi = breg[rs]%breg[rt]; 
                        break;
                    case ADD:  breg[rd] = breg[rs] + breg[rt];        break;
                    case ADDU: breg[rd] = breg[rs] + breg[rt];        break;
                    case SUB:  breg[rd] = breg[rs] - breg[rt];        break;
                    case AND:  breg[rd] = breg[rs] & breg[rt];        break;
                    case OR:   breg[rd] = breg[rs] | breg[rt];        break;
                    case XOR:  breg[rd] = breg[rs] ^ breg[rt];        break;
                    case NOR:  breg[rd] = ~(breg[rs] | breg[rt]);     break;
                    case SLT:  breg[rd] = breg[rs] < breg[rt];        break;
                    case MFHI: breg[rd] = hi;						  break;
                    case MFLO: breg[rd] = lo;						  break;
                    default: printf("Instrucao Invalida (*0x%x~0x%x)\n", pc, ri); break;
                }
                break;
            case JAL:   breg[RA] = pc;								
                pc = (pc & 0xf0000000) | (kte26<<2);
                break;
			
            case J:     pc = (pc & 0xf0000000) | (kte26<<2);		break;
			
            case BEQ:   if (breg[rs] == breg[rt])
                    pc += (kte16 << 2);     
                break;
            case BNE:   if (breg[rs] != breg[rt])
                    pc += (kte16 << 2);     
                break;
            case BLEZ:  if (breg[rs] <= 0)
                    pc += (kte16 << 2);     
                break;
            case BGTZ:  if (breg[rs] > 0)
                    pc += (kte16 << 2);     
                break;
            case ADDI:	breg[rt] = breg[rs] + kte16;								break;
            case ADDIU:	breg[rt] = (uint32_t)breg[rs] + kte16;						break;
            case SLTI:	breg[rt] = breg[rs] < kte16;								break;
            case SLTIU:	breg[rt] = (uint32_t)breg[rs] < (uint32_t)kte16;			break;
            case ANDI:	breg[rt] = breg[rs] & (uint32_t)kte16;						break;
            case ORI:	breg[rt] = breg[rs] | (uint32_t)kte16;						break;
            case XORI:	breg[rt] = breg[rs] ^ (uint32_t)kte16;						break;
            case LUI:	breg[rt] = (kte16 << 16);									break;
            case LB:	breg[rt] = pshell->lb(breg[rs], kte16);						break;
            case LBU:	breg[rt] = pshell->lbu(breg[rs], kte16);					break;
            case LH:	breg[rt] = pshell->lh(breg[rs],kte16);						break;
            case LW:	breg[rt] = pshell->lw(breg[rs], kte16);						break;
            case LHU:	breg[rt] = pshell->lhu(breg[rs], kte16);					break;
            case SB:	pshell->sb(breg[rs], kte16, get_byte_0(breg[rt]));			break;
            case SH:	pshell->sh(breg[rs], kte16, (uint16_t)(breg[rt]&0xFFFF));	break;
            case SW:	pshell->sw(breg[rs], kte16, breg[rt]);						break;
            default:	break;
        }
        e1_evt.notify();
    }
}


void mips_v0::run() {

	init();

	e1_evt.notify(SC_ZERO_TIME);
}
