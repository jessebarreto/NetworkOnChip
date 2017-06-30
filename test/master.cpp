#include "master.h"

#include <string>

#include "nocdebug.h"

Master::Master(sc_module_name name) : sc_module(name)
{
    data = new int[5];
    data[0] = 1;
    data[1] = 10;
    data[2] = 100;
    data[3] = 1000;
    data[4] = 10000;

    SC_THREAD(_threadRun)
}

void Master::_threadRun()
{
    for (int cnt = 0;cnt < 5;cnt++) {
        NoCDebug::printDebug("Master -> MShell      DATA: " + std::to_string(data[cnt]), NoCDebug::PE);
        masterOut.write(data[cnt]);
        char read;
        masterIn.read(read);
        std::string msg("Master <- MShell      DATA: ");
        msg += read;
        NoCDebug::printDebug(msg, NoCDebug::PE);
    }
}
