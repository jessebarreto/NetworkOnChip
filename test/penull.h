#ifndef PENULL_H
#define PENULL_H

#include <systemc.h>

class ProcessorElementNull : public sc_module
{
    SC_HAS_PROCESS(ProcessorElementNull);
    std::string _name;
public:
    ProcessorElementNull(sc_module_name name);
};

#endif // PENULL_H
