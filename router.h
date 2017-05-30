/*
 *  router.h
 *  roteador
 *
 *  Created by Ricardo Jacobi on 27/5/15.
 *  Modified by Felipe Cabral on 25/06/16.
 *  Copyright 2015 Universidade de Brasilia. All rights reserved.
 *
 */

#ifndef ROUTER_H
#define ROUTER_H

#include <systemc.h>
#include "noc_common.h"

SC_MODULE(Router) {

	//Entradas e saidas do modulo de roteamento
	sc_fifo_in<sc_uint<53> > i_norte, i_oeste, i_sul, i_leste, i_cod;
	sc_fifo_out<sc_uint<53> > o_sul, o_leste, o_oeste, o_norte, o_decod;


	SC_HAS_PROCESS(Router);
	
	Router(sc_module_name n) : 
			sc_module(n) {
		SC_THREAD(lerOeste);
		SC_THREAD(lerSul);
		SC_THREAD(lerLeste);
		SC_THREAD(lerNorte);
		SC_THREAD(lerCod);
		SC_THREAD(Norte);
		SC_THREAD(Sul);
		SC_THREAD(Leste);
		SC_THREAD(Oeste);
		SC_THREAD(Cod);
	}
	
	void lerOeste();
	void lerSul();
	void lerLeste();
	void lerNorte();
	void lerCod();
	void Norte();
	void Sul();
	void Leste();
	void Oeste();
	void Cod();
	



private:

	sc_event dado_oeste_evt, dado_norte_evt, dado_sul_evt, dado_leste_evt, dado_cod_evt;
	sc_event norte_ack_evt, sul_ack_evt, leste_ack_evt, oeste_ack_evt, cod_ack_evt;

	sc_uint<53> dado_oeste, dado_norte, dado_sul, dado_leste, dado_cod;

	bool eh_oeste, eh_norte, eh_sul, eh_leste, eh_cod;

	int x, y, ent, said, saida;

	void Run(sc_uint<53> tmp);

};

#endif
