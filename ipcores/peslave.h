#ifndef SLAVE_H
#define SLAVE_H

#include <systemc.h>

class Slave : public sc_module
{
    SC_HAS_PROCESS(Slave);

    char _send;

    void _threadRun();

public:
    Slave(sc_module_name name);

    // IO
    sc_fifo_out<char> slaveOut;
    sc_fifo_in<int> slaveIn;
};

#endif // SLAVE_H
