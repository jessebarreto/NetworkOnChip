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

#include "flit.h"

#define NOC_COMMON_DEBUG (NoCDebug::Assembly | NoCDebug::Channel)

namespace NoCDebug
{
    enum DebugLevel {       // 0x10: most restricted, 0x01: least restricted
        PE  = 0x10,         // mostra detalhes de processamento dos IP-cores (Processor Elements)
        NI = 0x08,          // mostra detalhes de processamento das interfaces de redes (NI)
        Router = 0x04,      // mostra detalhes de processamento dos modulos roteadores
        Channel = 0x02,     // mostra detalhes de transmissao entre roteadores (canais)
        Assembly = 0x01     // mostra detalhes da criação da NoC
    };

    /*!
     * \brief This function is responsible to print debug information to the NoC log.
     * \param message
     * \param type
     * \param isError
     */
    static void printDebug(const std::string &message, DebugLevel type, bool isError = false)
    {
        if (NOC_COMMON_DEBUG & type) {
            std::cout << "[DEBUG-Type: " << type << "]";
            if (isError) {
                std::cout << "[ERROR]";
            }
            std::cout << " - " << message << std::endl;
        }
    }
}

// Project Parameters
const unsigned ROUTER_BUFFER_SIZE = 32; // Number of Flits of a router channel buffer

// NoC Topology Characteristics
const unsigned NOC_SIZE = 6; // Number of Processor Elements
const unsigned NOC_ROW_SIZE = 3; // Number of PE per row

// Link Type
enum Link {
    Local = 0,
    North = 1,
    South = 2,
    East = 3,
    West = 4
};

// Processor Elements Placing

//typedef std::vector<std::tuple<unsigned, unsigned, unsigned> > map_t;


#endif // NOC_COMMON_H
