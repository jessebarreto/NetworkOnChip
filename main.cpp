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
#include <iostream>

#include "noc_common.h"
#include "router.h"
#include "routerchannel.h"
#include "networkinterface.h"

int sc_main(int argc, char *argv[])
{
    // Channels or Links
    std::vector<RouterChannel *> routerChannels;
    for (unsigned i = 0; i < NOC_SIZE; i++) {
        for (unsigned j = 0; j < 5; j++) {
            std::string routerChannelName("RouterChannel_");
            routerChannelName += std::to_string(i) + std::string("_") + std::to_string(j);
            routerChannels.push_back(new RouterChannel(routerChannelName.c_str(), i*NOC_SIZE + j));
        }
    }

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
        networkInterfaces.push_back(new NetworkInterface(niName.c_str()));
    }

    // Processor Elements

    // Assemble NoC Topology
    for (unsigned i = 0; i < NOC_SIZE; i ++) {
        Router *router = routers.at(i);
        NetworkInterface *ni = networkInterfaces.at(i);
        ni->localChannel(*routerChannels.at(i * NOC_SIZE + Link::Local));
        router->localChannel(*routerChannels.at(i * NOC_SIZE + Link::Local));
        router->northChannel(*routerChannels.at(i * NOC_SIZE + Link::North));
        router->southChannel(*routerChannels.at(i * NOC_SIZE + Link::South));
        router->eastChannel (*routerChannels.at(i * NOC_SIZE + Link::East));
        router->westChannel (*routerChannels.at(i * NOC_SIZE + Link::West));

        int row = i / NOC_ROW_SIZE;
        int col = i % NOC_ROW_SIZE;

        if (!row) {
            routers.at(i)->northChannel(*routerChannels.at((i - 1) * NOC_SIZE + Link::South));
        }

        if (!col) {
            routers.at(col)->westChannel (*routerChannels.at(row * NOC_SIZE + Link::East));
        }
    }

//    for (unsigned i = 0; i < NOC_SIZE; i += 2) {
//        Router *router = routers.at(i);
//        NetworkInterface *ni = networkInterfaces.at(i);


//        router->localChannel(*routerChannels.at(i * NOC_SIZE + Link::Local));
//        router->northChannel(*routerChannels.at(i * NOC_SIZE + Link::North));
//        router->southChannel(*routerChannels.at(i * NOC_SIZE + Link::South));
//        router->eastChannel (*routerChannels.at(i * NOC_SIZE + Link::East));
//        router->westChannel (*routerChannels.at(i * NOC_SIZE + Link::West));
//    }

    // Start Simulation
    std::cout << "Start NoC Simulation..." << std::endl;
    sc_start();

    return 0;
}
