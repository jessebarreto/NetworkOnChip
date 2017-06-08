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
#include <iostream>

#define NOC_COMMON_DEBUG (NoCDebug::Assembly || NoCDebug::Channel)

namespace NoCDebug
{
    enum DebugLevel {       // 0x10: most restricted, 0x01: least restricted
        PE  = 0x10,         // mostra detalhes de processamento dos IP-cores (Processor Elements)
        NI = 0x08,          // mostra detalhes de processamento das interfaces de redes (NI)
        Router = 0x04,      // mostra detalhes de processamento dos modulos roteadores
        Channel = 0x02,     // mostra detalhes de transmissao entre roteadores (canais)
        Assembly = 0x01     // mostra detalhes da criação da NoC
    };

    static void printDebug(const std::string &message, DebugLevel type)
    {
        if (NOC_COMMON_DEBUG && type) {
            std::cout << "[DEBUG-Type: " << type << "] - " << message << std::endl;
        }
    }
}

// Project Parameters
const unsigned MEMORY_SIZE = 0x00300000;
const unsigned FLIT_SOURCE_SIZE = 8; // bits
const unsigned FLIT_DESTINATION_SIZE = 8; // bits
const unsigned FLIT_N_PACKETS_SIZE = 8; // bits
const unsigned FLIT_ID_SIZE = 8; // bits

const unsigned FLIT_SIZE = FLIT_SOURCE_SIZE + FLIT_DESTINATION_SIZE + FLIT_N_PACKETS_SIZE + FLIT_ID_SIZE;
const unsigned BUFFER_SIZE = 32; // uint32_l's
const unsigned NOC_DEBUG = NoCDebug::Assembly;

// Common Types
typedef sc_uint<FLIT_SIZE> flit_t;
typedef sc_uint<FLIT_SIZE/2> halfflit_t;
typedef sc_uint<FLIT_SIZE/4> quarterflit_t;

// NoC Topology Characteristics
const unsigned NOC_SIZE = 4; // Number of Processor Elements
const unsigned NOC_ROW_SIZE = 2; // Number of PE per row

// Link Type
enum Link {
    Local = 0,
    North = 1,
    South = 2,
    East = 3,
    West = 4
};

#endif // NOC_COMMON_H
