#include "nocassembler.h"

#include <string>

#include "noccommon.h"
#include "nocdebug.h"

void connectRouters(Router &routerSource, Router &routerDestination, RouterChannel &inputChannel,
                    RouterChannel &outputChannel, bool direction)
{
    if (direction) {
        routerSource.eastChannelIn(inputChannel);
        routerDestination.westChannelOut(inputChannel);
        routerSource.eastChannelOut(outputChannel);
        routerDestination.westChannelIn(outputChannel);
    } else {
        routerSource.southChannelIn(inputChannel);
        routerDestination.northChannelOut(outputChannel);
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
        return;
    }
    std::string channelBaseName = std::string("RouterChannelEmpty_") + std::to_string(routerId) + std::string("_");
    RouterChannel *inputChannel, *outputChannel;
    if (isNorthDisconnected) {
        inputChannel = new RouterChannel(std::string(channelBaseName + std::to_string(Link::North) + "_Input").c_str());
        outputChannel = new RouterChannel(std::string(channelBaseName + std::to_string(Link::North) + "_Output").c_str());
        router->northChannelIn(*inputChannel);
        router->northChannelOut(*outputChannel);
        inputChannels->push_back(inputChannel);
    }

    if (isSouthDisconnected) {
        inputChannel = new RouterChannel(std::string(channelBaseName + std::to_string(Link::South) + "_Input").c_str());
        outputChannel = new RouterChannel(std::string(channelBaseName + std::to_string(Link::South) + "_Output").c_str());
        router->southChannelIn(*inputChannel);
        router->southChannelOut(*outputChannel);
        inputChannels->push_back(inputChannel);
        outputChannels->push_back(outputChannel);
    }

    if (isEastDisconnected) {
        inputChannel = new RouterChannel(std::string(channelBaseName + std::to_string(Link::East) + "_Input").c_str());
        outputChannel = new RouterChannel(std::string(channelBaseName + std::to_string(Link::East) + "_Output").c_str());
        router->eastChannelIn(*inputChannel);
        router->eastChannelOut(*outputChannel);
        inputChannels->push_back(inputChannel);
        outputChannels->push_back(outputChannel);
    }

    if (isWestDisconnected) {
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
            RouterChannel *inputChannel = new RouterChannel(std::string(routerChannelName + "_Input").c_str());
            RouterChannel *outputChannel = new RouterChannel(std::string(routerChannelName + "_Output").c_str());
            connectRouters(*routers.at(sourceB), *routers.at(i), *inputChannel, *outputChannel, false);
            routerInputChannels.push_back(inputChannel);
            routerOutputChannels.push_back(outputChannel);
            NoCDebug::printDebug(std::string("> Connect R" + std::to_string(sourceB) + " to R" + std::to_string(i) + " from North"), NoCDebug::Assembly);
        }
    }
}

void connectStrayChannels(std::vector<Router *> &routers, std::vector<RouterChannel *> &routerInputChannels,
                          std::vector<RouterChannel *> &routerOutputChannels,
                          std::vector<NetworkInterface *> &networkInterfaces)
{
    NoCDebug::printDebug(std::string("Connect Straw Channels and NIs"), NoCDebug::Assembly);
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
    }
}
