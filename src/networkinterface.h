#ifndef NETWORKINTERFACE_H
#define NETWORKINTERFACE_H

#include <systemc.h>

#include "noccommon.h"
#include "routerchannel.h"
#include "inetworkinterfacefrontend.h"

/*!
 * \brief The NetworkInterface class is responsible for connecting a Processor element to its router which are connect
 * to the Network. It works basically as a connection element between the PE and the NoC.
 */
class NetworkInterface : public sc_module
{
    SC_HAS_PROCESS(NetworkInterface);

    /*!
     * \brief Unique identifier for this Network Interface.
     */
    const unsigned _networkInterfaceId;

    /*!
     * \brief The wrapper between the PE and the common implmented Network Interface.
     */
    INetworkInterfaceFrontEnd* _frontEnd;

    std::vector<Flit> _sendPacket;

    std::vector<Flit> _receivePacket;

    void _threadRead();

    void _threadWrite();

    void _packetMessage(const std::vector<unsigned> &message);

    const std::vector<unsigned> &_unpackMessage();

    void _sendToRouter();

    void _receiveFromRouter();

public:
    // IO
    sc_port<RouterChannel> localChannel;    

    NetworkInterface(sc_module_name name, unsigned id);

    void connectFrontEnd(INetworkInterfaceFrontEnd *networkInterfaceFrontEnd);
};

#endif // NETWORKINTERFACE_H
