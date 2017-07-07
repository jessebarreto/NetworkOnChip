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
    //#1
    ProcessorElementMaster masterPE1("MasterPE1", 0, 5); ProcessorElementMasterShell masterPEShell1("MasterPEShell1", 0, 5);
    connectProcessorElementToNoC(networkInterfaces, &masterPEShell1, 0);
    sc_fifo<int> masterIntFifo1(16);
    sc_fifo<char> masterCharFifo1(16);
    masterPE1.masterOut(masterIntFifo1);
    masterPEShell1.shellIn(masterIntFifo1);
    masterPE1.masterIn(masterCharFifo1);
    masterPEShell1.shellOut(masterCharFifo1);

    ProcessorElementSlave slave1("PESlave1", 5, 0, 'A'); ProcessorElementSlaveShell slaveShell1("SlaveShell1", 5, 0);
    connectProcessorElementToNoC(networkInterfaces, &slaveShell1, 5);
    sc_fifo<int> slaveInt1(2);
    sc_fifo<char> slaveChar1(2);
    slaveShell1.shellOut(slaveInt1);
    slave1.slaveIn(slaveInt1);
    slave1.slaveOut(slaveChar1);
    slaveShell1.shellIn(slaveChar1);

    //ProcessorElementNull nullPE1("NullPE1", 1); ProcessorElementNullShell nullPEShell1("NullPEShell1", 1);
    //connectProcessorElementToNoC(networkInterfaces, &nullPEShell1, 1);

    ProcessorElementNull nullPE2("NullPE2", 2); ProcessorElementNullShell nullPEShell2("NullPEShell2", 2);
    connectProcessorElementToNoC(networkInterfaces, &nullPEShell2, 2);

    ProcessorElementNull nullPE3("NullPE3", 3); ProcessorElementNullShell nullPEShell3("NullPEShell3", 3);
    connectProcessorElementToNoC(networkInterfaces, &nullPEShell3, 3);

    //ProcessorElementNull nullPE4("NullPE4", 4); ProcessorElementNullShell nullPEShell4("NullPEShell4", 4);
    //connectProcessorElementToNoC(networkInterfaces, &nullPEShell4, 4);

    //#2
    ProcessorElementMaster masterPE2("MasterPE2", 4, 1); ProcessorElementMasterShell masterPEShell2("MasterPEShell2", 4, 1);
    connectProcessorElementToNoC(networkInterfaces, &masterPEShell2, 4);
    sc_fifo<int> masterIntFifo2(16);
    sc_fifo<char> masterCharFifo2(16);
    masterPE2.masterOut(masterIntFifo2);
    masterPEShell2.shellIn(masterIntFifo2);
    masterPE2.masterIn(masterCharFifo2);
    masterPEShell2.shellOut(masterCharFifo2);

    ProcessorElementSlave slave2("PESlave2", 1, 4, 'J'); ProcessorElementSlaveShell slaveShell2("SlaveShell2", 1, 4);
    connectProcessorElementToNoC(networkInterfaces, &slaveShell2, 1);
    sc_fifo<int> slaveInt2(2);
    sc_fifo<char> slaveChar2(2);
    slaveShell2.shellOut(slaveInt2);
    slave2.slaveIn(slaveInt2);
    slave2.slaveOut(slaveChar2);
    slaveShell2.shellIn(slaveChar2);


    /*

    //#3
    ProcessorElementMaster masterPE3("MasterPE3", 4, 5); ProcessorElementMasterShell masterPEShell3("MasterPEShell3", 4, 5);
    connectProcessorElementToNoC(networkInterfaces, &masterPEShell3, 4);
    sc_fifo<int> masterIntFifo3(16);
    sc_fifo<char> masterCharFifo3(16);
    masterPE3.masterOut(masterIntFifo3);
    masterPEShell3.shellIn(masterIntFifo3);
    masterPE3.masterIn(masterCharFifo3);
    masterPEShell3.shellOut(masterCharFifo3);

    ProcessorElementSlave slave3("PESlave3", 5, 4, 'T'); ProcessorElementSlaveShell slaveShell3("SlaveShell3", 5, 4);
    connectProcessorElementToNoC(networkInterfaces, &slaveShell3, 5);
    sc_fifo<int> slaveInt3(2);
    sc_fifo<char> slaveChar3(2);
    slaveShell3.shellOut(slaveInt3);
    slave3.slaveIn(slaveInt3);
    slave3.slaveOut(slaveChar3);
    slaveShell3.shellIn(slaveChar3);

    */

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
