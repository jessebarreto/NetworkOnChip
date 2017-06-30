#ifndef SLAVESHELL_H
#define SLAVESHELL_H

#include <systemc.h>

#include <networkinterfacefrontendbase.h>

class SlaveShell : public sc_module, public NetworkInterfaceFrontEndBase
{
    SC_HAS_PROCESS(SlaveShell);

    void _threadRun();

public:
    // IO
    sc_fifo_in<char> shellIn;
    sc_fifo_out<int> shellOut;

    SlaveShell(sc_module_name name);
};

#endif // SLAVESHELL_H
