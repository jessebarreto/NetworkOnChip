#ifndef NOCASSEMBLER_H
#define NOCASSEMBLER_H

#include <vector>

#include "router.h"
#include "routerchannel.h"
#include "networkinterface.h"

#include "pemaster.h"
#include "pemastershell.h"
#include "peslave.h"
#include "peslaveshell.h"
#include "penull.h"
#include "penullshell.h"

/*!
 * \brief Connect a pair of routers.
 * \param routerSource The source router.
 * \param routerDestination The destination router.
 * \param channel The channel that will be used to connect both routers.
 * \param direction The direction of this connection. (Horizontal = true, Vertical = false)
 */
void connectRouters(Router &routerSource, Router &routerDestination, RouterChannel &inputChannel,
                    RouterChannel &outputChannel, bool direction);

/*!
 * \brief Connect the empty channels of a router, i.e., channels that were not connected before.
 * \param router The router that will have its channels connected.
 * \param routerId  The identity of this router.
 * \param channels NoC's vector of channels.
 */
void connectEmptyChannels(Router *router, int routerId, std::vector<RouterChannel *> *inputChannels,
                          std::vector<RouterChannel *> *outputChannels);

/*!
 * \brief Connects the channels which were connected before and also connect null processor elements
 * to the empty network interfaces.
 * \param routers A vector of routers.
 * \param routerInputChannels A vector of input channels.
 * \param routerOutputChannels A vector of output channels.
 * \param networkInterfaces A vector of network interfaces.
 */
void connectStrayChannels(std::vector<Router *> &routers, std::vector<RouterChannel *> &routerInputChannels,
                          std::vector<RouterChannel *> &routerOutputChannels,
                          std::vector<NetworkInterface *> &networkInterfaces,
                          std::vector<ProcessorElementNull *> &processorElementsNull,
                          std::vector<ProcessorElementNullShell *> &processorElementNullShells);

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
void assembleNoC(const std::vector<Router *> &routers, std::vector<RouterChannel *> &routerInputChannels,
                 std::vector<RouterChannel *> &routerOutputChannels);

/*!
 * \brief Connects masters and slaves testers to the NoC.
 * \param networkInterfaces A vector of network interfaces.
 * \param processorElementMasters A vector of masters.
 * \param processorElementMasterShells A vector of master shells.
 * \param masterConnections A vector of FIFO pairs used to connect masters.
 * \param processorElementSlaves A vector of slaves.
 * \param processorElementSlaveShells A vector of slave shells.
 * \param slaveConnections A vector of FIFO pairs used to connect slaves.
 * \param masterPositions A vector of master positions.
 * \param slavePositions A vector of slave positions.
 * \param numberOfPairs A number of pairs of master and slave.
 * \param initialSlaveChar The initial char of all test slaves.
 */
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
                             char *initialSlaveChar);

#endif // NOCASSEMBLER_H
