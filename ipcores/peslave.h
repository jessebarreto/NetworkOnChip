#ifndef PESLAVE_H
#define PESLAVE_H

#include <systemc.h>

class ProcessorElementSlave : public sc_module
{
    SC_HAS_PROCESS(ProcessorElementSlave);

    char _send;

    void _threadRun();

public:
    ProcessorElementSlave(sc_module_name name);

    // IO
    sc_fifo_out<char> slaveOut;
    sc_fifo_in<int> slaveIn;
};

#endif // PESLAVE_H
