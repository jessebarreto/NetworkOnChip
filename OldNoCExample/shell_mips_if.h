/*
 *  shell_mips_if.h
 *  MIPS_sc_v1
 *
 *  Created by Ricardo Jacobi on 20/5/16.
 *  Copyright 2016 Universidade de Brasilia. All rights reserved.
 *
 */

#ifndef SHELL_MIPS_IF_H
#define SHELL_MIPS_IF_H

#include "stdint.h"
#include "systemc.h"

struct shell_mips_if : public sc_interface {
		
	virtual void
            check_destiny(uint32_t word, uint32_t destiny) = 0;

	virtual int32_t 
            lb(const uint32_t address, uint16_t kte) = 0;
	
	virtual int32_t 
            lbu(const uint32_t address, uint16_t kte) = 0;
	
	virtual int32_t 
            lh(const uint32_t address, uint16_t kte) = 0;

	virtual int32_t 
            lhu(const uint32_t address, uint16_t kte) = 0;
	
	virtual int32_t 
            lw(const uint32_t address, uint16_t kte) = 0;

            /* virtual int32_t  */
            /*   instruction_lw(const uint32_t address, uint16_t kte) = 0; */
	
	virtual void 
            sb(const uint32_t address, uint16_t kte, int8_t dado) = 0;
	
	virtual void 
            sh(const uint32_t address, uint16_t kte, int16_t dado) = 0;
	
	virtual void 
            sw(const uint32_t address, uint16_t kte, int32_t dado) = 0;
	
};

#endif
