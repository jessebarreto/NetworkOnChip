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
const unsigned NOC_SIZE = 9; // Number of Processor Elements
const unsigned NOC_ROW_SIZE = 3; // Number of PE per row

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
struct routingInfo {
  unsigned position;
  unsigned link;
};

/*!
 * \brief Connect a pair of routers.
 * \param routerSource The source router.
 * \param routerDestination The destination router.
 * \param channel The channel that will be used to connect both routers.
 * \param direction The direction of this connection. (Horizontal = true, Vertical = false)
 */
inline void connectRouters(Router &routerSource, Router &routerDestination, RouterChannel &channel, bool direction)
{
    if (direction) {
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
//
// Type A - Horizontal Connection
//  Source Channel: East
//  Destination Channel: West
//
// Type B - Vertical Connection
//  Source Channel: South
//  Destination Channel: North
//
//		  B
//	      ||
//	      ||
//	A ===(Ri)
//
// New routers must be connected to their left-side and up-side routers
// Should them exist and respecting the topology
inline void assembleNoC(std::vector<Router *> &routers, std::vector<RouterChannel *> &routerChannels)
{
    NoCDebug::printDebug(std::string("Topology"), NoCDebug::Assembly);
    for (unsigned i = 1; i < NOC_SIZE; i++) {
        //Type A
        // 1. Check if the current router is in same row as the previous router
        if (ceil(float (i)/NOC_ROW_SIZE) == ceil(float (i + 1)/NOC_ROW_SIZE)) {
            //Source Index
            unsigned sourceA = i - 1;
            std::string routerChannelName("RouterChannel_");
            routerChannelName += std::to_string(sourceA) + "_" + std::to_string(i);
            RouterChannel *channel = new RouterChannel(routerChannelName.c_str());
            connectRouters(*routers.at(sourceA), *routers.at(i), *channel, true);
            routerChannels.push_back(channel);
            NoCDebug::printDebug(std::string("> Connect R" + std::to_string(sourceA) + " to R" + std::to_string(i) + " from West"), NoCDebug::Assembly);
        }

        //Type B
        // 1. Check if isn't a topology in row
        // 2. Check if isn't the first row
        if (NOC_SIZE != NOC_ROW_SIZE && i >= NOC_ROW_SIZE) {
            //Source Index
            unsigned sourceB = i - NOC_ROW_SIZE;
            std::string routerChannelName("RouterChannel_");
            routerChannelName += std::to_string(sourceB) + "_" + std::to_string(i);
            RouterChannel *channel = new RouterChannel(routerChannelName.c_str());
            connectRouters(*routers.at(sourceB), *routers.at(i), *channel, false);
            routerChannels.push_back(channel);
            NoCDebug::printDebug(std::string("> Connect R" + std::to_string(sourceB) + " to R" + std::to_string(i) + " from North"), NoCDebug::Assembly);
        }
    }
}

/*!
 * \brief Routing XY
 * \param source Position of the current router.
 * \param dest  Position of the destination router.
 */
inline routingInfo routingXY(unsigned source, unsigned dest) {

    NoCDebug::printDebug(std::string("Routing XY: " + std::to_string(source) + " --> " + std::to_string(dest)), NoCDebug::Router);

    //Identify Row (Y)
    //Source
    unsigned source_router_y = ceil(float (source + 1) / NOC_ROW_SIZE);
    //Dest
    unsigned dest_router_y = ceil(float (dest + 1) / NOC_ROW_SIZE);
    //DeltaX
    int deltaY = dest_router_y - source_router_y;

    //Identify Column (X)
    //Source
    unsigned source_router_x = (source + 1) - (source_router_y - 1) * NOC_ROW_SIZE;
    //Dest
    unsigned dest_router_x = (dest + 1) - (dest_router_y - 1) * NOC_ROW_SIZE;
    //DeltaY
    int deltaX = dest_router_x - source_router_x;

    NoCDebug::printDebug(std::string("Routing XY: DeltaX " + std::to_string(deltaX) + " DeltaY " + std::to_string(deltaY)), NoCDebug::Router);

    routingInfo rXY;

    //Move in X
    if (deltaX != 0) {

        NoCDebug::printDebug(std::string("Routing XY: Move X"), NoCDebug::Router);

        int stepX = (deltaX > 0) ? 1 : -1;

        unsigned updated_source_router_y = ceil(float (source + stepX + 1) / NOC_ROW_SIZE);

        // 1. Check if the current router is in same row as the target router (SourceX = UpdateY)
        if (source_router_y == updated_source_router_y) {

            //Move Source
            rXY.position = source + stepX;

            //Link Identification
            if (stepX > 0) {
                NoCDebug::printDebug(std::string("Routing XY: Link " + std::to_string(Link::East)), NoCDebug::Router);
                rXY.link = Link::East;
            } else {
                NoCDebug::printDebug(std::string("Routing XY: Link " + std::to_string(Link::West)), NoCDebug::Router);
                rXY.link = Link::West;
            }

        }

        //Error
        else {

            NoCDebug::printDebug(std::string("Routing XY: Wrong Move X"), NoCDebug::Router, true);

            rXY.position = source;
            rXY.link = -1;

        }

    }

    //Move in Y
    else if (deltaY != 0) {

        NoCDebug::printDebug(std::string("Routing XY: Move Y"), NoCDebug::Router);

        int stepY = (deltaY > 0) ? 1 : -1;

        unsigned updated_source_router_y = ceil(float (source + stepY * NOC_ROW_SIZE + 1) / NOC_ROW_SIZE);
        unsigned updated_source_router_x = (source + stepY * NOC_ROW_SIZE + 1) - (updated_source_router_y - 1) * NOC_ROW_SIZE;

        // 1. Check if the current router is in same column as the target router (SourceX = UpdateX)
        if (source_router_x == updated_source_router_x) {

            //Move Source
            rXY.position = source + stepY * NOC_ROW_SIZE;

            //Link Identification
            if (stepY > 0) {
                NoCDebug::printDebug(std::string("Routing XY: Link " + std::to_string(Link::South)), NoCDebug::Router);
                rXY.link = Link::South;
            } else {
                NoCDebug::printDebug(std::string("Routing XY: Link " + std::to_string(Link::North)), NoCDebug::Router);
                rXY.link = Link::North;
            }

        }

        //Error
        else {

            NoCDebug::printDebug(std::string("Routing XY: Wrong Move Y"), NoCDebug::Router, true);

            rXY.position = source;
            rXY.link = -1;

        }

    }

    //In position
    else {

        NoCDebug::printDebug(std::string("Routing XY: In position"), NoCDebug::Router);

        rXY.position = source;
        rXY.link = 0;

    }

    return rXY;

}

/*!
 * \brief Routing XY
 * \param source Position of the current router.
 * \param dest  Position of the destination router.
 */
inline routingInfo routingYX(unsigned source, unsigned dest) {

    NoCDebug::printDebug(std::string("Routing YX: " + std::to_string(source) + " --> " + std::to_string(dest)), NoCDebug::Router);

    //Identify Row (Y)
    //Source
    unsigned source_router_y = ceil(float (source + 1) / NOC_ROW_SIZE);
    //Dest
    unsigned dest_router_y = ceil(float (dest + 1) / NOC_ROW_SIZE);
    //DeltaX
    int deltaY = dest_router_y - source_router_y;

    //Identify Column (X)
    //Source
    unsigned source_router_x = (source + 1) - (source_router_y - 1) * NOC_ROW_SIZE;
    //Dest
    unsigned dest_router_x = (dest + 1) - (dest_router_y - 1) * NOC_ROW_SIZE;
    //DeltaY
    int deltaX = dest_router_x - source_router_x;

    NoCDebug::printDebug(std::string("Routing YX: DeltaX " + std::to_string(deltaX) + " DeltaY " + std::to_string(deltaY)), NoCDebug::Router);

    routingInfo rYX;

    //Move in Y
    if (deltaY != 0) {

        NoCDebug::printDebug(std::string("Routing YX: Move Y"), NoCDebug::Router);

        int stepY = (deltaY > 0) ? 1 : -1;

        unsigned updated_source_router_y = ceil(float (source + stepY * NOC_ROW_SIZE + 1) / NOC_ROW_SIZE);
        unsigned updated_source_router_x = (source + stepY * NOC_ROW_SIZE + 1) - (updated_source_router_y - 1) * NOC_ROW_SIZE;

        // 1. Check if the current router is in same column as the target router (SourceX = UpdateX)
        if (source_router_x == updated_source_router_x) {

            //Move Source
            rYX.position = source + stepY * NOC_ROW_SIZE;

            //Link Identification
            if (stepY > 0) {
                NoCDebug::printDebug(std::string("Routing YX: Link " + std::to_string(Link::South)), NoCDebug::Router);
                rYX.link = Link::South;
            } else {
                NoCDebug::printDebug(std::string("Routing YX: Link " + std::to_string(Link::North)), NoCDebug::Router);
                rYX.link = Link::North;
            }

        }

        //Error
        else {

            NoCDebug::printDebug(std::string("Routing YX: Wrong Move Y"), NoCDebug::Router, true);

            rYX.position = source;
            rYX.link = -1;

        }

    }

    //Move in X
    else if (deltaX != 0) {

        NoCDebug::printDebug(std::string("Routing YX: Move X"), NoCDebug::Router);

        int stepX = (deltaX > 0) ? 1 : -1;

        unsigned updated_source_router_y = ceil(float (source + stepX + 1) / NOC_ROW_SIZE);

        // 1. Check if the current router is in same row as the target router (SourceX = UpdateY)
        if (source_router_y == updated_source_router_y) {

            //Move Source
            rYX.position = source + stepX;

            //Link Identification
            if (stepX > 0) {
                NoCDebug::printDebug(std::string("Routing YX: Link " + std::to_string(Link::East)), NoCDebug::Router);
                rYX.link = Link::East;
            } else {
                NoCDebug::printDebug(std::string("Routing YX: Link " + std::to_string(Link::West)), NoCDebug::Router);
                rYX.link = Link::West;
            }

        }

        //Error
        else {

            NoCDebug::printDebug(std::string("Routing YX: Wrong Move X"), NoCDebug::Router, true);

            rYX.position = source;
            rYX.link = -1;

        }

    }

    //In position
    else {

        NoCDebug::printDebug(std::string("Routing YX: In position"), NoCDebug::Router);

        rYX.position = source;
        rYX.link = 0;

    }

    return rYX;

}


/*!
 * \brief Function to test the routing algorithm
 * \param source Position of the current router.
 * \param dest  Position of the destination router.
 */
inline void routingTest(unsigned source, unsigned dest) {

    //Fail Safe: Source
    if (source < 0 || source > NOC_SIZE - 1) {

        NoCDebug::printDebug(std::string("Routing: Source position isn't part of the NOC"), NoCDebug::Router, true);

    }

    //Fail Safe: Dest
    if (dest < 0 || dest > NOC_SIZE - 1) {

        NoCDebug::printDebug(std::string("Routing: Dest position isn't part of the NOC"), NoCDebug::Router,true);

    }

    //Max Routing steps
    unsigned step_max = (NOC_ROW_SIZE - 1) + unsigned (ceil(float (NOC_SIZE / NOC_ROW_SIZE)) -1);
    //Steps
    unsigned stepXY = 0;

    //Routing Algorithm: XY or YX
    routingInfo routing;

    routing = routingYX(source, dest);

    while (routing.link > 0 && stepXY <= step_max) {

        routing = routingYX(routing.position, dest);
        stepXY++;

    }

    //Error: Diverting Routing
    if (stepXY > step_max) {

        NoCDebug::printDebug(std::string("Routing: Diverting Routing"), NoCDebug::Router, true);

    }

    //Error: Logic Fail
    if (routing.link == -1 || routing.position > NOC_SIZE - 1) {

        NoCDebug::printDebug(std::string("Routing: Logic Fail"), NoCDebug::Router, true);

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
