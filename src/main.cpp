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
    ProcessorElementMaster masterPE("MasterPE"); ProcessorElementMasterShell masterPEShell("MasterPEShell", 0, 1);
    connectProcessorElementToNoC(networkInterfaces, &masterPEShell, 0);
    sc_fifo<int> masterIntFifo(16);
    sc_fifo<char> masterCharFifo(16);
    masterPE.masterOut(masterIntFifo);
    masterPEShell.shellIn(masterIntFifo);
    masterPE.masterIn(masterCharFifo);
    masterPEShell.shellOut(masterCharFifo);

    ProcessorElementSlave slave("PESlave", 'A'); ProcessorElementSlaveShell slaveShell("SlaveShell");
    connectProcessorElementToNoC(networkInterfaces, &slaveShell, 1);
    sc_fifo<int> slaveInt(2);
    sc_fifo<char> slaveChar(2);
    slaveShell.shellOut(slaveInt);
    slave.slaveIn(slaveInt);
    slave.slaveOut(slaveChar);
    slaveShell.shellIn(slaveChar);

    ProcessorElementMaster masterPE2("MasterPE2"); ProcessorElementMasterShell masterPEShell2("MasterPEShell2", 2, 3);
    connectProcessorElementToNoC(networkInterfaces, &masterPEShell2, 2);
    sc_fifo<int> masterIntFifo2(16);
    sc_fifo<char> masterCharFifo2(16);
    masterPE2.masterOut(masterIntFifo2);
    masterPEShell2.shellIn(masterIntFifo2);
    masterPE2.masterIn(masterCharFifo2);
    masterPEShell2.shellOut(masterCharFifo2);

    ProcessorElementSlave slave2("PESlave2", 'J'); ProcessorElementSlaveShell slaveShell2("SlaveShell2");
    connectProcessorElementToNoC(networkInterfaces, &slaveShell2, 3);
    sc_fifo<int> slaveInt2(2);
    sc_fifo<char> slaveChar2(2);
    slaveShell2.shellOut(slaveInt2);
    slave2.slaveIn(slaveInt2);
    slave2.slaveOut(slaveChar2);
    slaveShell2.shellIn(slaveChar2);

    ProcessorElementMaster masterPE3("MasterPE3"); ProcessorElementMasterShell masterPEShell3("MasterPEShell2", 4, 5);
    connectProcessorElementToNoC(networkInterfaces, &masterPEShell3, 4);
    sc_fifo<int> masterIntFifo3(16);
    sc_fifo<char> masterCharFifo3(16);
    masterPE3.masterOut(masterIntFifo3);
    masterPEShell3.shellIn(masterIntFifo3);
    masterPE3.masterIn(masterCharFifo3);
    masterPEShell3.shellOut(masterCharFifo3);

    ProcessorElementSlave slave3("PESlave3", 'T'); ProcessorElementSlaveShell slaveShell3("SlaveShell3");
    connectProcessorElementToNoC(networkInterfaces, &slaveShell3, 5);
    sc_fifo<int> slaveInt3(2);
    sc_fifo<char> slaveChar3(2);
    slaveShell3.shellOut(slaveInt3);
    slave3.slaveIn(slaveInt3);
    slave3.slaveOut(slaveChar3);
    slaveShell3.shellIn(slaveChar3);
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
