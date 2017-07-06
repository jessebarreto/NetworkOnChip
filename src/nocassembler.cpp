#include "nocassembler.h"

#include <string>

#include "noccommon.h"
#include "nocdebug.h"

void connectRouters(Router &routerSource, Router &routerDestination, RouterChannel &channel, bool direction)
{
    if (direction) {
        routerSource.westChannel(channel);
        routerDestination.eastChannel(channel);
    } else {
        routerSource.southChannel(channel);
        routerDestination.northChannel(channel);
    }
}

void connectEmptyChannels(Router *router, int routerId, std::vector<RouterChannel *> *channels)
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

void assembleNoC(std::vector<Router *> &routers, std::vector<RouterChannel *> &routerChannels)
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

void connectStrayChannels(std::vector<Router *> &routers, std::vector<RouterChannel *> &routerChannels,
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
