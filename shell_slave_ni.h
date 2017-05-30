/*
 * - shell_slave_ni.h
 * 
* 
 * Created by José Adalberto F. Gualeve  on 13/07/15.
 *  Modified by Felipe Cabral e Eduardo Mesquita on 05/07/16.
 * Copyright 2015 - All rights reserved 
*/
#ifndef shell_slave_ni_h
#define shell_slave_ni_h

#include "systemc.h"

#include "bitset"

SC_MODULE ( ShellSlaveInterface ) {
        // to slave ports
    sc_fifo_out< flit_t >
        wr_data_port,
        addr_port;
    sc_fifo_out< flit1_4t >
        cmd_port;
  //  sc_fifo_out<sc_uint<10> >
		//burst_port;

    sc_fifo_in< flit_t >
        rd_data_port;
    sc_fifo_in< flit1_4t >
        wr_resp_port;
    
        // to kernel ports
    sc_fifo_out < flit_t > bufferPM_port;
    sc_fifo_in  < flit_t > bufferPD_port;
    
    void proc();
    
    SC_HAS_PROCESS( ShellSlaveInterface );
    ShellSlaveInterface (
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

void ShellSlaveInterface::proc() 
{
    flit_t header, data, address, nulo; // header = source+dest+command+burst
    flit1_4t tmp;
	sc_uint<10> burst;
	flit1_4t cmd;
    
    for(;;) {
        
        header = bufferPD_port.read();
		burst = header.range(flit_size-23, flit_size-32);
		cmd =   header.range(flit_size-17, flit_size-22);
        address = bufferPD_port.read();
        data  = bufferPD_port.read();

        for (unsigned int i=2; i<burst; i++)
            nulo = bufferPD_port.read();
        
        
        if ( cmd & 8 )  { // CMD_SB, CMD_SH or CMD_SW
            wr_data_port.write(data);
        }
        
        addr_port.write(address);
        cmd_port.write(cmd);

        data = ( (cmd & 8) ? (flit_t)wr_resp_port.read() : rd_data_port.read() );
        
            // inverter source / dest para retornar
		if(debug>=1)
			cout << "[" << this->name() << "]: " << "Header original " << std::hex << (header)<< std::dec << endl;
        
        tmp = header.range(31,24);
        header.range(31,24) = header.range(23,16);
        header.range(23,16) = tmp;
        if (debug >= 1) 
			cout << "[" << this->name() << "]: " << "Header alterado " << std::hex << (header) << std::dec << endl;

		burst = 0x001;
		header.range(flit_size-23, flit_size-32)= burst;
        bufferPM_port.write(header);
//        bufferPM_port.write(address);  // descomentar se o kernel não diferenciar entre slave e master
        bufferPM_port.write(data);
        for (unsigned int i=1; i< burst; i++)
            bufferPM_port.write(0);
        
    }
    
}

#endif
