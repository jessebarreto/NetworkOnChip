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

// User Libraries
#include "noccommon.h"
#include "nocdebug.h"

#include "router.h"
#include "routerchannel.h"
#include "networkinterface.h"
#include "networkinterfacefrontendbase.h"
#include "nocassembler.h"
#include "nocrouting.h"

// PE Includes
#include "master.h"
#include "mastershell.h"
#include "slave.h"
#include "slaveshell.h"
//#include "ip-cores_srcs/simplemasterslave/pemastershell.h"
//#include "ip-cores_srcs/simplemasterslave/peslave.h"
//#include "ip-cores_srcs/simplemasterslave/peslaveshell.h"


void connectProcessorElementToNoC(const std::vector<NetworkInterface *> &networkInterfaces,
                                  NetworkInterfaceFrontEndBase *shell, int position);

/*!
 * \brief Main Function
 */
int sc_main(int argc, char *argv[])
{
    // Routers
    NoCDebug::printDebug(std::string("Adding Routers:"), NoCDebug::Assembly);
    std::vector<Router *> routers;
    for (unsigned i = 0; i < NOC_SIZE; i++) {
        std::string routerName("Router_");
        routerName += std::to_string(i);
        routers.push_back(new Router(routerName.c_str(), i));
        NoCDebug::printDebug(std::string("> " + routerName), NoCDebug::Assembly);
    }

    // Network Interfaces
    NoCDebug::printDebug(std::string("Adding Network Interfaces:"), NoCDebug::Assembly);
    std::vector<NetworkInterface *> networkInterfaces;
    for (unsigned i = 0; i < NOC_SIZE; i++) {
        std::string niName("NetworkInterface_");
        niName += std::to_string(i);
        networkInterfaces.push_back(new NetworkInterface(niName.c_str(), i));
        NoCDebug::printDebug(std::string("> " + niName), NoCDebug::Assembly);
    }

    /////////////////////////////////////////////////////////////////////////////
    // Processor Elements Connections
    Master masterPE("MasterPE"); MasterShell masterPEShell("MasterPEShell");
    connectProcessorElementToNoC(networkInterfaces, &masterPEShell, 0);
    sc_fifo<int> masterIntFifo(16);
    sc_fifo<char> masterCharFifo(16);
    masterPE.masterOut(masterIntFifo);
    masterPEShell.shellIn(masterIntFifo);
    masterPE.masterIn(masterCharFifo);
    masterPEShell.shellOut(masterCharFifo);

    Slave slave("PESlave"); SlaveShell slaveShell("SlaveShell");
    connectProcessorElementToNoC(networkInterfaces, &slaveShell, 1);
    sc_fifo<int> slaveInt(2);
    sc_fifo<char> slaveChar(2);
    slaveShell.shellOut(slaveInt);
    slave.slaveIn(slaveInt);
    slave.slaveOut(slaveChar);
    slaveShell.shellIn(slaveChar);
    /////////////////////////////////////////////////////////////////////////////

    // Channels or Links
    std::vector<RouterChannel *> routerInputChannels, routerOutputChannels;

    // Assemble NoC
    assembleNoC(routers, routerInputChannels, routerOutputChannels);

    // Stray Channels to the routers
    connectStrayChannels(routers, routerInputChannels, routerOutputChannels, networkInterfaces);

    // Start Simulation
    std::cout << "Start NoC Simulation..." << std::endl;
    sc_start();

    return 0;
}

void connectProcessorElementToNoC(const std::vector<NetworkInterface *> &networkInterfaces,
                                  NetworkInterfaceFrontEndBase *shell, int position)
{
    networkInterfaces.at(position)->connectFrontEnd(shell);
}
