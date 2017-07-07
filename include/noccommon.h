/*
 * Universidade de Brasília - UnB
 *
 * Project - Network on Chip using SystemC
 * File: noccommon.h
 *
 * Changes Log
 * Created by José Adalberto F. Gualeve  on 07/07/15.
 * Modified by Felipe Cabral e Eduardo Mesquita on 05/07/16.
 * Modified by Jesse Barreto on 05/07/2017
 * Copyright 2015, 2016, 2017 - All rights reserved
 */

#ifndef NOC_COMMON_H
#define NOC_COMMON_H

// System C Library
#include <systemc.h>

// STL Libraries
#include <iostream>
#include <map>

// Project Parameters
const unsigned NOC_ROUTER_BUFFER_SIZE = 32; // Number of Flits of a router channel buffer
const unsigned NOC_ROUTER_ROUND_ROBIN_SIZE = 3; // Number of Flits sent by the arbiter before it preemptively changes.

// NoC Topology Characteristics
const unsigned NOC_SIZE = 6; // Number of Processor Elements
const unsigned NOC_ROW_SIZE = 2; // Number of PE per row

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

/*!
 * \brief Routing Information
 * \param position Destination Router.
 * \param link Link used in the current router to reach the destination router.
 */
struct routingInfo
{
    unsigned position;
    unsigned link;
};

#endif // NOC_COMMON_H
