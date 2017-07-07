#ifndef PENULL_H
#define PENULL_H

#include <systemc.h>

class ProcessorElementNull : public sc_module
{
    SC_HAS_PROCESS(ProcessorElementNull);

    unsigned _position;

    void _threadRun();

public:
    ProcessorElementNull(sc_module_name name, unsigned position);
};

#endif // PENULL_H
