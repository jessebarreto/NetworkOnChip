/******************************************************************************************
 * Universidade de Brasília – UnB
 * Instituto de Ciências Exatas – IE
 * Departamento de Ciência da Computação – CIC
 * Modelagem de Sistemas em Silício – Professor R. Jacobi
 *
 * Projeto: Simple System-C NoC.
 *
 * Nome: Jessé Barreto de Barros, Javier Urresty Sanches, João Carlos Passos
 * Matrícula: 17/0067033
 * Copyright 2017 - All rights reserved
 ******************************************************************************************
*/

#include "nocassembler.h"

#include <string>

#include "noccommon.h"
#include "nocdebug.h"

void connectRouters(Router &routerDestination, Router &routerSource, RouterChannel &inputChannel,
                    RouterChannel &outputChannel, bool direction)
{
    if (direction) {
        routerSource.eastChannelIn(inputChannel);
        routerDestination.westChannelOut(inputChannel);
        routerSource.eastChannelOut(outputChannel);
        routerDestination.westChannelIn(outputChannel);
    } else {
        routerSource.southChannelIn(inputChannel);
        routerDestination.northChannelOut(inputChannel);
        routerSource.southChannelOut(outputChannel);
        routerDestination.northChannelIn(outputChannel);
    }
}

void connectEmptyChannels(Router *router, int routerId, std::vector<RouterChannel *> *inputChannels,
                          std::vector<RouterChannel *> *outputChannels)
{
    // Connect Straw Channels
    bool isNorthDisconnected = (router->northChannelIn.bind_count() == 0);
    bool isSouthDisconnected = (router->southChannelIn.bind_count() == 0);
    bool isEastDisconnected = (router->eastChannelIn.bind_count() == 0);
    bool isWestDisconnected = (router->westChannelIn.bind_count() == 0);

    if (!(isNorthDisconnected || isSouthDisconnected || isEastDisconnected || isWestDisconnected)) {
        NoCDebug::printDebug(std::string("Router_" + std::to_string(routerId) + ": None"), NoCDebug::Assembly);
        return;
    }
    std::string channelBaseName = std::string("RouterChannelEmpty_") + std::to_string(routerId) + std::string("_");
    RouterChannel *inputChannel, *outputChannel;
    if (isNorthDisconnected) {
        NoCDebug::printDebug(std::string("> Router_" + std::to_string(routerId) + ": North"), NoCDebug::Assembly);
        inputChannel = new RouterChannel(std::string(channelBaseName + std::to_string(Link::North) + "_Input").c_str());
        outputChannel = new RouterChannel(std::string(channelBaseName + std::to_string(Link::North) + "_Output").c_str());
        router->northChannelIn(*inputChannel);
        router->northChannelOut(*outputChannel);
        inputChannels->push_back(inputChannel);
    }

    if (isSouthDisconnected) {
        NoCDebug::printDebug(std::string("> Router_" + std::to_string(routerId) + ": South"), NoCDebug::Assembly);
        inputChannel = new RouterChannel(std::string(channelBaseName + std::to_string(Link::South) + "_Input").c_str());
        outputChannel = new RouterChannel(std::string(channelBaseName + std::to_string(Link::South) + "_Output").c_str());
        router->southChannelIn(*inputChannel);
        router->southChannelOut(*outputChannel);
        inputChannels->push_back(inputChannel);
        outputChannels->push_back(outputChannel);
    }

    if (isEastDisconnected) {
        NoCDebug::printDebug(std::string("> Router_" + std::to_string(routerId) + ": East"), NoCDebug::Assembly);
        inputChannel = new RouterChannel(std::string(channelBaseName + std::to_string(Link::East) + "_Input").c_str());
        outputChannel = new RouterChannel(std::string(channelBaseName + std::to_string(Link::East) + "_Output").c_str());
        router->eastChannelIn(*inputChannel);
        router->eastChannelOut(*outputChannel);
        inputChannels->push_back(inputChannel);
        outputChannels->push_back(outputChannel);
    }

    if (isWestDisconnected) {
        NoCDebug::printDebug(std::string("> Router_" + std::to_string(routerId) + ": West"), NoCDebug::Assembly);
        inputChannel = new RouterChannel(std::string(channelBaseName + std::to_string(Link::West) + "_Input").c_str());
        outputChannel = new RouterChannel(std::string(channelBaseName + std::to_string(Link::West) + "_Output").c_str());
        router->westChannelIn(*inputChannel);
        router->westChannelOut(*outputChannel);
        inputChannels->push_back(inputChannel);
        outputChannels->push_back(outputChannel);
    }
}

void assembleNoC(const std::vector<Router *> &routers, std::vector<RouterChannel *> &routerInputChannels,
                 std::vector<RouterChannel *> &routerOutputChannels)
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
            RouterChannel *inputChannel = new RouterChannel(std::string(routerChannelName + "_Input").c_str());
            RouterChannel *outputChannel = new RouterChannel(std::string(routerChannelName + "_Output").c_str());
            connectRouters(*routers.at(sourceA), *routers.at(i), *inputChannel, *outputChannel, true);
            routerInputChannels.push_back(inputChannel);
            routerOutputChannels.push_back(outputChannel);
            NoCDebug::printDebug(std::string("> Connect R" + std::to_string(sourceA) + " to R" + std::to_string(i) + " (West to East)"), NoCDebug::Assembly);
        }

        //Type B
        // 1. Check if isn't a topology in row
        // 2. Check if isn't the first row
        if (NOC_SIZE != NOC_ROW_SIZE && i >= NOC_ROW_SIZE) {
            //Source Index
            unsigned sourceB = i - NOC_ROW_SIZE;
            std::string routerChannelName("RouterChannel_");
            routerChannelName += std::to_string(sourceB) + "_" + std::to_string(i);
            RouterChannel *inputChannel = new RouterChannel(std::string(routerChannelName + "_Input").c_str());
            RouterChannel *outputChannel = new RouterChannel(std::string(routerChannelName + "_Output").c_str());
            connectRouters(*routers.at(sourceB), *routers.at(i), *inputChannel, *outputChannel, false);
            routerInputChannels.push_back(inputChannel);
            routerOutputChannels.push_back(outputChannel);
            NoCDebug::printDebug(std::string("> Connect R" + std::to_string(sourceB) + " to R" + std::to_string(i) + " (North to South)"), NoCDebug::Assembly);
        }
    }
}

void connectStrayChannels(std::vector<Router *> &routers, std::vector<RouterChannel *> &routerInputChannels,
                          std::vector<RouterChannel *> &routerOutputChannels,
                          std::vector<NetworkInterface *> &networkInterfaces,
                          std::vector<ProcessorElementNull *> &processorElementsNull,
                          std::vector<ProcessorElementNullShell *> &processorElementNullShells)
{
    NoCDebug::printDebug(std::string("Connect Straw Channels and NIs:"), NoCDebug::Assembly);
    for (int i = 0; i < NOC_SIZE; i++) {
        Router *router = routers.at(i);
        NetworkInterface *ni = networkInterfaces.at(i);
        RouterChannel *inputChannel = new RouterChannel(std::string("RouterChannel_" + std::to_string(i) + "_" +
                                                                     std::to_string(i) + "_Input").c_str());
        RouterChannel *outputChannel = new RouterChannel(std::string("RouterChannel_" + std::to_string(i) + "_" +
                                                                     std::to_string(i) + "_Output").c_str());
        router->localChannelIn(*inputChannel);
        ni->localChannelOut(*inputChannel);
        router->localChannelOut(*outputChannel);
        ni->localChannelIn(*outputChannel);

        connectEmptyChannels(router, i, &routerInputChannels, &routerOutputChannels);

        // Connect Empty NI to Null PE
        if (!ni->getFrontEndReference()) {
            ProcessorElementNull *nullPE =
                    new ProcessorElementNull(std::string("NullPE_" + std::to_string(processorElementsNull.size())).c_str(), i);
            ProcessorElementNullShell *nullPEShell =
                    new ProcessorElementNullShell(std::string("NullPEShell_" + std::to_string(processorElementNullShells.size())).c_str(), i);
            processorElementsNull.push_back(nullPE);
            processorElementNullShells.push_back(nullPEShell);
            ni->connectFrontEnd(nullPEShell);
        }
    }
}

void connectMastersAndSlaves(const std::vector<NetworkInterface *> &networkInterfaces,
                             std::vector<ProcessorElementMaster *> &processorElementMasters,
                             std::vector<ProcessorElementMasterShell *> &processorElementMasterShells,
                             std::vector<std::pair<sc_fifo<int> *, sc_fifo<char> *> > &masterConnections,
                             std::vector<ProcessorElementSlave *> &processorElementSlaves,
                             std::vector<ProcessorElementSlaveShell *> &processorElementSlaveShells,
                             std::vector<std::pair<sc_fifo<int> *, sc_fifo<char> *> > &slaveConnections,
                             const std::vector<int> &masterPositions,
                             const std::vector<int> &slavePositions,
                             int numberOfPairs,
                             char *initialSlaveChar)
{
    for (int i = 0; i < numberOfPairs; i++) {
        ProcessorElementMaster *master =
                new ProcessorElementMaster(std::string("Master_" + std::to_string(i)).c_str(),
                                           masterPositions.at(i),
                                           slavePositions.at(i));
        ProcessorElementMasterShell *masterShell =
                new ProcessorElementMasterShell(std::string("MasterShell_" + std::to_string(i)).c_str(),
                                                masterPositions.at(i),
                                                slavePositions.at(i));
        sc_fifo<int> *fifoMasterInt = new sc_fifo<int>();
        sc_fifo<char> *fifoMasterChar = new sc_fifo<char>();

        master->masterOut(*fifoMasterInt);
        masterShell->shellIn(*fifoMasterInt);
        masterShell->shellOut(*fifoMasterChar);
        master->masterIn(*fifoMasterChar);

        // Connect Front-End to NetworkInterface
        networkInterfaces.at(masterPositions.at(i))->connectFrontEnd(masterShell);
        processorElementMasters.push_back(master);
        processorElementMasterShells.push_back(masterShell);
        masterConnections.push_back(std::make_pair(fifoMasterInt, fifoMasterChar));

        ProcessorElementSlave *slave =
                new ProcessorElementSlave(std::string("Slave_" + std::to_string(processorElementSlaves.size())).c_str(),
                                           slavePositions.at(processorElementSlaves.size()),
                                           masterPositions.at(processorElementSlaves.size()), *initialSlaveChar);
        ProcessorElementSlaveShell *slaveShell =
                new ProcessorElementSlaveShell(std::string("SlaveShell_" + std::to_string(processorElementSlaveShells.size())).c_str(),
                                                slavePositions.at(processorElementSlaveShells.size()),
                                                masterPositions.at(processorElementSlaveShells.size()));
        *initialSlaveChar += 5;
        sc_fifo<int> *fifoSlaveInt = new sc_fifo<int>();
        sc_fifo<char> *fifoSlaveChar = new sc_fifo<char>();

        slaveShell->shellOut(*fifoSlaveInt);
        slave->slaveIn(*fifoSlaveInt);
        slave->slaveOut(*fifoSlaveChar);
        slaveShell->shellIn(*fifoSlaveChar);

        // Connect Front-End to NetworkInterface
        networkInterfaces.at(slavePositions.at(i))->connectFrontEnd(slaveShell);
        processorElementSlaves.push_back(slave);
        processorElementSlaveShells.push_back(slaveShell);
        slaveConnections.push_back(std::make_pair(fifoSlaveInt, fifoSlaveChar));
    }
}
