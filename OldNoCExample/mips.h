/*
 *  mips.h
 *  MIPS
 *
 *  Created by Ricardo Jacobi on 18/04/11.
 *  Copyright 2011 Universidade de Brasilia. All rights reserved.
 *
 */

#ifndef MIPS_H
#define MIPS_H

#include "shell_mips_if.h"
//#include <iostream>
using namespace std;

SC_MODULE(mips_v0) {
	
	sc_port<shell_mips_if> pshell;
	
	sc_in<bool> reset;

/*     SC_HAS_PROCESS(Master); */
/* // constructor */
/*   Master(sc_module_name _name, unsigned int identify) : */
/*     sc_module(_name), */
/*         identify(identify) */
/*         { */
/*             SC_THREAD(test_master); */
            
/*         } */


        SC_HAS_PROCESS(mips_v0);
  mips_v0(sc_module_name _name, unsigned int identify) :
        sc_module(_name), identify(identify) 
        {
            
            SC_METHOD(run);
            
            SC_THREAD(fetch);
            SC_THREAD(decode);
            SC_THREAD(execute);
	}
	
	void init();
	void fetch();
	void decode();
	void debug_decode();
	void dump_breg();
	void execute ();
	void run();
	
private:
	sc_event e1_evt, e2_evt, e3_evt;
        unsigned int identify;
        
	int32_t breg[32];
	
	int32_t pc,	// contador de programa
            ri,		// registrador de intrucao
            hi,		// 32 bits mais significativos da multiplicacao
            lo,		// 32 bits menos significativos da multiplicacao
            kte26;	// constante instrucao tipo J
	
	int16_t kte16;	// constante instrucao tipo I

	
	//
	// campos das instrucoes MIPS
	//
	// Formato R: | opcode | rs | rt | rd | shamt | funct |
	// Formato I: | opcode | rs | rt |	kte16 - 16 bits	  |
	// Formato J: | opcode |		kte26 - 26 bits		  |
	
	uint32_t opcode,				// codigo da operacao
			rs,						// indice registrador rs
			rt,						// indice registrador rt
			rd,						// indice registrador rd
			shamt,					// deslocamento
			funct;					// campo auxiliar
};

#endif
