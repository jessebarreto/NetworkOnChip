#include "slave.h"

#include "nocdebug.h"

Slave::Slave(sc_module_name name)
{
    _send = 'A';

    SC_THREAD(_threadRun);
}

void Slave::_threadRun()
{
    for (;;) {
        int read = slaveIn.read();
        NoCDebug::printDebug("Slave <- SShell       DATA: " + std::to_string(read), NoCDebug::PE);
        NoCDebug::printDebug("Slave -> SShell", NoCDebug::PE);
        slaveOut.write(_send++);
    }
}
