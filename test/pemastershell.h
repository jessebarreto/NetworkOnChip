#ifndef PEMASTERSHELL_H
#define PEMASTERSHELL_H

#include <systemc.h>

#include "networkinterfacefrontendbase.h"

class ProcessorElementMasterShell : public sc_module, public NetworkInterfaceFrontEndBase
{
    SC_HAS_PROCESS(ProcessorElementMasterShell);

    void _threadRun();

    unsigned _slavePosition;
    std::string _name;

public:
    // IO
    sc_fifo_in<int> shellIn;
    sc_fifo_out<char> shellOut;

    ProcessorElementMasterShell(sc_module_name name, unsigned slavePosition);
};

#endif // PEMASTERSHELL_H
