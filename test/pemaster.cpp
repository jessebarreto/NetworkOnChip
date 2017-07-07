#include "pemaster.h"

#include <string>

#include "nocdebug.h"

ProcessorElementMaster::ProcessorElementMaster(sc_module_name name, unsigned position, unsigned slavePosition) :
    sc_module(name),
  _position(position),
  _slavePosition(slavePosition)
{

    NoCDebug::printDebug(std::string("> Master: M" + std::to_string(_position) + "S" + std::to_string(_slavePosition)), NoCDebug::Assembly);
    data = new int[5];
    data[0] = 1;
    data[1] = 10;
    data[2] = 100;
    data[3] = 1000;
    data[4] = 10000;

    SC_THREAD(_threadRun)
}

void ProcessorElementMaster::_threadRun()
{
    for (int cnt = 0;cnt < 5;cnt++) {
        NoCDebug::printDebug("M" + std::to_string(_position) + "S" + std::to_string(_slavePosition) + ": Master -> MShell      DATA: " + std::to_string(data[cnt]), NoCDebug::PE);
        masterOut.write(data[cnt]);
        char read;
        masterIn.read(read);
        std::string msg("M" + std::to_string(_position) + "S" + std::to_string(_slavePosition) + ": Master <- MShell      DATA: ");
        msg += read;
        NoCDebug::printDebug(msg, NoCDebug::PE);
    }
}
