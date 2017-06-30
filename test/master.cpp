#include "master.h"

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
        std::cout << "Master -> MShell - " << masterOut.num_attributes() << " - " << masterOut.num_free() << std::endl;
        masterOut.write(data[cnt]);
        std::cout << "      DATA: " <<  data[cnt] << " - " << masterOut.num_attributes() << " - " << masterOut.num_free() << std::endl;
        char read = masterIn.read();
        std::cout << "Master <- MShell" << std::endl;
        std::cout << cnt+1 << " MLendo: " <<  read << std::endl;
    }
}
