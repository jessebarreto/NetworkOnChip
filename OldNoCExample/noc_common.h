/*
 * - noc_common.h
 * 
 * Created by José Adalberto F. Gualeve  on 07/07/15.
 *  Modified by Felipe Cabral e Eduardo Mesquita on 05/07/16.
 * Copyright 2015 - All rights reserved 
*/
#ifndef noc_common_h
#define noc_common_h

#include <systemc.h>

const int mem_size = 0x00300000;
const int flit_size = 32;   // bits
const int buffer_size = 32; // uint32_l's
//const int pkg_size = 8;     // flits
const int debug = 2; // 0: most restricted, 3: least restricted
                     // 3 - mostra detalhes de transmissao entre roteadores (canais)
                     // 2 - mostra detalhes de processamento dos modulos roteadores
                     // 1 - mostra detalhes de processamento das interfaces de redes (NI)
                     // 0 - mostra detalbes de processamento dos IP-cores


typedef sc_uint<flit_size> flit_t;
typedef sc_uint<flit_size/2> flit1_2t;
typedef sc_uint<flit_size/4> flit1_4t;

const flit1_4t CMD_SB=0x28, // command store a byte 0b0010.1000
    CMD_SH=0x29, // command store a half word       0b0010.1001
    CMD_SW=0x2B, // command store a word            0b0010.1011
    CMD_LB=0x20, // command load a byte             0b0010.0000
    CMD_LH=0x21, // command load a half word        0b0010.0001
    CMD_LW=0x23; // command load a word             0b0010.0011

// control inline, used to code debuging
inline void passo(const char* id, int x ) 
{    
    cout <<"In " << id << ",checked "<<x<<endl;
}


#endif
