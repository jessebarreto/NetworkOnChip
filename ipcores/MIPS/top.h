#include "systemc.h"
#include "stdarg.h"
#include "fetch.h"
#include "decode.h"
#include "execute.h"
#include "cache.h"
#include "mem.h"
#include "breg.h"

#ifndef TOP_H_
#define TOP_H_

// Função auxiliar para gerar codigo máquina de instruções
int32_t gen_inst(int n, ...)
{
	int32_t inst = 0;

	va_list ap;

	va_start(ap, n);

	switch (n)
	{
		case fm_R:
			inst |= (va_arg(ap, int ) & 0x3F) << 26;
			inst |= (va_arg(ap, int ) & 0x1F) << 21;
			inst |= (va_arg(ap, int ) & 0x1F) << 16;
			inst |= (va_arg(ap, int ) & 0x1F) << 11;
			inst |= (va_arg(ap, int ) & 0x1F) << 6;
			inst |= (va_arg(ap, int ) & 0x3F);
			break;
		case fm_I:
			inst |= (va_arg(ap, int ) & 0x3F) << 26;
			inst |= (va_arg(ap, int ) & 0x1F) << 21;
			inst |= (va_arg(ap, int ) & 0x1F) << 16;
			inst |= (va_arg(ap, int ) & 0xFFFF);
			break;
		case fm_J:
			inst |= (va_arg(ap, int ) & 0x3F) << 26;
			inst |= (va_arg(ap, int ) & 0x03FFFFFF);
			break;
		default:
			break;
	}

	return inst;
}

SC_MODULE(top)
{
	// Instancias dos módulos de fetch, decode e execute
	fetch f;
	decode d;
	execute e;

	// Instancias da cache, memória e do banco de registradores
	cache c;
	mem m;
	breg b;

	// Conectores
	sc_fifo <Context*> fetch_decode; // Fila bloqueante entre fetch e decode
	sc_fifo <Context*> decode_execute; // Fila bloqueante entre decode e execute
	sc_fifo <Context*> execute_fetch; // Fila bloqueante entre execute e fetch


	SC_CTOR(top) : f("f"), d("u"), e("e"), c("c"), m("m"), b("b"), fetch_decode(1), decode_execute(1), execute_fetch(1)
	{
		// Conectando elementos necessários no módulo de Fetch
		f.p_cache(c);
		f.from_execute(execute_fetch);
		f.to_decode(fetch_decode);

		// Conectando elementos necessários no módulo de Decode
		d.from_fetch(fetch_decode);
		d.to_execute(decode_execute);

		// Conectando elementos necessários no módulo de Execute
		e.p_cache(c);
		e.p_breg(b);
		e.from_decode(decode_execute);
		e.to_fetch(execute_fetch);

		// Conectando a memória principal à cache
		c.p_mem(m);

		// Inserindo um contexto de execução de entrada na fila entre execute e fetch para inicialização
		Context *entry = new Context();
		entry->pc = 0;
		entry->ir = 0;
		entry->hi = 0;
		entry->lo = 0;
		entry->op = 0;
		entry->rs = 0;
		entry->rt = 0;
		entry->rd = 0;
		entry->shamt = 0;
		entry->funct = 0;
		entry->const16 = 0;
		entry->const26 = 0;
		execute_fetch.write(entry);

		// Montagem do programa

		/*c.sw(,0,gen_inst(fm_R,i_FUN,,,,,fn_ADD));
		c.sw(,0,gen_inst(fm_R,i_FUN,,,,,fn_ADDU));
		c.sw(,0,gen_inst(fm_R,i_FUN,,,,,fn_SUB));
		c.sw(,0,gen_inst(fm_R,i_FUN,,,,,fn_MULT));
		c.sw(,0,gen_inst(fm_R,i_FUN,,,,,fn_DIV));
		c.sw(,0,gen_inst(fm_R,i_FUN,,,,,fn_AND));
		c.sw(,0,gen_inst(fm_R,i_FUN,,,,,fn_OR));
		c.sw(,0,gen_inst(fm_R,i_FUN,,,,,fn_XOR));
		c.sw(,0,gen_inst(fm_R,i_FUN,,,,,fn_NOR));
		c.sw(,0,gen_inst(fm_R,i_FUN,,,,,fn_SLT));
		c.sw(,0,gen_inst(fm_R,i_FUN,,,,,fn_JR));
		c.sw(,0,gen_inst(fm_R,i_FUN,,,,,fn_SLL));
		c.sw(,0,gen_inst(fm_R,i_FUN,,,,,fn_SRL));
		c.sw(,0,gen_inst(fm_R,i_FUN,,,,,fn_SRA));
		c.sw(,0,gen_inst(fm_R,i_FUN,,,,,fn_SYSCALL));
		c.sw(,0,gen_inst(fm_R,i_FUN,,,,,fn_MFHI));
		c.sw(,0,gen_inst(fm_R,i_FUN,,,,,fn_MFLO));
		c.sw(,0,gen_inst(fm_R,i_FUN,,,,,fn_SLLV));
		c.sw(,0,gen_inst(fm_R,i_FUN,,,,,fn_SRAV));
		c.sw(,0,gen_inst(fm_R,i_FUN,,,,,fn_SRLV));
		c.sw(,0,gen_inst(fm_R,i_FUN,,,,,fn_SLTU));
		c.sw(,0,gen_inst(fm_I,i_LW,,,));
		c.sw(,0,gen_inst(fm_I,i_LB,,,));
		c.sw(,0,gen_inst(fm_I,i_LH,,,));
		c.sw(,0,gen_inst(fm_I,i_LBU,,,));
		c.sw(,0,gen_inst(fm_I,i_LHU,,,));
		c.sw(,0,gen_inst(fm_I,i_LUI,,,));
		c.sw(,0,gen_inst(fm_I,i_SW,,,));
		c.sw(,0,gen_inst(fm_I,i_SB,,,));
		c.sw(,0,gen_inst(fm_I,i_SH,,,));
		c.sw(,0,gen_inst(fm_I,i_BEQ,,,));
		c.sw(,0,gen_inst(fm_I,i_BNE,,,));
		c.sw(,0,gen_inst(fm_I,i_BLEZ,,,));
		c.sw(,0,gen_inst(fm_I,i_BGTZ,,,));
		c.sw(,0,gen_inst(fm_I,i_ADDI,,,));
		c.sw(,0,gen_inst(fm_I,i_ADDIU,,,));
		c.sw(,0,gen_inst(fm_I,i_SLTI,,,));
		c.sw(,0,gen_inst(fm_I,i_SLTIU,,,));
		c.sw(,0,gen_inst(fm_I,i_ANDI,,,));
		c.sw(,0,gen_inst(fm_I,i_ORI,,,));
		c.sw(,0,gen_inst(fm_I,i_XORI,,,));
		c.sw(,0,gen_inst(fm_J,i_J,));
		c.sw(,0,gen_inst(fm_J,i_JAL,));
		c.sw(,0,gen_inst(fm_J,i_BLTZ,));*/

		m.sw(0,0,gen_inst(fm_I,i_ADDI,r_ZERO,r_V0,10));
		m.sw(4,0,gen_inst(fm_R,i_FUN,0,0,0,0,fn_SYSCALL));
	}
};

#endif
