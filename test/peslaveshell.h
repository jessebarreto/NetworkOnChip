#ifndef PESLAVESHELL_H
#define PESLAVESHELL_H

#include <systemc.h>

#include "networkinterfacefrontendbase.h"

class ProcessorElementSlaveShell : public sc_module, public NetworkInterfaceFrontEndBase
{
    SC_HAS_PROCESS(ProcessorElementSlaveShell);

    void _threadRun();

    unsigned _masterPosition;
    std::string _name;

public:
    // IO
    sc_fifo_in<char> shellIn;
    sc_fifo_out<int> shellOut;

    ProcessorElementSlaveShell(sc_module_name name, unsigned masterPosition);
};

#endif // PESLAVESHELL_H
