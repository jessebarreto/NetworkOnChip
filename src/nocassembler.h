#ifndef NOCASSEMBLER_H
#define NOCASSEMBLER_H

#include <vector>

#include "router.h"
#include "routerchannel.h"
#include "networkinterface.h"

/*!
 * \brief Connect a pair of routers.
 * \param routerSource The source router.
 * \param routerDestination The destination router.
 * \param channel The channel that will be used to connect both routers.
 * \param direction The direction of this connection. (Horizontal = true, Vertical = false)
 */
void connectRouters(Router &routerSource, Router &routerDestination, RouterChannel &channel, bool direction);

/*!
 * \brief Connect the empty channels of a router, i.e., channels that were not connected before.
 * \param router The router that will have its channels connected.
 * \param routerId  The identity of this router.
 * \param channels NoC's vector of channels.
 */
void connectEmptyChannels(Router *router, int routerId, std::vector<RouterChannel *> *channels);

void connectStrayChannels(std::vector<Router *> &routers, std::vector<RouterChannel *> &routerChannels,
                                 std::vector<NetworkInterface *> &networkInterfaces);

// Assemble NoC Topology
//
// Type A - Horizontal Connection
//  Source Channel: East
//  Destination Channel: West
//
// Type B - Vertical Connection
//  Source Channel: South
//  Destination Channel: North
//
//		  B
//	      ||
//	      ||
//	A ===(Ri)
//
// New routers must be connected to their left-side and up-side routers
// Should them exist and respecting the topology
void assembleNoC(std::vector<Router *> &routers, std::vector<RouterChannel *> &routerChannels);

#endif // NOCASSEMBLER_H
