#ifndef SLAVESHELL_H
#define SLAVESHELL_H

#include <systemc.h>

#include "networkinterfacefrontendbase.h"

class NocMemShell : public sc_module, public NetworkInterfaceFrontEndBase
{
    SC_HAS_PROCESS(NocMemShell);

    void _threadRun();

public:
    // IO
    sc_fifo_in<int> memshellIn;
    sc_fifo_out<int> memshellOut;

    NocMemShell(sc_module_name name);
};

#endif // SLAVESHELL_H
