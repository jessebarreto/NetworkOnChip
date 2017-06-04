/*
 *  memoria.h
 *  MIPSc++
 *
 *  Created by Ricardo Jacobi on 18/4/15.
 *  Copyright 2015 Universidade de Brasilia. All rights reserved.
 *
 */

#ifndef MEM_H 
#define MEM_H

#include <map>
#include "systemc.h"
#include "mem_if.h"

struct mem_mips : public sc_module, public mem_if {
	
	int32_t read(uint32_t address);
	
	void check_address_range(uint32_t address);
	
	int32_t lb(const uint32_t address);
	
	int32_t lbu(const uint32_t address);

	int32_t lh(const uint32_t address);
	
	int32_t lhu(const uint32_t address);

	int32_t lw(const uint32_t address);
	
	void sb(const uint32_t address, int8_t dado);
	
	void sh(const uint32_t address, int16_t dado);
	
	void sw(const uint32_t address,int32_t dado);
	
	int load_mem(const char *fn, int start);
	
	void dump_mem(int start, int end, char format);
	
	SC_HAS_PROCESS(mem_mips);

        mem_mips (sc_module_name n, uint32_t _size, unsigned int identify) : 
        sc_module(n), _size(_size), identify(identify)
        {
		mem = new int32_t[_size];
	}
	
private:
	int32_t *mem;
	uint32_t _size;
        unsigned int identify;
        
	
};


#endif
