#ifndef PETESTRECEIVER_H
#define PETESTRECEIVER_H

#include <systemc.h>

#include "noccommon.h"

class PETestReceiver : public sc_module
{
    SC_HAS_PROCESS(PETestReceiver);

    std::string _message;

    void _threadRun();

public:
    // IO
    sc_fifo_in<char> fifoInput;

    PETestReceiver(sc_module_name name);

    const std::__cxx11::string getName();

    const std::string &getMessage();
};

#endif // PETESTRECEIVER_H
