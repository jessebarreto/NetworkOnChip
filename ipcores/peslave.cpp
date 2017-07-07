#include "peslave.h"

#include "nocdebug.h"

ProcessorElementSlave::ProcessorElementSlave(sc_module_name name)
{
    _send = 'A';

    SC_THREAD(_threadRun);
}

void ProcessorElementSlave::_threadRun()
{
    for (;;) {
        int read = slaveIn.read();
        NoCDebug::printDebug("Slave <- SShell       DATA: " + std::to_string(read), NoCDebug::PE);
        NoCDebug::printDebug("Slave -> SShell", NoCDebug::PE);
        slaveOut.write(_send++);
    }
}
