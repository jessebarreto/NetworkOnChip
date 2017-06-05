#ifndef NETWORKINTERFACE_H
#define NETWORKINTERFACE_H

#include <systemc.h>

#include "noc_common.h"
#include "routerchannel.h"

class NetworkInterface : public sc_module
{
    SC_HAS_PROCESS(NetworkInterface);

public:
    // IO
    sc_port<RouterChannel> localChannel;

    NetworkInterface(sc_module_name name);
};

#endif // NETWORKINTERFACE_H
