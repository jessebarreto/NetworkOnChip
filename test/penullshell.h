#ifndef PENULLSHELL_H
#define PENULLSHELL_H

#include <systemc.h>

#include "networkinterfacefrontendbase.h"

class ProcessorElementNullShell : public sc_module, public NetworkInterfaceFrontEndBase
{
    SC_HAS_PROCESS(ProcessorElementNullShell);

    std::string _name;

public:
    ProcessorElementNullShell(sc_module_name name);
};

#endif // PENULLSHELL_H
