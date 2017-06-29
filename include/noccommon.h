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

// System C Library
#include <systemc.h>

// STL Libraries
#include <iostream>
#include <map>

// User Libraries
#include "nocdebug.h"
#include "router.h"
#include "routerchannel.h"
#include "networkinterface.h"

// Project Parameters
const unsigned ROUTER_BUFFER_SIZE = 32; // Number of Flits of a router channel buffer

// NoC Topology Characteristics
const unsigned NOC_SIZE = 2; // Number of Processor Elements
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
 * \brief Connect a pair of routers.
 * \param routerSource The source router.
 * \param routerDestination The destination router.
 * \param channel The channel that will be used to connect both routers.
 * \param directionHorizontal The direction of this connection. (Horizontal = false, Vertical = true)
 */
inline void connectRouters(Router &routerSource, Router &routerDestination, RouterChannel &channel,
                           bool directionHorizontal)
{
    if (directionHorizontal) {
        routerSource.westChannel(channel);
        routerDestination.eastChannel(channel);
    } else {
        routerSource.southChannel(channel);
        routerDestination.northChannel(channel);
    }
}

/*!
 * \brief Connect the empty channels of a router, i.e., channels that were not connected before.
 * \param router The router that will have its channels connected.
 * \param routerId  The identity of this router.
 * \param channels NoC's vector of channels.
 */
inline void connectEmptyChannels(Router *router, int routerId, std::vector<RouterChannel *> *channels)
{
    // Connect Straw Channels
    bool isNorthDisconnected = (router->northChannel.bind_count() == 0);
    bool isSouthDisconnected = (router->southChannel.bind_count() == 0);
    bool isEastDisconnected = (router->eastChannel.bind_count() == 0);
    bool isWestDisconnected = (router->westChannel.bind_count() == 0);

    if (!(isNorthDisconnected || isSouthDisconnected || isEastDisconnected || isWestDisconnected)) {
        return;
    }
    std::string channelBaseName = std::string("RouterChannelEmpty_") + std::to_string(routerId) + std::string("_");
    RouterChannel *channel;
    if (isNorthDisconnected) {
        channel = new RouterChannel(std::string(channelBaseName + std::to_string(Link::North)).c_str());
        router->northChannel(*channel);
        channels->push_back(channel);
    }

    if (isSouthDisconnected) {
        channel = new RouterChannel(std::string(channelBaseName + std::to_string(Link::South)).c_str());
        router->southChannel(*channel);
        channels->push_back(channel);
    }

    if (isEastDisconnected) {
        channel = new RouterChannel(std::string(channelBaseName + std::to_string(Link::East)).c_str());
        router->eastChannel(*channel);
        channels->push_back(channel);
    }

    if (isWestDisconnected) {
        channel = new RouterChannel(std::string(channelBaseName + std::to_string(Link::West)).c_str());
        router->westChannel(*channel);
        channels->push_back(channel);
    }
}

// Assemble NoC Topology
// Type A - Horizontal Connection
// Source Channel: East
// Destination Channel: West
//
// Type B - Vertical Connection
// Source Channel: South
//  Destination Channel: North
//
//		   B
//	      ||
//	      ||
//	A ===(ri)
//
// New routers must be connected to their left-side and up-side routers
// Should them exist and respecting the topology
inline void assembleNoC(std::vector<Router *> &routers, std::vector<RouterChannel *> &routerChannels)
{
    for (unsigned i = 1; i < NOC_SIZE; i++) {
        //Type A
        //Source Index
        unsigned sourceA = i - 1;;
        // 1. Check if the current router is in same row as the previous router
        if (ceil((sourceA + 1)/NOC_ROW_SIZE) == ceil((i + 1)/NOC_ROW_SIZE)) {
            std::string routerChannelName("RouterChannel_");
            routerChannelName += std::to_string(i) + "_" + std::to_string(sourceA);
            RouterChannel *channel = new RouterChannel(routerChannelName.c_str());
            connectRouters(*routers.at(i), *routers.at(sourceA), *channel, false);
            routerChannels.push_back(channel);
            NoCDebug::printDebug(std::string("Connect R" + std::to_string(i) + " to R" +
                                             std::to_string(sourceA) + " from West"), NoCDebug::Assembly);
        }

        //Type B
        //Source Index
        unsigned sourceB = i - NOC_ROW_SIZE;
        // 1. Check if isn't a topology in row
        // 2. Check if isn't the first row
        if (NOC_SIZE != NOC_ROW_SIZE && i > NOC_ROW_SIZE) {
            std::string routerChannelName("RouterChannel_");
            routerChannelName += std::to_string(i) + "_" + std::to_string(sourceB);
            RouterChannel *channel = new RouterChannel(routerChannelName.c_str());
            connectRouters(*routers.at(i), *routers.at(sourceB), *channel, false);
            routerChannels.push_back(channel);
            NoCDebug::printDebug(std::string("Connect R" + std::to_string(i) + " to R" + std::to_string(sourceB) +
                                             " from North"), NoCDebug::Assembly);
        }
    }
}

inline void connectStrayChannels(std::vector<Router *> &routers, std::vector<RouterChannel *> &routerChannels,
                                 std::vector<NetworkInterface *> &networkInterfaces)
{
    NoCDebug::printDebug(std::string("Connect Straw Channels and NIs"), NoCDebug::Assembly);
    for (int i = 0; i < NOC_SIZE; i++) {
        Router *router = routers.at(i);
        NetworkInterface *ni = networkInterfaces.at(i);
        RouterChannel *channel = new RouterChannel(std::string("RouterChannel_"
                                                               + std::to_string(i) + "_" + std::to_string(i)).c_str());
        router->localChannel(*channel);
        ni->localChannel(*channel);

        connectEmptyChannels(router, i, &routerChannels);
    }
}

#endif // NOC_COMMON_H
