#ifndef PEMASTER_H
#define PEMASTER_H

#include <systemc.h>

class ProcessorElementMaster : public sc_module
{
    SC_HAS_PROCESS(ProcessorElementMaster);

    int *data;
    void _threadRun();
    std::string _name;

public:
    ProcessorElementMaster(sc_module_name name);

    // IO
    sc_fifo_out<int> masterOut;
    sc_fifo_in<char> masterIn;
};

#endif // PEMASTER_H
