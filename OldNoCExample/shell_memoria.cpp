/*
 *  memoria_shell.cpp
 *  MIPSc++
 *
 *  Created by Ricardo Jacobi on 18/4/15.
 *  Copyright 2015 Universidade de Brasilia. All rights reserved.
 *
 */

#include "globals.h"
#include "memoria.h"
#include "mem_if.h"

#include "noc_common.h"

//#include <iostream>
using namespace std;

SC_MODULE(shellme_mem_v0)
{
    sc_fifo_in<flit_t> in;
    sc_fifo_out<flit_t> out;

	sc_port<mem_if> pmem;
		
	// Variables
    sc_uint<32>
            flitz_1,
            flitz_2,
            flitz_3,
            cmd_tmp,
            size_tmp,

            address,
            dado,
				
            size,
            flit_tmp;

    void proc()
    {

            while (true) {
                    // At least two flips are always espected to be received
                flitz_1 = in.read();
                flitz_2 = in.read();

                    // If size = 2 receives another
                size_tmp = get_size(flitz_1);
                if (size_tmp == 2)
                    flitz_3 = in.read();

                cmd_tmp = get_cmd(flitz_1); // get command

                switch (cmd_tmp) {
                    case LB:
                        // send header flit throug fifo (size = 1)
                        size = 0x01;
                        flit_tmp = build_Hflit(M0, P, SW, size);
                        out.write(flit_tmp);
                        // sent data flit
                        address = flitz_2;
                        out.write(pmem->lb(address));
                        break;
                    case LBU:
                        // send header flit throug fifo (size = 1)
                        size = 0x01;
                        flit_tmp = build_Hflit(M0, P, SW, size);
                        out.write(flit_tmp);
                        // sent data flit
                        address = flitz_2;
                        out.write(pmem->lbu(address));
                        break;
                    case LH:
                        // send header flit throug fifo (size = 1)
                        size = 0x01;
                        flit_tmp = build_Hflit(M0, P, SW, size);
                        out.write(flit_tmp);
                        // sent data flit
                        address = flitz_2;
                        out.write(pmem->lh(address));
                        break;
                    case LHU:
                        // send header flit throug fifo (size = 1)
                        size = 0x01;
                        flit_tmp = build_Hflit(M0, P, SW, size);
                        out.write(flit_tmp);
                        // sent data flit
                        address = flitz_2;
                        out.write(pmem->lhu(address));
                        break;
                    case LW:
                        // send header flit throug fifo (size = 1)
                        size = 0x01;
                        flit_tmp = build_Hflit(M0, P, SW, size);
                        out.write(flit_tmp);
                        // sent data flit
                        address = flitz_2;
                        out.write(pmem->lw(address));
                        break;
                    case SB:
                        address = flitz_2;
                        dado = flitz_3;
                        pmem->sb(address, (int8_t)dado);
                        break;
                    case SH:
                        address = flitz_2;
                        dado = flitz_3;
                        pmem->sh(address, (int16_t)dado);
                        break;
                    case SW:
                        address = flitz_2;
                        dado = flitz_3;
                        pmem->sw(address, dado);
                        break;
                    default:
                        cout << "Erro: comando nao valido em - " << cmd_tmp;
                        exit(-1);
                        break;
                }
            }
    }


	SC_HAS_PROCESS (shellme_mem_v0);
    shellme_mem_v0(sc_module_name n, unsigned int identify) :
        sc_module(n),
        _identify(identify)
    {
		SC_THREAD(proc);
	}

private:
    unsigned int _identify;
};
