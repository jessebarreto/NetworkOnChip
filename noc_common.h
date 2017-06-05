/*
 * Universidade de Brasília - UnB
 *
 * Project - Network on Chip using SystemC
 * File: noc_common.h
 *
 * Changes Log
 * Created by José Adalberto F. Gualeve  on 07/07/15.
 * Modified by Felipe Cabral e Eduardo Mesquita on 05/07/16.
 * Modified by Jesse Barreto de Barros on 05/06/2017
 * Copyright 2015 - All rights reserved
 */

#ifndef NOC_COMMON_H
#define NOC_COMMON_H

#include <systemc.h>

const unsigned MEMORY_SIZE = 0x00300000;
const unsigned FLIT_SIZE = 32;   // bits
const unsigned BUFFER_SIZE = 32; // uint32_l's
const unsigned DEBUG_LVL = 2;    // 0: most restricted, 3: least restricted
                                 // 3 - mostra detalhes de transmissao entre roteadores (canais)
                                 // 2 - mostra detalhes de processamento dos modulos roteadores
                                 // 1 - mostra detalhes de processamento das interfaces de redes (NI)
                                 // 0 - mostra detalhes de processamento dos IP-cores


typedef sc_uint<FLIT_SIZE> flit_t;
typedef sc_uint<FLIT_SIZE/2> halfflit_t;
typedef sc_uint<FLIT_SIZE/4> quarterflit_t;

const unsigned NOC_SIZE = 6; // Number of Processor Elements
const unsigned NOC_ROW_SIZE = 2; // Number of PE per row

// Link
enum Link {
    Local = 0,
    North = 1,
    South = 2,
    East = 3,
    West = 4
};

#endif // NOC_COMMON_H
