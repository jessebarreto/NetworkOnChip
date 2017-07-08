#include "systemc.h"
#include "shared.h"

#include "networkinterfacefrontendbase.h"

#ifndef MIPSSHELL_H_
#define MIPSSHELL_H_

// Interface da memória
struct mem_if : public sc_interface
{
	virtual int32_t lw(uint32_t addr, int16_t const16) = 0;
	virtual int32_t lh(uint32_t addr, int16_t const16) = 0;
	virtual int32_t lb(uint32_t addr, int16_t const16) = 0;
	virtual int32_t lhu(uint32_t addr, int16_t const16) = 0;
	virtual int32_t lbu(uint32_t addr, int16_t const16) = 0;
	virtual void sw(uint32_t addr, int16_t const16, int32_t data) = 0;
	virtual void sh(uint32_t addr, int16_t const16, int16_t data) = 0;
	virtual void sb(uint32_t addr, int16_t const16, int8_t data) = 0;
	virtual bool addr_check(uint32_t addr) = 0;
	virtual void dump_mem(uint32_t start, uint32_t end) = 0;
};

// Memória
struct mem : public sc_module, public mem_if, public networkinterfacefrontendbase
{
	// Funções de interface
	int32_t lw(uint32_t addr, int16_t const16);
	int32_t lh(uint32_t addr, int16_t const16);
	int32_t lb(uint32_t addr, int16_t const16);
	int32_t lhu(uint32_t addr, int16_t const16);		
	int32_t lbu(uint32_t addr, int16_t const16);
	void sw(uint32_t addr, int16_t const16, int32_t data);
	void sh(uint32_t addr, int16_t const16, int16_t data);
	void sb(uint32_t addr, int16_t const16, int8_t data);
	bool addr_check(uint32_t addr);
	void dump_mem(uint32_t start, uint32_t end);
	// Construtor
	SC_CTOR(mem)
	{
		memory = new int32_t[MEM_WORD_SIZE];
		//SC_THREAD(init);
	}

private:
	int32_t *memory;
};

#endif
