#include "cache.h"

// Inicialização da cache em 0
void cache::init()
{
	uint8_t aux1,aux2;

	for(aux1 = 0; aux1 < CACHE_BLOCKS; aux1++)
	{
		cacheFastMATH[aux1].v = false;
		cacheFastMATH[aux1].tag = 0;
		for(aux2 = 0; aux2 < CACHE_WORDS; aux2++)
			cacheFastMATH[aux1].data[aux2] = 0;
	}
	return;
}

// Operação de load word
int32_t cache::lw(uint32_t addr, int16_t const16)
{
	int32_t aux_addr;

	if(addr_check(addr+const16))
	{
		addr_decode(addr+const16);
		if(cacheFastMATH[index].v)
		{
			if(cacheFastMATH[index].tag == tag)
			{
				if(byte_offset == 0)
					return cacheFastMATH[index].data[block_offset];
				printf("\nCache Error: word address %d|0x%.8x is not aligned.\n", addr+const16, (addr+const16)/* & 0xFFFFFFFF*/);
				sc_stop();
			}
			for(aux_addr = 0; aux_addr < CACHE_WORDS*4; aux_addr += 4)
				p_mem->sw((((tag<<14) & 0xFFFFC000) | ((addr+const16) & 0x3FC0)),aux_addr,cacheFastMATH[index].data[aux_addr/4]);
		}
		for(aux_addr = 0; aux_addr < CACHE_WORDS*4; aux_addr += 4)
			cacheFastMATH[index].data[aux_addr/4] = p_mem->lw((addr+const16) & 0xFFFFFFC0,aux_addr);
		cacheFastMATH[index].v = true;
		if(byte_offset == 0)
			return cacheFastMATH[index].data[block_offset];
		printf("\nCache Error: word address %d|0x%.8x is not aligned.\n", addr+const16, (addr+const16)/* & 0xFFFFFFFF*/);
	}
	sc_stop();

	return 0;
}

// Operação de load half
int32_t cache::lh(uint32_t addr, int16_t const16)
{
	int32_t aux32;
	int32_t aux_addr;

	if(addr_check(addr+const16))
	{
		aux32 = cacheFastMATH[index].data[block_offset];
		aux32 = (aux32>>8*(((addr+const16)%4)&2));
		addr_decode(addr+const16);
		if(cacheFastMATH[index].v)
		{
			if(cacheFastMATH[index].tag == tag)
			{
				if(byte_offset == 0 || byte_offset == 2)
					return (int16_t)aux32;
				printf("\nCache Error: half address %d|0x%.8x is not aligned.\n", addr+const16, (addr+const16)/* & 0xFFFFFFFF*/);
				sc_stop();
			}
			for(aux_addr = 0; aux_addr < CACHE_WORDS*4; aux_addr += 4)
				p_mem->sw((((tag<<14) & 0xFFFFC000) | ((addr+const16) & 0x3FC0)),aux_addr,cacheFastMATH[index].data[aux_addr/4]);
		}
		for(aux_addr = 0; aux_addr < CACHE_WORDS*4; aux_addr += 4)
			cacheFastMATH[index].data[aux_addr/4] = p_mem->lw((addr+const16) & 0xFFFFFFC0,aux_addr);
		cacheFastMATH[index].v = true;
		if(byte_offset == 0 || byte_offset == 2)
			return (int16_t)aux32;
		printf("\nCache Error: half address %d|0x%.8x is not aligned.\n", addr+const16, (addr+const16)/* & 0xFFFFFFFF*/);
	}
	sc_stop();

	return 0;
}

// Operação de load byte
int32_t cache::lb(uint32_t addr, int16_t const16)
{
	int32_t aux32;
	int32_t aux_addr;

	if(addr_check(addr+const16))
	{
		aux32 = cacheFastMATH[index].data[block_offset];
		addr_decode(addr+const16);
		if(cacheFastMATH[index].v)
		{
			if(cacheFastMATH[index].tag == tag)
				return (int8_t)((aux32>>8*((addr+const16)%4)&0xFF));
			for(aux_addr = 0; aux_addr < CACHE_WORDS*4; aux_addr += 4)
				p_mem->sw((((tag<<14) & 0xFFFFC000) | ((addr+const16) & 0x3FC0)),aux_addr,cacheFastMATH[index].data[aux_addr/4]);
		}
		for(aux_addr = 0; aux_addr < CACHE_WORDS*4; aux_addr += 4)
			cacheFastMATH[index].data[aux_addr/4] = p_mem->lw((addr+const16) & 0xFFFFFFC0,aux_addr);
		cacheFastMATH[index].v = true;
		return (int8_t)((aux32>>8*((addr+const16)%4)&0xFF));
	}
	sc_stop();

	return 0;
}

// Operação de load half unsigned
int32_t cache::lhu(uint32_t addr, int16_t const16)
{
	int32_t aux32;
	int32_t aux_addr;

	if(addr_check(addr+const16))
	{
		aux32 = cacheFastMATH[index].data[block_offset];
		aux32 = (aux32>>8*(((addr+const16)%4)&2));
		addr_decode(addr+const16);
		if(cacheFastMATH[index].v)
		{
			if(cacheFastMATH[index].tag == tag)
			{
				if(byte_offset == 0 || byte_offset == 2)
					return (aux32 & 0xFFFF);
				printf("\nCache Error: half address %d|0x%.8x is not aligned.\n", addr+const16, (addr+const16)/* & 0xFFFFFFFF*/);
				sc_stop();
			}
			for(aux_addr = 0; aux_addr < CACHE_WORDS*4; aux_addr += 4)
				p_mem->sw((((tag<<14) & 0xFFFFC000) | ((addr+const16) & 0x3FC0)),aux_addr,cacheFastMATH[index].data[aux_addr/4]);
		}
		for(aux_addr = 0; aux_addr < CACHE_WORDS*4; aux_addr += 4)
			cacheFastMATH[index].data[aux_addr/4] = p_mem->lw((addr+const16) & 0xFFFFFFC0,aux_addr);
		cacheFastMATH[index].v = true;
		if(byte_offset == 0 || byte_offset == 2)
			return (aux32 & 0xFFFF);
		printf("\nCache Error: half address %d|0x%.8x is not aligned.\n", addr+const16, (addr+const16)/* & 0xFFFFFFFF*/);
	}
	sc_stop();

	return 0;
}

// Operação de load byte unsigned
int32_t cache::lbu(uint32_t addr, int16_t const16)
{
	int32_t aux32;
	int32_t aux_addr;

	if(addr_check(addr+const16))
	{
		aux32 = cacheFastMATH[index].data[block_offset];
		addr_decode(addr+const16);
		if(cacheFastMATH[index].v)
		{
			if(cacheFastMATH[index].tag == tag)
				return ((aux32>>8*((addr+const16)%4)&0xFF));
			for(aux_addr = 0; aux_addr < CACHE_WORDS*4; aux_addr += 4)
				p_mem->sw((((tag<<14) & 0xFFFFC000) | ((addr+const16) & 0x3FC0)),aux_addr,cacheFastMATH[index].data[aux_addr/4]);
		}
		for(aux_addr = 0; aux_addr < CACHE_WORDS*4; aux_addr += 4)
			cacheFastMATH[index].data[aux_addr/4] = p_mem->lw((addr+const16) & 0xFFFFFFC0,aux_addr);
		cacheFastMATH[index].v = true;
		return ((aux32>>8*((addr+const16)%4)&0xFF));
	}
	sc_stop();

	return 0;
}

// Operação de store word
void cache::sw(uint32_t addr, int16_t const16, int32_t data)
{
	int32_t aux_addr;

	if(addr_check(addr+const16))
	{
		addr_decode(addr+const16);
		if(cacheFastMATH[index].v)
		{
			if(cacheFastMATH[index].tag == tag)
			{
				if(byte_offset == 0)
				{
					cacheFastMATH[index].data[block_offset] = data;
					return;
				}
				printf("\nCache Error: word address %d|0x%.8x is not aligned.\n", addr+const16, (addr+const16)/* & 0xFFFFFFFF*/);
				sc_stop();
			}
			for(aux_addr = 0; aux_addr < CACHE_WORDS*4; aux_addr += 4)
				p_mem->sw((((tag<<14) & 0xFFFFC000) | ((addr+const16) & 0x3FC0)),aux_addr,cacheFastMATH[index].data[aux_addr/4]);
		}
		for(aux_addr = 0; aux_addr < CACHE_WORDS*4; aux_addr += 4)
			cacheFastMATH[index].data[aux_addr/4] = p_mem->lw((addr+const16) & 0xFFFFFFC0,aux_addr);
		cacheFastMATH[index].v = true;
		if(byte_offset == 0)
		{
			cacheFastMATH[index].data[block_offset] = data;
			return;
		}
		printf("\nCache Error: word address %d|0x%.8x is not aligned.\n", addr+const16, (addr+const16)/* & 0xFFFFFFFF*/);
	}
	sc_stop();

	return;
}

// Operação de store half
void cache::sh(uint32_t addr, int16_t const16, int16_t data)
{
	uint16_t *p_uaux16;
	int32_t aux_addr;

	if(addr_check(addr+const16))
	{
		p_uaux16 = (uint16_t *)&cacheFastMATH[index].data[block_offset];
		if((addr+const16)&2)
			p_uaux16++;
		addr_decode(addr+const16);
		if(cacheFastMATH[index].v)
		{
			if(cacheFastMATH[index].tag == tag)
			{
				if(byte_offset == 0 || byte_offset == 2)
				{
					*p_uaux16 = (uint16_t)data;
					return;
				}
				printf("\nCache Error: half address %d|0x%.8x is not aligned.\n", addr+const16, (addr+const16)/* & 0xFFFFFFFF*/);
				sc_stop();
			}
			for(aux_addr = 0; aux_addr < CACHE_WORDS*4; aux_addr += 4)
				p_mem->sw((((tag<<14) & 0xFFFFC000) | ((addr+const16) & 0x3FC0)),aux_addr,cacheFastMATH[index].data[aux_addr/4]);
		}
		for(aux_addr = 0; aux_addr < CACHE_WORDS*4; aux_addr += 4)
			cacheFastMATH[index].data[aux_addr/4] = p_mem->lw((addr+const16) & 0xFFFFFFC0,aux_addr);
		cacheFastMATH[index].v = true;
		if(byte_offset == 0 || byte_offset == 2)
		{
			*p_uaux16 = (uint16_t)data;
			return;
		}
		printf("\nCache Error: half address %d|0x%.8x is not aligned.\n", addr+const16, (addr+const16)/* & 0xFFFFFFFF*/);
		sc_stop();
	}
	sc_stop();

	return;
}

// Operação de store byte
void cache::sb(uint32_t addr, int16_t const16, int8_t data)
{
	uint8_t *p_uaux8;
	int32_t aux_addr;

	if(addr_check(addr+const16))
	{
		p_uaux8 = (uint8_t *)&cacheFastMATH[index].data[block_offset];
		p_uaux8 += ((addr+const16)%4);
		addr_decode(addr+const16);
		if(cacheFastMATH[index].v)
		{
			if(cacheFastMATH[index].tag == tag)
			{
				*p_uaux8 = (uint8_t)data;
				return;
			}
			for(aux_addr = 0; aux_addr < CACHE_WORDS*4; aux_addr += 4)
				p_mem->sw((((tag<<14) & 0xFFFFC000) | ((addr+const16) & 0x3FC0)),aux_addr,cacheFastMATH[index].data[aux_addr/4]);
		}
		for(aux_addr = 0; aux_addr < CACHE_WORDS*4; aux_addr += 4)
			cacheFastMATH[index].data[aux_addr/4] = p_mem->lw((addr+const16) & 0xFFFFFFC0,aux_addr);
		cacheFastMATH[index].v = true;
		*p_uaux8 = (uint8_t)data;
		return;
	}
	sc_stop();

	return;
}

// Verificação de endereço dentro dos limites de memória
bool cache::addr_check(uint32_t addr)
{
	if((addr>>2) > MEM_WORD_SIZE)
	{
		printf("\nCache Error: address %d|0x%.8x out of memory boundaries.\n",addr,addr/* & 0xFFFFFFFF*/);
		return false;
	}
	else
		return true;
}

// Decodificação do endereço
void cache::addr_decode(uint32_t addr)
{
	tag = (int32_t)(addr >> 14) & 0x3FFFF;
	index = (int8_t)(addr >> 6) & 0xFF;
	block_offset = (int8_t)(addr >> 2) & 0xF;
	byte_offset = (int8_t)addr & 0x3;
}

// Impressão de segmento da memória
void cache::dump_cache(uint8_t start, uint8_t end)
{
	uint16_t aux1,aux2;

	printf("\ncache:\n");
	for(aux1 = start; aux1 <= end; aux1++)
	{
		printf("\tcacheFastMATH[%d|0x%.2x]: .v = %d | .tag = %d = 0x%.5X\n", aux1, aux1/* & 0xFF*/, cacheFastMATH[aux1].v, cacheFastMATH[aux1].tag, cacheFastMATH[aux1].tag/* & 0xFFFFF*/);
		for(aux2 = 0; aux2 < CACHE_WORDS; aux2++)
			printf("\t\t.data[%d|0x%.1X] = %d = 0x%.8X\n", aux2, aux2/* & 0xF*/, cacheFastMATH[aux1].data[aux2], cacheFastMATH[aux1].data[aux2]);
	}
	return;
}
