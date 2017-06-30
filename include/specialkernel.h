#ifndef SPECIALKERNEL_H
#define SPECIALKERNEL_H

#include <systemc.h>

#include "inetworkinterfacefrontend.h"


class SpecialKernel : public sc_module
{
    SC_HAS_PROCESS(SpecialKernel);

    INetworkInterfaceFrontEnd *_frontEndMaster;

    INetworkInterfaceFrontEnd *_frontEndSlave;

    void _threadConnectionMasterSlave();
public:
    SpecialKernel(sc_module_name name);

    void connectMaster(INetworkInterfaceFrontEnd *frontEndMaster);

    void connectSlave(INetworkInterfaceFrontEnd *frontEndSlave);
};

#endif // SPECIALKERNEL_H
