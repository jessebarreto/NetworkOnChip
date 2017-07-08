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
#include "pemaster.h"
#include "pemastershell.h"
#include "peslave.h"
#include "peslaveshell.h"
#include "penull.h"
#include "penullshell.h"

void connectProcessorElementToNoC(const std::vector<NetworkInterface *> &networkInterfaces,
                                  NetworkInterfaceFrontEndBase *shell, int position);
/*!
 * \brief Main Function
 */
int main(int argc, char *argv[])
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
    NoCDebug::printDebug(std::string("Adding PE Connections:"), NoCDebug::Assembly);
    std::vector<int> masterPositions = {0, 2, 4, 6};
    std::vector<int> slavePositions = {5, 3, 1, 15};
    int numberOfPairs = 4;

    std::vector<std::pair<sc_fifo<int> *, sc_fifo<char> *>> masterConnections;
    std::vector<std::pair<sc_fifo<int> *, sc_fifo<char> *>> slaveConnections;

    std::vector<ProcessorElementMaster *> processorMasterElements;
    std::vector<ProcessorElementMasterShell *> processorMasterElementShells;

    std::vector<ProcessorElementSlave *> processorSlaveElements;
    std::vector<ProcessorElementSlaveShell *> processorSlaveElementShells;

    char initialChar = 'A';
    connectMastersAndSlaves(networkInterfaces, processorMasterElements, processorMasterElementShells, masterConnections,
                            processorSlaveElements, processorSlaveElementShells, slaveConnections,
                            masterPositions, slavePositions, numberOfPairs, &initialChar);

    // Vector of Null Processor Elements
    std::vector<ProcessorElementNull *> processorNullElements;
    std::vector<ProcessorElementNullShell *> processorNullElementShell;
    /////////////////////////////////////////////////////////////////////////////

    // Channels or Links
    std::vector<RouterChannel *> routerInputChannels, routerOutputChannels;

    // Assemble NoC
    assembleNoC(routers, routerInputChannels, routerOutputChannels);

    // Stray Channels to the routers
    connectStrayChannels(routers, routerInputChannels, routerOutputChannels, networkInterfaces,
                         processorNullElements, processorNullElementShell);

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
