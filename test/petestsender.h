#ifndef PETESTSENDER_H
#define PETESTSENDER_H

#include <systemc.h>

#include "noccommon.h"

class PETestSender : public sc_module
{
    SC_HAS_PROCESS(PETestSender);

    std::string _message;

    void _threadRun();

public:
    // IO
    sc_fifo_out<char> fifoOutput;

    PETestSender(sc_module_name name);

    const std::__cxx11::string &getMessage();

    const std::__cxx11::string getName();
};

#endif // PETESTSENDER_H
