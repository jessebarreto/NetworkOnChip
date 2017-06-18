#ifndef PETESTRECEIVERFRONTEND_H
#define PETESTRECEIVERFRONTEND_H

#include "networkinterfacefrontendbase.h"

class PETestReceiverFrontEnd : public sc_module, public NetworkInterfaceFrontEndBase
{
    SC_HAS_PROCESS(PETestReceiverFrontEnd);

    void _threadRun();

public:
    //IO
    sc_fifo_out<char> fifoOutput;

    PETestReceiverFrontEnd(sc_module_name name);
};

#endif // PETESTRECEIVERFRONTEND_H
