/*
 * cod.h
 *
 *  Created on: 08/07/2015
 *   *  Modified by José Adalberto F. Gualeve on 30/04/16
 *   *  Modified by Felipe Cabral e Eduardo Mesquita on 05/07/16.
 *      Author: soudre
 */

#ifndef COD_H
#define COD_H

#include <systemc.h>
#include "noc_common.h"

SC_MODULE(Cod) {

	//Entrada e saida do modulo de decodificacao:(recebe o flit do modulo e empacota-o para o protocolo de rede)
    sc_fifo_in<sc_uint<32> > i_cod;
    sc_fifo_out<sc_uint<53> > o_cod;
    SC_HAS_PROCESS(Cod);
  Cod(sc_module_name n) :
    sc_module(n) {
        SC_THREAD(lerCod);
        SC_THREAD(main);
    }
    void lerCod();
    void main();
  private:
    bool eh_cod;
    sc_uint<32> dado_cod;
    sc_event dado_cod_evt, main_ack_evt;
    int origem, destino, count;

};

#endif
