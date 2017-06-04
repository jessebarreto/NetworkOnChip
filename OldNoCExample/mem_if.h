/*
 *  mem_if.h
 *  MIPS_sc_v1
 *
 *  Created by Ricardo Jacobi on 20/5/16.
 *  Copyright 2016 Universidade de Brasilia. All rights reserved.
 *
 */

#ifndef MEM_IF_H
#define MEM_IF_H

#include "stdint.h"
#include "systemc.h"


struct mem_if : public sc_interface {
	
	virtual int32_t 
	read(const uint32_t address) = 0;
	
	virtual int32_t 
	  lb(const uint32_t address) = 0;
	
	virtual int32_t 
	lbu(const uint32_t address) = 0;
	
	virtual int32_t 
	  lh(const uint32_t address) = 0;

	virtual int32_t 
	lhu(const uint32_t address) = 0;
	
	virtual int32_t 
	  lw(const uint32_t address) = 0;
	
	virtual void 
	  sb(const uint32_t address, int8_t dado) = 0;
	
	virtual void 
	  sh(const uint32_t address, int16_t dado) = 0;
	
	virtual void 
	  sw(const uint32_t address, int32_t dado) = 0;
	
	virtual int 
	  load_mem(const char *fn, int start) = 0;
	
	virtual void 
	  dump_mem(int start, int end, char format) = 0;
};

#endif
