#include "networkinterface.h"

NetworkInterface::NetworkInterface(sc_module_name name, unsigned id) :
    sc_module(name),
    _networkInterfaceId(id)
{

}

void NetworkInterface::connectFrontEnd(INetworkInterfaceFrontEnd *networkInterfaceFrontEnd)
{
    _frontEnd = networkInterfaceFrontEnd;
}
