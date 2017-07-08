#include "systemc.h"

#ifndef BREG_H_
#define BREG_H_

// Interface do banco de registradores
struct breg_if : public sc_interface
{
	virtual int32_t read(uint8_t addr) = 0;
	virtual void write(uint8_t addr, int32_t data) = 0;
	virtual void dump_breg() = 0;
};

// Banco de Registradores
struct breg : public sc_module, public breg_if
{
	// Funções de interface
	int read(uint8_t addr);
	void write(uint8_t addr, int32_t data);
	void dump_breg();

	// Função de inicialização
	void init();

	// Construtor
	SC_CTOR(breg)
	{
		registers = new int32_t[32];
		SC_THREAD(init);
	}

private:
	int32_t *registers;
};

#endif
