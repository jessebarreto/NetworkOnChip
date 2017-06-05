/*
 * Universidade de Brasília - UnB
 *
 * Project - Network on Chip using SystemC
 * File: main.cpp
 *
 * Changes Log
 * Created by José Adalberto F. Gualeve  and Marlon Soudre on 07/07/15.
 * Modified by José Adalberto F. Gualeve on 05/05/16
 * Modified by Felipe Cabral e Eduardo Mesquita on 05/07/16.
 * Modified by Jessé Barreto de Barros on 05/06/2017
 * Copyright 2015,2016 - All rights reserved
 */


/* NoC Topology

          [NI0]  ||             [NI1]  ||
              \\ ||                 \\ ||
           ====(r00)===r0001/r0100===(r01)=
                 ||                    ||
             r0010/r1000           r0111/r1101
                 ||                    ||
          [NI2]  ||             [NI3]  ||
              \\ ||                 \\ ||
           ====(r10)===r1011/r1110===(r11)==
                 ||                    ||
             r1020/r2010           r1121/r2111
                 ||                    ||
          [NI4]  ||             [NI5]  ||
              \\ ||                 \\ ||
           ====(r20)===r2021/r2120===(r21)===
                 ||                    ||


*/

#include <systemc.h>

#include "noc_common.h"
#include "router.h"
#include "routerchannel.h"
#include "networkinterface.h"

static void connectEmptyChannels(Router *router, int routerId, std::vector<RouterChannel *> *channels);

static void connectRouters(Router &routerSource, Router &routerDestination, RouterChannel &channel,
                           bool directionHorizontal);

int sc_main(int argc, char *argv[])
{
    // Routers
    std::vector<Router *> routers;
    for (unsigned i = 0; i < NOC_SIZE; i++) {
        std::string routerName("Router_");
        routerName += std::to_string(i);
        routers.push_back(new Router(routerName.c_str(), i));
    }

    // Network Interfaces
    std::vector<NetworkInterface *> networkInterfaces;
    for (unsigned i = 0; i < NOC_SIZE; i++) {
        std::string niName("NetworkInterface_");
        niName += std::to_string(i);
        networkInterfaces.push_back(new NetworkInterface(niName.c_str(), i));
    }

    // Processor Elements


    // Channels or Links
    std::vector<RouterChannel *> routerChannels;

    // Assemble NoC Topology
    // TODO: GitHub #8
    NoCDebug::printDebug(std::string("Connect Routers..."), NoCDebug::Assembly);
    for (unsigned i = 0; i < NOC_SIZE; i++) {
        for (unsigned j = 1; j <= NOC_ROW_SIZE && i + j < NOC_SIZE; j++) {
            bool shouldConnect;
            if (NOC_ROW_SIZE == 1 && (i % NOC_ROW_SIZE == (i + j) % NOC_ROW_SIZE)) {
                shouldConnect = true;
            } else {
                shouldConnect = (j == 1 && !(i % NOC_ROW_SIZE == NOC_ROW_SIZE - 1)) || (j == NOC_ROW_SIZE);
            }

            if (shouldConnect) {
                std::string routerChannelName("RouterChannel_");
                routerChannelName += std::to_string(i) + "_" + std::to_string(i + j);
                RouterChannel *channel = new RouterChannel(routerChannelName.c_str());
                connectRouters(*routers.at(i), *routers.at(i + j), *channel, j == 1);
                routerChannels.push_back(channel);
                NoCDebug::printDebug(std::string("Connect R" + std::to_string(i) + " to R" + std::to_string(i + j) +
                                                 " from " + std::string(((j == 1) ? "West" : "North"))),
                                     NoCDebug::Assembly);
            }
        }
    }
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

    // Start Simulation
    std::cout << "Start NoC Simulation..." << std::endl;
//    sc_start();

    return 0;
}

static void connectEmptyChannels(Router *router, int routerId, std::vector<RouterChannel *> *channels)
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

static void connectRouters(Router &routerSource, Router &routerDestination, RouterChannel &channel,
                           bool directionHorizontal)
{
    if (directionHorizontal) {
        routerSource.eastChannel(channel);
        routerDestination.westChannel(channel);
    } else {
        routerSource.southChannel(channel);
        routerDestination.northChannel(channel);
    }
}
