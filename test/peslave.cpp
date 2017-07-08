#include "peslave.h"

#include "nocdebug.h"

ProcessorElementSlave::ProcessorElementSlave(sc_module_name name, unsigned position, unsigned masterPosition, char letter) :
    _position(position),
    _masterPosition(masterPosition),
    _send(letter)
{
    NoCDebug::printDebug(std::string("> Slave: S" + std::to_string(_position) + "M" + std::to_string(_masterPosition)), NoCDebug::Assembly);
    SC_THREAD(_threadRun);

}

void ProcessorElementSlave::_threadRun()
{
    for (;;) {
        int read = slaveIn.read();
        NoCDebug::printDebug("S" + std::to_string(_position) + "M" + std::to_string(_masterPosition) + ": Slave <- SShell       DATA: " + std::to_string(read), NoCDebug::PE);
        NoCDebug::printDebug("S" + std::to_string(_position) + "M" + std::to_string(_masterPosition) + ": Slave -> SShell", NoCDebug::PE);
        slaveOut.write(_send++);
    }
}
