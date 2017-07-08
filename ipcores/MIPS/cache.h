#include "systemc.h"
#include "shared.h"
#include "mem.h"

#ifndef CACHE_H_
#define CACHE_H_

// Tupla/Entrada na tabela da cache
struct fastMATH
{
	bool v;
	uint32_t tag;
	int32_t data[CACHE_WORDS];
};
typedef struct fastMATH FastMATH;

// Interface da cache
struct cache_if : public sc_interface
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
	virtual void addr_decode(uint32_t addr) = 0;
	virtual void dump_cache(uint8_t start, uint8_t end) = 0;
};

// Cache
struct cache : public sc_module, public cache_if
{
	// Interface com a memória
	sc_port <mem_if> p_mem;

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
	void addr_decode(uint32_t addr);
	void dump_cache(uint8_t start, uint8_t end);

	// Função de inicialização
	void init();

	// Construtor
	SC_CTOR(cache)
	{
		cacheFastMATH = new FastMATH[CACHE_BLOCKS];
		//SC_THREAD(init);
	}

private:
	// Ponteiro para a cache
	FastMATH *cacheFastMATH;
	// Campos de endereço
	uint32_t tag;
	uint8_t index,block_offset,byte_offset;
};

#endif
