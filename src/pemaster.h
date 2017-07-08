#ifndef PEMASTER_H
#define PEMASTER_H

#include <systemc.h>

class ProcessorElementMaster : public sc_module
{
    SC_HAS_PROCESS(ProcessorElementMaster);

    int *data;

    unsigned _position, _slavePosition;

    void _threadRun();

public:
    ProcessorElementMaster(sc_module_name name, unsigned position, unsigned slavePosition);

    // IO
    sc_fifo_out<int> masterOut;
    sc_fifo_in<char> masterIn;
};

#endif // PEMASTER_H
