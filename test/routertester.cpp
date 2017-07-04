
#include <systemc.h>

#include "master.h"
#include "mastershell.h"
#include "slave.h"
#include "slaveshell.h"
#include "flit.h"
#include "router.h"
#include "routerchannel.h"
#include "networkinterface.h"

int main()
{

    // PEs
    Master master("PEMaster");
    Slave slave("PESlave");

    // Shell
    MasterShell masterShell("MasterShell");
    SlaveShell slaveShell("SlaveShell");

    // Connect PE and Shell
    sc_fifo<int> slaveInt(2);
    sc_fifo<char> slaveChar(2);
    sc_fifo<int> masterInt(2);
    sc_fifo<char> masterChar(2);
    master.masterOut(masterInt);
    masterShell.shellIn(masterInt);
    masterShell.shellOut(masterChar);
    master.masterIn(masterChar);
    slaveShell.shellOut(slaveInt);
    slave.slaveIn(slaveInt);
    slave.slaveOut(slaveChar);
    slaveShell.shellIn(slaveChar);

    // Network Interfaces
    NetworkInterface niMaster("NIMaster", 0);
    NetworkInterface niSlave("NISlave", 1);

    // Connect Front-End
    niMaster.connectFrontEnd(&masterShell);
    niSlave.connectFrontEnd(&slaveShell);
    RouterChannel masterLocalChannel("MasterLocalChannel");
    niMaster.localChannel(masterLocalChannel);
    niSlave.localChannel(masterLocalChannel);

    // Connect Both Kernels Together
//    RouterChannel masterLocalChannel("MasterLocalChannel");
//    niMaster.localChannel(masterLocalChannel);
//    niSlave.localChannel(masterLocalChannel);

//    // Routers
//    Router routerMaster("RouterMaster", 0);
//    Router routerSlave("RouterSlave", 1);

//    // Router Channels
//    RouterChannel masterLocalChannel("MasterLocalChannel");
//    RouterChannel masterNorthChannel("MasterNorthChannel");
//    RouterChannel masterSouthChannel("MasterSouthChannel");
//    RouterChannel masterEastChannel("MasterEastChannel");
//    RouterChannel masterWestChannel("MasterWestChannel");
//    RouterChannel slaveLocalChannel("SlaveLocalChannel");
//    RouterChannel slaveNorthChannel("SlaveNorthChannel");
//    RouterChannel slaveSouthChannel("SlaveSouthChannel");
//    RouterChannel slaveEastChannel("SlaveEastChannel");
////    RouterChannel slaveWestChannel("SlaveWestChannel");

//    // Connect Routers and Router Channels
//    routerMaster.localChannel(masterLocalChannel);
//    routerMaster.northChannel(masterNorthChannel);
//    routerMaster.southChannel(masterSouthChannel);
//    routerMaster.eastChannel(masterEastChannel);
//    routerMaster.westChannel(masterWestChannel);
//    routerSlave.localChannel(slaveLocalChannel);
//    routerSlave.northChannel(slaveNorthChannel);
//    routerSlave.southChannel(slaveSouthChannel);
//    routerSlave.eastChannel(slaveEastChannel);
//    routerSlave.westChannel(masterEastChannel); // Connection

//    // Connect Routers and NI
//    niMaster.localChannel(masterLocalChannel);
//    niSlave.localChannel(slaveLocalChannel);

    // Run Simulation
    sc_start();
    return 0;
}

