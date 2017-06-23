#ifndef CHANNELTESTER_H
#define CHANNELTESTER_H

#include <systemc.h>

#include "noccommon.h"
#include "routerchannel.h"
#include "flit.h"

class ChannelTester : public sc_module
{
    SC_HAS_PROCESS(ChannelTester);

    void _runThread();

    bool _begin;

    Flit *_innerFlit;

    int _packetCounter;

    int _0ID;
public:
    // IO Port
    sc_port<RouterChannel> channel;

    ChannelTester(sc_module_name name, int id, bool begin);
};

#endif // CHANNELTESTER_H
