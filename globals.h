//
//  globals.h
//  MIPSc++
//
//  Created by Ricardo Jacobi on 18/4/15.
//
//

#ifndef MIPSc___globals_h
#define MIPSc___globals_h

enum CONSTANTS {
	INT_MEM_SIZE = 0x4000,
	DATA_SEGMENT_START = 0x2000
};

#define get_byte_0(w) (w & 0xFF)
#define get_byte_1(w) ((w>>8) & 0xFF)
#define get_byte_2(w) ((w>>16) & 0xFF)
#define get_byte_3(w) ((w>>24) & 0xFF)

#define build_Hflit(orig, dest, cmd, size) (((orig << 24) & 0xFF000000) | ((dest << 16) & 0xFF0000) | ((cmd << 10) & 0xFC00) | (size & 0x3FF))
#define get_orig(flit) ((flit >> 24) & 0xFF)
#define get_dest(flit) ((flit >> 16) & 0xFF)
#define get_cmd(flit) ((flit >> 10) & 0x3F)
#define get_size(flit) (flit & 0x3FF)

//
// definicao dos valores das posiçoes da noc 
//

enum NOC {
	P = 4,	M0 = 3,
	DMA = 5,	R_A = 0,
	M1 = 1,	DSPL = 2 
};

//
// definicao dos valores do campo de extensao
//
enum FUNCT { 
	ADD=0x20,		ADDU=0x21, 
	SUB=0x22,		MULT=0x18, 
	DIV=0x1A,		AND=0x24, 
	OR=0x25,		XOR=0x26, 
	NOR=0x27,		SLT=0x2A, 
	JR=0x08,		SLL=0x00, 
	SRL=0x02,		SRA=0x03,
	SYSCALL=0x0c,	DBREG=1024,
	MFHI=0x10,		MFLO=0x12
};


//
// definicao dos valores do campo de codigo da operacao do MIPS
//
enum OPCODES {	
	FUN=0x00,	LW=0x23, 
	LB=0x20,	LH=0x21, 
	LBU=0x24,
	LHU=0x25,	LUI=0x0F,
	SW=0x2B,	SB=0x28, 
	SH=0x29,	BEQ=0x04, 
	BNE=0x05,	BLEZ=0x06, 
	BGTZ=0x07,	ADDI=0x08, 
	ADDIU=0x09, SLTI=0x0A, 
	SLTIU=0x0B, ANDI=0x0C, 
	ORI=0x0D,	XORI=0x0E, 
	J=0x02,		JAL=0x03
};

//
// identificacao dos registradores do banco do MIPS
//
enum REGISTERS {
	ZERO=0, AT=1,	V0=2,	V1=3, 
	A0=4,	A1=5,	A2=6,	A3=7, 
	T0=8,	T1=9,	T2=10,	T3=11, 
	T4=12,	T5=13,	T6=14,	T7=15, 
	T8=24,	T9=25,	S0=16,	S1=17, 
	S2=18,	S3=19,	S4=20,	S5=21, 
	S6=22,	S7=23,	K0=26,	K1=27, 
	GP=28,	SP=29,	FP=30,	RA=31 
};

//
// Identificacao de tipo de dado
//
enum DATA_TYPE {
	BYTE=4, INTEGER=1
};

#endif
