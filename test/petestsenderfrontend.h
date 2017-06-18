#ifndef PETESTSENDERFRONTEND_H
#define PETESTSENDERFRONTEND_H

#include "noccommon.h"
#include "networkinterfacefrontendbase.h"

class PETestSenderFrontEnd : public sc_module, public NetworkInterfaceFrontEndBase
{
    SC_HAS_PROCESS(PETestSenderFrontEnd);

    void _threadRun();

public:
    // IO
    sc_fifo_in<char> fifoInput;

    PETestSenderFrontEnd(sc_module_name name);
};

#endif // PETESTSENDERFRONTEND_H
