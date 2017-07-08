#include "systemc.h"
#include "shared.h"

#ifndef DECODE_H_
#define DECODE_H_

// Módulo de Decode
SC_MODULE(decode)
{
	sc_fifo_in <Context*> from_fetch;
	sc_fifo_out<Context*> to_execute;

	void decode_method()
	{
		while(true)
		{
			in = from_fetch.read();
			out = in;
			out->op = (in->ir >> 26) & 0x3F;
			out->rs = (in->ir >> 21) & 0x1F;
			out->rt = (in->ir >> 16) & 0x1F;
			out->rd = (in->ir >> 11) & 0x1F;
			out->shamt = (in->ir >> 6) & 0x1F;
			out->funct = in->ir & 0x3F;
			out->const16 = in->ir & 0xFFFF;
			out->const26 = in->ir & 0x03FFFFFF;
#ifdef DEBUG_MODE
			printf("\tIR: 0x%.8X\n\tOP: %d, RS: %d, RT: %d, RD: %d, SHAMT: %d, FUNCT: %d, "
			"CONST16: %d, CONST26: %d\n", out->ir/* & 0xFFFFFFFF*/, out->op, out->rs, out->rt,
			out->rd, out->shamt, out->funct, out->const16, out->const26);
#endif
			to_execute.write(out);
		}
	}

	SC_CTOR(decode)
	{
		SC_THREAD(decode_method);
		in = new Context();
		out = new Context();
	}

private:
	Context *in,
			*out;
};

#endif
