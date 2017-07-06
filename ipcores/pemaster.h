#ifndef PEMASTER_H
#define PEMASTER_H

#include <systemc.h>

class Master : public sc_module
{
    SC_HAS_PROCESS(Master);

    int *data;

    void _threadRun();

public:
    Master(sc_module_name name);

    // IO
    sc_fifo_out<int> masterOut;
    sc_fifo_in<char> masterIn;
};

#endif // PEMASTER_H
