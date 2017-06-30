
#include <systemc.h>

#include "master.h"
#include "mastershell.h"
#include "slave.h"
#include "slaveshell.h"
#include "specialkernel.h"


int main()
{
    Master master("PEMaster");
    MasterShell masterShell("MasterShell");
    sc_fifo<int> *masterIntFifo = new sc_fifo<int>(1);
    sc_fifo<char> *masterCharFifo = new sc_fifo<char>(1);
    master.masterOut(*masterIntFifo);
    masterShell.shellIn(*masterIntFifo);
    masterShell.shellOut(*masterCharFifo);
    master.masterIn(*masterCharFifo);

    Slave slave("PESlave");
    SlaveShell slaveShell("SlaveShell");
    sc_fifo<int> slaveIntFifo(1);
    sc_fifo<char> slaverCharFifo(1);
    slave.slaveOut(slaverCharFifo);
    slaveShell.shellIn(slaverCharFifo);
    slaveShell.shellOut(slaveIntFifo);
    slave.slaveIn(slaveIntFifo);

    SpecialKernel multKernel("specialKernel");
    multKernel.connectMaster(&masterShell);
    multKernel.connectSlave(&slaveShell);

    // Connection Test
//    sc_fifo<int> fifoInt;
//    sc_fifo<char> fifoChar;
//    master.masterOut(fifoInt);
//    slave.slaveIn(fifoInt);
//    slave.slaveOut(fifoChar);
//    master.masterIn(fifoChar);

    sc_start(sc_time(100, SC_SEC),  SC_RUN_TO_TIME);
    return 0;
}

