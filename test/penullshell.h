#ifndef PENULLSHELL_H
#define PENULLSHELL_H

#include <systemc.h>

#include "networkinterfacefrontendbase.h"

class ProcessorElementNullShell : public sc_module, public NetworkInterfaceFrontEndBase
{
    SC_HAS_PROCESS(ProcessorElementNullShell);

    void _threadRun();

    unsigned _position;

public:
    ProcessorElementNullShell(sc_module_name name, unsigned position);
};

#endif // PENULLSHELL_H
