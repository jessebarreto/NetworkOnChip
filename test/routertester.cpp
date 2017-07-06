
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

    // Routers
    Router routerMaster("RouterMaster", 0);
    Router routerSlave("RouterSlave", 1);

    // Router Channels In
    RouterChannel masterLocalChannelIn("MasterLocalChannelIn");
    RouterChannel masterNorthChannelIn("MasterNorthChannelIn");
    RouterChannel masterSouthChannelIn("MasterSouthChannelIn");
    RouterChannel masterEastChannelIn("MasterEastChannelIn");
    RouterChannel masterWestChannelIn("MasterWestChannelIn");
    RouterChannel slaveLocalChannelIn("SlaveLocalChannelIn");
    RouterChannel slaveNorthChannelIn("SlaveNorthChannelIn");
    RouterChannel slaveSouthChannelIn("SlaveSouthChannelIn");
    RouterChannel slaveEastChannelIn("SlaveEastChannelIn");
    RouterChannel slaveWestChannelIn("SlaveWestChannelIn");

    // Router Channels Out
    RouterChannel masterLocalChannelOut("MasterLocalChannelOut");
    RouterChannel masterNorthChannelOut("MasterNorthChannelOut");
    RouterChannel masterSouthChannelOut("MasterSouthChannelOut");
    RouterChannel masterEastChannelOut("MasterEastChannelOut");
    RouterChannel masterWestChannelOut("MasterWestChannelOut");
    RouterChannel slaveLocalChannelOut("SlaveLocalChannelOut");
    RouterChannel slaveNorthChannelOut("SlaveNorthChannelOut");
    RouterChannel slaveSouthChannelOut("SlaveSouthChannelOut");
    RouterChannel slaveEastChannelOut("SlaveEastChannelOut");
    RouterChannel slaveWestChannelOut("SlaveWestChannelOut");

    // Connect Routers and Router Channels
    routerMaster.localChannelIn(masterLocalChannelIn);
    routerMaster.localChannelOut(masterLocalChannelOut);
    routerMaster.northChannelIn(masterNorthChannelIn);
    routerMaster.northChannelOut(masterNorthChannelOut);
    routerMaster.southChannelIn(masterSouthChannelIn);
    routerMaster.southChannelOut(masterSouthChannelOut);
    routerMaster.eastChannelIn(masterEastChannelIn);
    routerMaster.eastChannelOut(masterEastChannelOut);
    routerMaster.westChannelIn(masterWestChannelIn);
    routerMaster.westChannelOut(masterWestChannelOut);

    routerSlave.localChannelIn(slaveLocalChannelIn);
    routerSlave.localChannelOut(slaveLocalChannelOut);
    routerSlave.northChannelIn(slaveNorthChannelIn);
    routerSlave.northChannelOut(slaveNorthChannelOut);
    routerSlave.southChannelIn(slaveSouthChannelIn);
    routerSlave.southChannelOut(slaveSouthChannelOut);
    routerSlave.eastChannelIn(masterWestChannelOut); // Connection
    routerSlave.eastChannelOut(masterWestChannelIn);// Connection
    routerSlave.westChannelIn(slaveWestChannelIn);
    routerSlave.westChannelOut(slaveWestChannelOut);

    // Connect Routers and NI
    niMaster.localChannelIn(masterLocalChannelOut);
    niMaster.localChannelOut(masterLocalChannelIn);
    niSlave.localChannelOut(slaveLocalChannelIn);
    niSlave.localChannelIn(slaveLocalChannelOut);
//    niSlave.localChannelIn(masterWestChannelOut);
//    niSlave.localChannelOut(masterWestChannelIn);

    // Run Simulation
    sc_start();
    return 0;
}

