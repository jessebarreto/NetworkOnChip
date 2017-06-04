/*
 * - master.h
 * 
 * 
 * Created by José Adalberto F. Gualeve  on 07/07/15.
 *  Modified by Felipe Cabral e Eduardo Mesquita on 05/07/16.
 * Copyright 2015 - All rights reserved 
 */
#ifndef master_h
#define master_h

#include "systemc.h"
#include "noc_common.h"

SC_MODULE(Master)
{
    sc_fifo_out< flit_t >
        wr_data_port,
        addr_port;
    sc_fifo_out<sc_uint<8> >
        cmd_port;
    sc_fifo_out<sc_uint<10> >
        burst_port;

    sc_fifo_in< flit_t >
        rd_data_port;
    sc_fifo_in<sc_uint<8> >
        wr_resp_port;

    SC_HAS_PROCESS(Master);
// constructor
  Master(sc_module_name _name, unsigned int identify) :
    sc_module(_name),
        identify(identify)
        {
            SC_THREAD(test_master);
            
        }
    void test_master();
  private:
    unsigned int identify;
    
    
};

void Master::test_master() 
{
    flit_t data, address0, address1, address2, address3;
    sc_uint<10> burst;

    address0 = 0x00001000; // Slave at node 2
    address1 = 0x00090000; // Slave at node 3
    address2 = 0x00100000; // Slave at node 4
    address3 = 0x00300000; // Slave at node 5
    switch (identify) {
        case  0:
          
                //WRITING 1st VALUE
            data = 0x00000010;
            if (debug >= 1) cout << "[Master0]: will send 1st value ("<<data<<") for writing at Slave0"<<endl<<endl;
            burst= 0x002;
                //passo("m0",0);
            wr_data_port.write( data );
                //passo("m0,wr_data_port.write",1);
            cmd_port.write( CMD_SW ); // store word
                //passo("m0,cmd_port.write",1);
            addr_port.write( address0 );
                //passo("m0,addr_port.write",1);
            burst_port.write(burst);
            if ( wr_resp_port.read() == 1 )
                if (debug >= 1) cout << "[Master0]: Write OK 1" << endl<<endl;
                else
                    if (debug >= 1) cout << "[Master0]: Write error 1" << endl<<endl;
                //passo("m0,wr_resp_port.read",2);
			
                //READING VALUE WRITTEN BEFORE
            if (debug >= 1) cout <<"[Master0]: will read the value from memory written before"<<endl<<endl;
            burst= 0x001;
            cmd_port->write( CMD_LW );
            addr_port->write( address0 );
            burst_port.write( burst );
            data = rd_data_port->read();
            if (debug >= 1) cout << "[Master0]: Result = " << data << endl<<endl;

                //WRITING 2nd VALUE

            data = 0x00000020;//32 em inteiro
            if (debug >= 1) cout << "[Master0]: will send 2nd value ("<<data<<") for writing at Slave0"<<endl<<endl;
            burst= 0x002;
            wr_data_port.write( data );
            cmd_port.write( CMD_SW ); // store word
            addr_port.write( address0 );
            burst_port.write(burst);
            if ( wr_resp_port.read() == 1 )
                if (debug >= 1) cout << "[Master0]: Write OK 2" << endl<<endl;
                else
                    if (debug >= 1) cout << "[Master0]: Write error 2" << endl<<endl;
			
            break;
            
        case 1:
            
                //WRITING 1st VALUE
            data = 0x00000012;
            if (debug >= 1) cout << "[Master1]: will send 1st value ("<<data<<") for writing at Slave0"<<endl<<endl;
            burst= 0x002;
                //passo("m0",0);
            wr_data_port.write( data );
                //passo("m0,wr_data_port.write",1);
            cmd_port.write( CMD_SW ); // store word
                //passo("m0,cmd_port.write",1);
            addr_port.write( address3 );
                //passo("m0,addr_port.write",1);
            burst_port.write(burst);
            if ( wr_resp_port.read() == 1 )
                if (debug >= 1) cout << "[Master1]: Write OK 1" << endl<<endl;
                else
                    if (debug >= 1) cout << "[Master1]: Write error 1" << endl<<endl;
                //passo("m0,wr_resp_port.read",2);
                //READING VALUE WRITTEN BEFORE
            if (debug >= 1) cout <<"[Master1]: will read the value from memory written before"<<endl<<endl;
            burst= 0x001;
            cmd_port->write( CMD_LW );
            addr_port->write( address3 );
            burst_port.write( burst );
            data = rd_data_port->read();
            if (debug >= 1) cout << "[Master1]: Result = " << data << endl<<endl;

                //WRITING 2nd VALUE
            data = 0x00000022;//32 em inteiro
            if (debug >= 1) cout << "[Master1]: will send 2nd value ("<<data<<") for writing at Slave0"<<endl<<endl;
            burst= 0x002;
            wr_data_port.write( data );
            cmd_port.write( CMD_SW ); // store word
            addr_port.write( address3 );
            burst_port.write(burst);
            if ( wr_resp_port.read() == 1 )
                if (debug >= 1) cout << "[Master1]: Write OK 2" << endl<<endl;
                else
                    if (debug >= 1) cout << "[Master1]: Write error 2" << endl<<endl;
            break;
    }

}

#endif
