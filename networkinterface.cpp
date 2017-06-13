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

void NetworkInterface::_threadReadShell()
{
    for (;;) {
//        WAIT(Ready from shell);
        if (_frontEnd->getFrontEndReady()) {
            _frontEnd->getMessage();
            _frontEnd->sendDestiny();
        }
    }
}

void NetworkInterface::_threadWriteShell()
{

}

