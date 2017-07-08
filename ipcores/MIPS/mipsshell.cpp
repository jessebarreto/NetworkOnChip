#include "mipsshell.h"

#include <vector>

#include NOC_MEMORY_POSITION 1

// Inicialização da memória em 0
void mem::init()
{
	for(uint32_t aux = 0; aux < MEM_WORD_SIZE; memory[aux++] = 0);
	return;
}

// Operação de load word
int32_t mem::lw(uint32_t addr, int16_t const16)
{
	if(addr_check(addr+const16))
	{
        if((addr+const16)%4 == 0) {
			//return memory[(addr+const16)>>2];
            // Sending Load Command to Memory
            std::vector<uint32_t> payload;
            payload.push_back(0);
            payload.push_back(addr + const16);
            payload.push_back(1);
            int payloadDst = NOC_MEMORY_POSITION;
            sendPayload(payload, payloadDst);
            payload.clear();
            
            // Reading Load Command from Memory
            int payloadSrc;
            receivePayload(payload, &payloadSrc);
            if (payload.size() == 2 && payload.at(0) == 1) {
                return static_cast<int32_t>(payload.at(1));
            } else {
                return 0;
            }
        }
		printf("\nMemory Error: word address %d|0x%.8x is not aligned.\n", addr+const16, (addr+const16)/* & 0xFFFFFFFF*/);
		sc_stop();
	}
	sc_stop();

	return 0;
}

// Operação de load half
int32_t mem::lh(uint32_t addr, int16_t const16)
{
	int32_t aux32;

    if(addr_check(addr+const16))
	{
    	if((addr+const16)%2 == 0)
    	{
            // Sending Load Command to Memory
            std::vector<uint32_t> payload;
            payload.push_back(0);
            payload.push_back(addr + const16);
            payload.push_back(1);
            int payloadDst = NOC_MEMORY_POSITION;
            sendPayload(payload, payloadDst);
            payload.clear();
            
            // Reading Load Command from Memory
            int payloadSrc;
            receivePayload(payload, &payloadSrc);
            if (payload.size() == 2 && payload.at(0) == 1) {
                return static_cast<int32_t>(payload.at(1));
            } else {
                return 0;
            }
			aux32 = memory[(addr+const16)>>2];
			aux32 = (aux32>>8*(((addr+const16)%4)&2));
			return (int16_t)aux32;
    	}
    	printf("\nMemory Error: half address %d|0x%.8x is not aligned.\n", addr+const16, (addr+const16)/* & 0xFFFFFFFF*/);
    	sc_stop();
	}
    sc_stop();

    return 0;
}

// Operação de load byte
int32_t mem::lb(uint32_t addr, int16_t const16)
{
	int32_t aux32;

    if(addr_check(addr + const16))
   	{
        // Sending Load Command to Memory
        std::vector<uint32_t> payload;
        payload.push_back(0);
        payload.push_back(addr + const16);
        payload.push_back(1);
        int payloadDst = NOC_MEMORY_POSITION;
        sendPayload(payload, payloadDst);
        payload.clear();
        
        // Reading Load Command from Memory
        int payloadSrc;
        receivePayload(payload, &payloadSrc);
        if (payload.size() == 2 && payload.at(0) == 1) {
            return static_cast<int32_t>(payload.at(1));
        } else {
            return 0;
        }
    	aux32 = memory[(addr+const16)>>2];
		return (int8_t)((aux32>>8*((addr+const16)%4)&0xFF));
   	}
    sc_stop();

    return 0;
}

// Operação de load half unsigned
int32_t mem::lhu(uint32_t addr, int16_t const16)
{
	int32_t aux32;

    if(addr_check(addr+const16))
	{
    	if((addr+const16)%2 == 0)
    	{
            // Sending Load Command to Memory
            std::vector<uint32_t> payload;
            payload.push_back(0);
            payload.push_back(addr + const16);
            payload.push_back(1);
            int payloadDst = NOC_MEMORY_POSITION;
            sendPayload(payload, payloadDst);
            payload.clear();
            
            // Reading Load Command from Memory
            int payloadSrc;
            receivePayload(payload, &payloadSrc);
            if (payload.size() == 2 && payload.at(0) == 1) {
                return static_cast<int32_t>(payload.at(1));
            } else {
                return 0;
            }
			aux32 = memory[(addr+const16)>>2];
			aux32 = (aux32>>8*((addr+const16)%4)&2);
			return (aux32 & 0xFFFF);
    	}
    	printf("\nMemory Error: half address %d|0x%.8x is not aligned.\n", addr+const16, (addr+const16)/* & 0xFFFFFFFF*/);
    	sc_stop();
	}
    sc_stop();

    return 0;
}

// Operação de load byte unsigned
int32_t mem::lbu(uint32_t addr, int16_t const16)
{
	int32_t aux32;

    if(addr_check(addr+const16))
   	{
        // Sending Load Command to Memory
        std::vector<uint32_t> payload;
        payload.push_back(0);
        payload.push_back(addr + const16);
        payload.push_back(1);
        int payloadDst = NOC_MEMORY_POSITION;
        sendPayload(payload, payloadDst);
        payload.clear();
        
        // Reading Load Command from Memory
        int payloadSrc;
        receivePayload(payload, &payloadSrc);
        if (payload.size() == 2 && payload.at(0) == 1) {
            return static_cast<int32_t>(payload.at(1));
        } else {
            return 0;
        }
    	aux32 = memory[(addr+const16)>>2];
		return ((aux32>>8*((addr+const16)%4))&0xFF);
   	}
    sc_stop();

    return 0;
}

// Operação de store word
void mem::sw(uint32_t addr, int16_t const16, int32_t data)
{
	if(addr_check(addr+const16))
	{
		if((addr+const16)%4 == 0)
		{
            // Sending Load Command to Memory
            std::vector<uint32_t> payload;
            payload.push_back(1);
            payload.push_back(addr + const16);
            payload.push_back(1);
            payload.push_back(data);
            int payloadDst = NOC_MEMORY_POSITION;
            sendPayload(payload, payloadDst);
            payload.clear();
            
            // Reading Load Command from Memory
            int payloadSrc;
            receivePayload(payload, &payloadSrc);
            if (payload.size() == 2 && payload.at(0) == 1) {
                return static_cast<int32_t>(payload.at(1));
            } else {
                return 0;
            }
		    //memory[(addr+const16)>>2] = data;
		    //return;
		}
		printf("\nMemory Error: word address %d|0x%.8x is not aligned.\n", addr+const16, (addr+const16)/* & 0xFFFFFFFF*/);
		sc_stop();
	}
	sc_stop();

	return;
}

// Operação de store half
void mem::sh(uint32_t addr, int16_t const16, int16_t data)
{
	uint16_t *p_uaux16;

	if(addr_check(addr+const16))
	{
		if((addr+const16)%2 == 0)
		{
			p_uaux16 = (uint16_t *)&memory[(addr+const16)>>2];
			if((addr+const16)&2)
            // Sending Load Command to Memory
            std::vector<uint32_t> payload;
            payload.push_back(1);
            payload.push_back(addr + const16);
            payload.push_back(1);
            payload.push_back(static_cast<uint32_t>data);
            int payloadDst = NOC_MEMORY_POSITION;
            sendPayload(payload, payloadDst);
            payload.clear();
            
            // Reading Load Command from Memory
            int payloadSrc;
            receivePayload(payload, &payloadSrc);
            if (payload.size() == 2 && payload.at(0) == 1) {
                return static_cast<int32_t>(payload.at(1));
            } else {
                return 0;
            }
            //p_uaux16++;
            //*p_uaux16 = (uint16_t)data;
			//return;
		}
		printf("\nMemory Error: half address %d|0x%.8x is not aligned.\n", addr+const16, (addr+const16)/* & 0xFFFFFFFF*/);
		sc_stop();
	}
	sc_stop();

	return;
}

// Operação de store byte
void mem::sb(uint32_t addr, int16_t const16, int8_t data)
{
	uint8_t *p_uaux8 = NULL;

    if(addr_check(addr+const16))
   	{
        // Sending Load Command to Memory
        std::vector<uint32_t> payload;
        payload.push_back(1);
        payload.push_back(addr + const16);
        payload.push_back(1);
        payload.push_back(static_cast<uint32_t>data);
        int payloadDst = NOC_MEMORY_POSITION;
        sendPayload(payload, payloadDst);
        payload.clear();
        
        // Reading Load Command from Memory
        int payloadSrc;
        receivePayload(payload, &payloadSrc);
        if (payload.size() == 2 && payload.at(0) == 1) {
            return static_cast<int32_t>(payload.at(1));
        } else {
            return 0;
        }
    	//p_uaux8 = (uint8_t *)&memory[(addr+const16)>>2];
    	//p_uaux8 += ((addr+const16)%4);
    	//*p_uaux8 = (uint8_t)data;
    	//return;
   	}
    sc_stop();

    return;
}

// Verificação de endereço dentro dos limites de memória
bool mem::addr_check(uint32_t addr)
{
	if((addr>>2) > MEM_WORD_SIZE)
	{
		printf("\nMemory Error: address %d|0x%.8x out of memory boundaries.\n",addr,addr/* & 0xFFFFFFFF*/);
		return false;
	}
	else
		return true;
}

// Impressão de segmento da memória
void mem::dump_mem(uint32_t start, uint32_t end)
{
	printf("\nmem:\n");
	for(uint64_t aux = start/4; aux <= end/4; aux++)
		printf("\tmemory[%d|0x%.8X] = %d = 0x%.8X\n", 4*aux, 4*aux/* & 0xFFFFFFFF*/, lw(4*aux,0), lw(4*aux,0)/* & 0xFFFFFFFF*/);
	return;
}
