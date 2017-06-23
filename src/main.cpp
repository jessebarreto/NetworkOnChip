/*
 * Universidade de Brasília - UnB
 * Departamento de Ciências da Computação
 * Project - Network on Chip using SystemC
 * File: main.cpp
 *
 * Changes Log
 * Created by José Adalberto F. Gualeve  and Marlon Soudre on 07/07/15.
 * Modified by José Adalberto F. Gualeve on 05/05/16
 * Modified by Felipe Cabral e Eduardo Mesquita on 05/07/16.
 * Modified by Jessé Barreto de Barros on 05/06/2017
 * Copyright 2015, 2016, 2017 - All rights reserved
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

//#include <systemc.h>

#include "noccommon.h"
#include "router.h"
#include "routerchannel.h"
#include "networkinterface.h"

#if NOC_CONNECTION_TEST
#include "petestreceiver.h"
#include "petestreceiverfrontend.h"
#include "petestsender.h"
#include "petestsenderfrontend.h"
#include "channeltester.h"
#endif //NOC_CONNECTION_TEST

/*!
 * \brief Connect the empty channels of a router, i.e., channels that were not connected before.
 * \param router The router that will have its channels connected.
 * \param routerId  The identity of this router.
 * \param channels NoC's vector of channels.
 */
static void connectEmptyChannels(Router *router, int routerId, std::vector<RouterChannel *> *channels);

/*!
 * \brief Connect a pair of routers.
 * \param routerSource The source router.
 * \param routerDestination The destination router.
 * \param channel The channel that will be used to connect both routers.
 * \param directionHorizontal The direction of this connection. (Horizontal = false, Vertical = true)
 */
static void connectRouters(Router &routerSource, Router &routerDestination, RouterChannel &channel,
                           bool directionHorizontal);

/*!
 * \brief Main Function
 */
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

    // Processor Elements Connections
#if NOC_CONNECTION_TEST
//    PETestSender *testSender = new PETestSender("TestSender");
//    PROCESSORS_MAP[testSender->getName()] = 0;
//    PETestReceiver *testReceiver = new PETestReceiver("TestReceiver");
//    PROCESSORS_MAP[testReceiver->getName()] = 1;

//    PETestSenderFrontEnd *testSenderShell = new PETestSenderFrontEnd("TestSenderFrontEnd");
//    NetworkInterface *ni = networkInterfaces.at(0);
//    ni->connectFrontEnd(testSenderShell);

//    PETestReceiverFrontEnd *testReceiverShell = new PETestReceiverFrontEnd("TestReceiverFrontEnd");
//    ni = networkInterfaces.at(1);
//    ni->connectFrontEnd(testReceiverShell);

//    sc_fifo<char> *senderFifo = new sc_fifo<char>(1);
//    sc_fifo<char> *receiverFifo = new sc_fifo<char>(1);

//    testSender->fifoOutput(*senderFifo);
//    testSenderShell->fifoInput(*senderFifo);
//    testReceiver->fifoInput(*receiverFifo);
//    testReceiverShell->fifoOutput(*receiverFifo);

    ChannelTester channelTester1("ChannelTester1", 0, true);
    ChannelTester channelTester2("ChannelTester2", 1, false);

    RouterChannel channel("RouterChannelTest1");
    channelTester1.channel(channel);
    channelTester2.channel(channel);
#else

#endif //NOC_CONNECTION_TEST

    // Channels or Links
    std::vector<RouterChannel *> routerChannels;

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
			NoCDebug::printDebug(std::string("Connect R" + std::to_string(i) + " to R" + std::to_string(sourceA) + " from West"), NoCDebug::Assembly);
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
			NoCDebug::printDebug(std::string("Connect R" + std::to_string(i) + " to R" + std::to_string(sourceB) + " from North"), NoCDebug::Assembly);		
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
    sc_start();

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
        routerSource.westChannel(channel);
        routerDestination.eastChannel(channel);
    } else {
        routerSource.southChannel(channel);
        routerDestination.northChannel(channel);
    }
}
