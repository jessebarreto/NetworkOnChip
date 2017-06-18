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
#include <map>

// Defines the Debug Level to be printed.
#define NOC_COMMON_DEBUG (NoCDebug::Assembly | NoCDebug::Channel | NoCDebug::Router | NoCDebug::NI | NoCDebug::PE)

// NoC Connections
#define NOC_CONNECTION_TEST 1

/*!
 * Namespace with everything related to Debug.
 */
namespace NoCDebug
{
    /*!
     * \brief The DebugLevel enumerates the multiple types of sources from debug.
     */
    enum DebugLevel {       // 0x10: most restricted, 0x01: least restricted
        PE  = 0x10,         // mostra detalhes de processamento dos IP-cores (Processor Elements)
        NI = 0x08,          // mostra detalhes de processamento das interfaces de redes (NI)
        Router = 0x04,      // mostra detalhes de processamento dos modulos roteadores
        Channel = 0x02,     // mostra detalhes de transmissao entre roteadores (canais)
        Assembly = 0x01     // mostra detalhes da criação da NoC
    };

    /*!
     * \brief Converts a DebugLevel type to its string value.
     * \param type The DebugLevel type, i.e, PE, NI, Router, Channel or Assembly.
     * \return The string value of the DebugLevel type or an empty string when a not registered DebugLevel type is used.
     */
    inline static const std::string debugTypeToString(DebugLevel type)
    {
        switch (type) {
        case DebugLevel::PE:
            return "PE";
        case DebugLevel::NI:
            return "NI";
        case DebugLevel::Router:
            return "Router";
        case DebugLevel::Channel:
            return "Channel";
        case DebugLevel::Assembly:
            return "Assembly";
        default:
            return "";
        }
    }

    /*!
     * \brief This function is responsible to print debug messages to execution console/log.
     * \param message The message to be printed.
     * \param type The type of the source of the message.
     * \param isError A flag that indicates a critical error on the system.
     *        Deal with this error as you like with assert, exceptiption handling or even exit.
     */
    static void printDebug(const std::string &message, DebugLevel type, bool isError = false)
    {
        if (NOC_COMMON_DEBUG & type) {
            std::cout << "[DEBUG-Type: " << debugTypeToString(type) << "]";
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
const unsigned NOC_SIZE = 2; // Number of Processor Elements
const unsigned NOC_ROW_SIZE = 2; // Number of PE per row

// Flit Parameters
const unsigned FLIT_SOURCE_SIZE = 8; // bits
const unsigned FLIT_DESTINATION_SIZE = 8; // bits
const unsigned FLIT_PACKET_SIZE = 8; // bits
const unsigned FLIT_SIZE = FLIT_SOURCE_SIZE + FLIT_DESTINATION_SIZE + FLIT_PACKET_SIZE;

// Common flit data type
typedef sc_uint<FLIT_SIZE> flit_t;
typedef sc_uint<FLIT_SIZE/2> halfflit_t;
typedef sc_uint<FLIT_SIZE/4> quarterflit_t;

// Link Type
enum Link {
    Local = 0,
    North = 1,
    South = 2,
    East = 3,
    West = 4
};

// Processors Map
// Maps the unique id from the processor to its NoC Position
typedef std::map<std::string, int> Map_t ;
static Map_t PROCESSORS_MAP;

#endif // NOC_COMMON_H
