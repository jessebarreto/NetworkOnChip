#ifndef PESLAVE_H
#define PESLAVE_H

#include <systemc.h>

class ProcessorElementSlave : public sc_module
{
    SC_HAS_PROCESS(ProcessorElementSlave);

    char _send;

    unsigned _position, _masterPosition;

    void _threadRun();

public:
    ProcessorElementSlave(sc_module_name name, unsigned position, unsigned masterPosition, char letter);

    // IO
    sc_fifo_out<char> slaveOut;
    sc_fifo_in<int> slaveIn;
};

#endif // PESLAVE_H
