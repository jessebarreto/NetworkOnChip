#include "systemc.h"
#include "shared.h"
#include "cache.h"
//#include "mem.h"
#include "breg.h"

#ifndef EXECUTE_H_
#define EXECUTE_H_

// Módulo de Execute
SC_MODULE(execute)
{
	sc_fifo_in <Context*> from_decode;
	sc_fifo_out <Context*> to_fetch;
	sc_port <cache_if> p_cache;
	//sc_port <mem_if> p_mem;
	sc_port <breg_if> p_breg;

	void execute_method()
	{
		while(true)
		{
			in = from_decode.read();
			out = in;

			switch (in->op)
			{
				case i_FUN:
					switch (in->funct)
					{
						case fn_ADD:
							p_breg->write(in->rd,(p_breg->read(in->rs) + p_breg->read(in->rt)));
							break;
						case fn_ADDU:
							p_breg->write(in->rd,(p_breg->read(in->rs) + p_breg->read(in->rt)));
							break;
						case fn_SUB:
							p_breg->write(in->rd,(p_breg->read(in->rs) - p_breg->read(in->rt)));
							break;
						case fn_MULT:
							out->hi = ((int64_t)p_breg->read(in->rs) * p_breg->read(in->rt)) >> 32;
							out->lo = (int32_t)((int64_t)p_breg->read(in->rs) * p_breg->read(in->rt));
							break;
						case fn_DIV:
							out->hi = p_breg->read(in->rs) % p_breg->read(in->rt);
							out->lo = p_breg->read(in->rs) / p_breg->read(in->rt);
							break;
						case fn_AND:
							p_breg->write(in->rd,(p_breg->read(in->rs) & p_breg->read(in->rt)));
							break;
						case fn_OR:
							p_breg->write(in->rd,(p_breg->read(in->rs) | p_breg->read(in->rt)));
							break;
						case fn_XOR:
							p_breg->write(in->rd,(p_breg->read(in->rs) ^ p_breg->read(in->rt)));
							break;
						case fn_NOR:
							p_breg->write(in->rd,~(p_breg->read(in->rs) | p_breg->read(in->rt)));
							break;
						case fn_SLT:
							p_breg->write(in->rd,(p_breg->read(in->rs) < p_breg->read(in->rt)));
							break;
						case fn_JR:
							out->pc = p_breg->read(in->rs);
							break;
						case fn_SLL:
							p_breg->write(in->rd,(p_breg->read(in->rt) << in->shamt));
							break;
						case fn_SRL:
							p_breg->write(in->rd,(uint32_t)(p_breg->read(in->rt) >> in->shamt));
							break;
						case fn_SRA:
							p_breg->write(in->rd,(p_breg->read(in->rt) >> in->shamt));
							break;
						case fn_SYSCALL:
							switch (p_breg->read(r_V0))
							{
								case s_EXIT:
#ifdef DEBUG_MODE
									p_breg->dump_breg();
									p_cache->dump_cache(0,127);
									//p_mem->dump_mem(0,127);
#endif
									sc_stop();
									break;
								default:
									printf("\nMIPS Error: unsupported syscall value (0x%.8X).\n",p_breg->read(r_V0));
									sc_stop();
									break;
							}
							break;
						case fn_MFHI:
							p_breg->write(in->rd,in->hi);
							break;
						case fn_MFLO:
							p_breg->write(in->rd,in->lo);
							break;
						case fn_SLLV:
							p_breg->write(in->rd,(p_breg->read(in->rt) << p_breg->read(in->rs)));
							break;
						case fn_SRAV:
							p_breg->write(in->rd,(p_breg->read(in->rt) >> p_breg->read(in->rs)));
							break;
						case fn_SRLV:
							p_breg->write(in->rd,(uint32_t)(p_breg->read(in->rt) >> p_breg->read(in->rs)));
							break;
						case fn_SLTU:
							p_breg->write(in->rd,((uint32_t)(p_breg->read(in->rs)) < (uint32_t)(p_breg->read(in->rt))));
							break;
						default:
							printf("\nMIPS Error: unsupported funct value (0x%.8X).\n",in->funct);
							sc_stop();
							break;
					}
					break;
				case i_LW:
					p_breg->write(in->rt,p_cache->lw(p_breg->read(in->rs),in->const16));
					break;
				case i_LB:
					p_breg->write(in->rt,p_cache->lb(p_breg->read(in->rs),in->const16));
					break;
				case i_LH:
					p_breg->write(in->rt,p_cache->lh(p_breg->read(in->rs),in->const16));
					break;
				case i_LBU:
					p_breg->write(in->rt,p_cache->lbu(p_breg->read(in->rs),in->const16));
					break;
				case i_LHU:
					p_breg->write(in->rt,p_cache->lhu(p_breg->read(in->rs),in->const16));
					break;
				case i_LUI:
					p_breg->write(in->rt,in->const16 << 16);
					break;
				case i_SW:
					p_cache->sw(p_breg->read(in->rs),in->const16,p_breg->read(in->rt));
					break;
				case i_SB:
					p_cache->sb(p_breg->read(in->rs),in->const16,p_breg->read(in->rt));
					break;
				case i_SH:
					p_cache->sh(p_breg->read(in->rs),in->const16,p_breg->read(in->rt));
					break;
				case i_BEQ:
					if(p_breg->read(in->rs) == p_breg->read(in->rt))
						out->pc += (in->const16 << 2);
					break;
				case i_BNE:
					if(p_breg->read(in->rs) != p_breg->read(in->rt))
						out->pc += (in->const16 << 2);
					break;
				case i_BLEZ:
					if(p_breg->read(in->rs) <= 0)
						out->pc += (in->const16 << 2);
					break;
				case i_BGTZ:
					if(p_breg->read(in->rs) > 0)
						out->pc += (in->const16 << 2);
					break;
				case i_ADDI:
					p_breg->write(in->rt,(p_breg->read(in->rs) + in->const16));
					break;
				case i_ADDIU:
					p_breg->write(in->rt,((uint32_t)p_breg->read(in->rs) + in->const16));
					break;
				case i_SLTI:
					p_breg->write(in->rt,(p_breg->read(in->rs) < in->const16));
					break;
				case i_SLTIU:
					p_breg->write(in->rt,((uint32_t)p_breg->read(in->rs) < (uint32_t)in->const16));
					break;
				case i_ANDI:
					p_breg->write(in->rt,(p_breg->read(in->rs) & (uint32_t)in->const16));
					break;
				case i_ORI:
					p_breg->write(in->rt,(p_breg->read(in->rs) | (uint32_t)in->const16));
					break;
				case i_XORI:
					p_breg->write(in->rt,(p_breg->read(in->rs) ^ (uint32_t)in->const16));
					break;
				case i_J:
					out->pc = (in->pc & 0xf0000000) | (in->const26 << 2);
					break;
				case i_JAL:
					p_breg->write(r_RA,in->pc);
					out->pc = (in->pc & 0xf0000000) | (in->const26 << 2);
					break;
				case i_BLTZ:
					if(p_breg->read(in->rs) < 0)
						out->pc += (in->const16 << 2);
					break;
				default:
					printf("\nMIPS Error: unsupported opcode value (0x%.8X)\n",in->op);
					sc_stop();
					break;
			}

			// Registrador 0 não deve ser alterado
			p_breg->write(r_ZERO, 0);

			to_fetch.write(out);
		}
	}

	SC_CTOR(execute)
	{
		SC_THREAD(execute_method);
		in = new Context();
		out = new Context();
	}

private:
	Context *in,
			*out;

};

#endif
