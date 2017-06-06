#ifndef NETWORKINTERFACE_H
#define NETWORKINTERFACE_H

#include <systemc.h>

#include "noc_common.h"
#include "routerchannel.h"
#include "networkinterfacefrontend.h"

class NetworkInterface : public sc_module
{
    SC_HAS_PROCESS(NetworkInterface);

    const unsigned _networkInterfaceId;

    INetworkInterfaceFrontEnd* _frontEnd;

public:
    // IO
    sc_port<RouterChannel> localChannel;    

    NetworkInterface(sc_module_name name, unsigned id);

    void connectFrontEnd(INetworkInterfaceFrontEnd *networkInterfaceFrontEnd);
};

#endif // NETWORKINTERFACE_H
