/*
 * - shell_master_ni.h
 * 
* 
 * Created by José Adalberto F. Gualeve  on 13/07/15.
 *  Modified by Felipe Cabral e Eduardo Mesquita on 05/07/16.
 * Copyright 2015 - All rights reserved 
*/
#ifndef shell_master_ni_h
#define shell_master_ni_h

#include "systemc.h"
#include "noc_common.h"
#include "bitset"

SC_MODULE ( ShellMasterInterface ) {
        // to/from master ports
    sc_fifo_in<flit_t >
        wr_data_port,
        addr_port;
    sc_fifo_in<flit1_4t >
        cmd_port;
    sc_fifo_in<sc_uint<10> >
        burst_port;
    
    sc_fifo_out< flit_t >
        rd_data_port;
    sc_fifo_out< flit1_4t >
        wr_resp_port;
    
        // to/from kernel ports
    sc_fifo_out < flit_t > bufferPM_port;
    sc_fifo_in  < flit_t > bufferPD_port;

	flit1_4t identify_tab( flit_t );
    void proc();
    
    SC_HAS_PROCESS( ShellMasterInterface );
    ShellMasterInterface (
        sc_module_name _name,
        flit1_4t identify
                          ):
    sc_module(_name), identify(identify) 
    {
        SC_THREAD(proc);
    }
  private:
    flit1_4t identify;
    
};

flit1_4t ShellMasterInterface::identify_tab( flit_t address ) 
{
    if ( address < 0x00010000 ) 
        return 2;                    // memory 0 (slave) (0 .. 64k-1)
    else if (address < 0x00100000 ) 
        return 3;                    // memory 1 (slave) (64k .. 1M-1)
    else if (address < 0x00200000 ) 
        return 4;                    // memory 2 (slave) (1M .. 2M-1 )
    else if (address < 0xFFFFF800 ) 
        return 5;                    // memory 3 (slave) (2M .. ~4G )
    else if (address < 0xFFFFFC00 ) 
        return 0;                    // cpu 0 (master) (512 bytes)
    else 
        return 1;                    // cpu 1 (master) (512 bytes + altos)
}


void ShellMasterInterface::proc() 
{
    flit1_4t cmd;
    flit_t data, address, nulo, header=0;
	sc_uint<10> burst;
    unsigned int i;
            
    for(;;) {
        
        data = 0;
            /*
             * send
             **/ 
        if ( ( cmd = cmd_port.read() ) & 8 )  // CMD_SB, CMD_SH or CMD_SW
            data = wr_data_port.read();
		if(debug>=1)
			cout << "["<< this->name() << "]: cmd read: " <<  std::hex << cmd << std::dec<<endl;
        address = addr_port.read();
		burst = burst_port.read();

		header.range(flit_size-1, flit_size-8) = identify;
		header.range(flit_size-9, flit_size-16) = identify_tab( address );
		header.range(flit_size-17, flit_size-22) = cmd;
		header.range(flit_size-23, flit_size-32) = burst;

		bufferPM_port.write(header);
		if (debug >= 1) 
			cout << "[" << this->name() << "]: " << "1 - header: " << std::hex << header << std::dec <<endl;
        bufferPM_port.write(address);
		if (debug >= 1) 
			cout << "[" << this->name() << "]: " << "2 - address: " << std::hex  << address << std::dec <<endl;
        bufferPM_port.write(data);
		if (debug >= 1) 
			cout << "[" << this->name() << "]: " << "3 - data: " << std::hex  << data << std::dec <<endl;
        
		for (i=2; i<burst; i++) 
            bufferPM_port.write(0);

            /*
             * receive
             **/ 
        
        header = bufferPD_port.read();
		data = bufferPD_port.read();
		burst = header.range(flit_size-23, flit_size-32);
		cmd = header.range(flit_size-17, flit_size-22);
        
		if (debug >= 1) 
			cout << "[" << this->name() << "]: " << "header received = " << std::hex  << header << std::dec << endl ;
        for (i=1; i<burst; i++) 
            nulo=bufferPD_port.read();
        if ( cmd & 8 )
            wr_resp_port.write((flit1_4t)data);
        else
            rd_data_port.write(data);
    }
    
}

#endif
