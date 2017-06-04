/*
 * Decod.h
 *
 *  Created on: 09/07/2015
 *   *  Modified by José Adalberto F. Gualeve on 30/04/16
 *   *  Modified by Felipe Cabral on 05/07/16.
 *      Author: soudre
 */

#ifndef DECOD_H
#define DECOD_H
#include <systemc.h>
#include "noc_common.h"

SC_MODULE(Decod) {

	//Entrada e saida do modulo de decodificacao:(recebe o flit do roteamento e o desempacota, entregando ao modulo de destino)

	sc_fifo_in<sc_uint<53> > i_decod;
	sc_fifo_out<sc_uint<32> > o_decod;



	SC_HAS_PROCESS(Decod);

		Decod(sc_module_name n) :
				sc_module(n), FIFO0(1024), FIFO1(1024), FIFO2(1024), FIFO3(1024), FIFO4(1024), FIFO5(1024) {
			SC_THREAD(lerDecod);
			SC_THREAD(main);
		}

		void lerDecod();
		void main();



	private:

		bool eh_decod;

		sc_fifo< flit_t > FIFO0;
		sc_fifo< flit_t > FIFO1;
		sc_fifo< flit_t > FIFO2;
		sc_fifo< flit_t > FIFO3;
		sc_fifo< flit_t > FIFO4;
		sc_fifo< flit_t > FIFO5;

		sc_uint<53> dado_decod;

		sc_event dado_decod_evt, main_ack2_evt;


	};
#endif
