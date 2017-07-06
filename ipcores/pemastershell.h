#ifndef PEMASTERSHELL_H
#define PEMASTERSHELL_H

#include <systemc.h>

#include "networkinterfacefrontendbase.h"

class MasterShell : public sc_module, public NetworkInterfaceFrontEndBase
{
    SC_HAS_PROCESS(MasterShell);

    void _threadRun();

public:
    // IO
    sc_fifo_in<int> shellIn;
    sc_fifo_out<char> shellOut;

    MasterShell(sc_module_name name);
};

#endif // PEMASTERSHELL_H
