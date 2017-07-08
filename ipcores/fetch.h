#include "systemc.h"
#include "shared.h"
#include "cache.h"
//#include "mem.h"

#ifndef FETCH_H_
#define FETCH_H_


// Módulo de Fetch
SC_MODULE(fetch)
{
	sc_fifo_in <Context*> from_execute;
	sc_fifo_out <Context*> to_decode;
	sc_port <cache_if> p_cache;
	//sc_port <mem_if> p_mem;

	void fetch_method()
	{
		while(true)
		{
			in = from_execute.read();
#ifdef DEBUG_MODE
			printf("\nPC: %d\n", in->pc);
#endif
			out = in;
			out->ir = p_cache->lw(in->pc,0);
			//out->ir = p_mem->lw(in->pc,0);
			out->pc = (in->pc)+4;
			to_decode.write(out);
		}
	}

	SC_CTOR(fetch)
	{
		SC_THREAD(fetch_method);
		in = new Context;
		out = new Context;
	}

private:
	Context *in,
			*out;

};

#endif
