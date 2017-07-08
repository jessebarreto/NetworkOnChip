#include "peslave.h"

#include "nocdebug.h"

ProcessorElementSlave::ProcessorElementSlave(sc_module_name name, char letter) :
    _send(letter)
{
    _name = this->basename();
    NoCDebug::printDebug(std::string("> Slave: " + _name), NoCDebug::Assembly);
    SC_THREAD(_threadRun);
}

void ProcessorElementSlave::_threadRun()
{
    for (;;) {
        int read = slaveIn.read();
        NoCDebug::printDebug(std::string(_name + ": Slave <- SShell       DATA: " + std::to_string(read)), NoCDebug::PE);
        NoCDebug::printDebug(std::string(_name + ": Slave -> SShell"), NoCDebug::PE);
        slaveOut.write(_send++);
    }
}
