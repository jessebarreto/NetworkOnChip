#include "slave.h"

Slave::Slave(sc_module_name name)
{
    _send = 'I';

    SC_THREAD(_threadRun);
}

void Slave::_threadRun()
{
    for (;;) {
        int read = slaveIn.read();
        std::cout << " SLendo: " <<  read << std::endl;;
        std::cout << " SEscrevendo: " << std::endl;;
        slaveOut.write(_send);
    }
}
