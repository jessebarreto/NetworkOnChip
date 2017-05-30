/*
 *  mips_shell.h
 *  MIPSc++
 *
 *  Created by Ricardo Jacobi on 18/4/15.
 *  Copyright 2015 Universidade de Brasilia. All rights reserved.
 *
 */

#ifndef SHELL_MIPS_H 
#define SHELL_MIPS_H


#include "systemc.h"
#include "shell_mips_if.h"

struct shellmi_mips : public sc_module, public shell_mips_if {
	
    sc_fifo_in<sc_uint<32>> in;
    sc_fifo_out<sc_uint<32>> out;
	
    void check_destiny(uint32_t word, uint32_t destiny);

    int32_t lb(const uint32_t address, uint16_t kte);
	
    int32_t lbu(const uint32_t address, uint16_t kte);

    int32_t lh(const uint32_t address, uint16_t kte);
	
    int32_t lhu(const uint32_t address, uint16_t kte);

    int32_t lw(const uint32_t address, uint16_t kte);
        // int32_t instruction_lw(const uint32_t address, uint16_t kte);
	
    void sb(const uint32_t address, uint16_t kte, int8_t dado);
	
    void sh(const uint32_t address, uint16_t kte, int16_t dado);
	
    void sw(const uint32_t address, uint16_t kte, int32_t dado);
		
	//SC_HAS_PROCESS(shellmi_mips);
	//
	//shellmi_mips (sc_module_name n) : 
	//	sc_module(n) {
	//	
	//}

    /* SC_CTOR(shellmi_mips){ */
    /* } */

    SC_HAS_PROCESS( shellmi_mips );
    shellmi_mips (
        sc_module_name _name,
        unsigned int identify
                          ):
    sc_module(_name), identify(identify) 
    {

    }
  private:
    unsigned int identify;

    
};

#endif
