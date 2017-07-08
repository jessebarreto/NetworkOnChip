#include "breg.h"

// Inicialização dos resgistradores em 0
void breg::init()
{
	for(uint8_t aux = 0; aux < 32; registers[aux++] = 0);
	return;
}

// Leitura do banco de registradores
int32_t breg::read(uint8_t addr)
{
	return registers[addr];
}

// Escrita no banco de registradores
void breg::write(uint8_t addr, int32_t data)
{
	registers[addr] = data;
	return;
}

// Impressão do banco de registradores
void breg::dump_breg()
{
	printf("\nbreg:\n");
	for(uint8_t aux = 0; aux < 32; aux++)
		printf("\tregisters[%.2d] = %d = 0x%.8X\n", aux, registers[aux], registers[aux]/* & 0xFFFFFFFF*/);
	return;
}
