/*
 * - Kernel_ni.cpp
 * 
* 
 * Created by José Adalberto F. Gualeve  on 08/07/15.
 *  Modified by Felipe Cabral on 05/07/16.
 * Copyright 2015 - All rights reserved 
*/

#include "systemc.h"
#include "kernel_ni.h"
#include "bitset"


void Kernel_ni::packetMaker() 
{
    int i;
    sc_uint<10> burst;


    if ( debug >=1 ) cout << "["<< this->name() << "::packetMaker] kernel id: " << identify << endl;
        
    for (;;) {
        
        queueOut[0] = bufferPM_port.read(); // Read 1st flit header (src + dest + cmd + burst)
		
        if ( debug >=1 ) cout << "["<< this->name() << "::packetMaker] bufferPM_port0: " <<std::hex << queueOut[0]<< std::dec<< endl;
		
		burst = queueOut[0].range(flit_size-23, flit_size-32);

        for (i = 1; i <= burst; i++) { // Read next flits
            queueOut[i] = bufferPM_port.read();

            if ( debug >=1 ) cout << "["<< this->name() << "::packetMaker] bufferPM_port"<<i<<": " <<std::hex << queueOut[i]<< std::dec<< endl;
        }            
        
        for (i = 0; i <= burst; i++) {
            o_kernel.write(queueOut[i]);

            if ( debug >=1 ) cout << "[" << this->name() << "::packetMaker]:<<<flit"<<i<<" sent: [" << std::hex << (queueOut[i])<< std::dec<<"]"<<endl;
                
        }

        
    }
        
}
    

void Kernel_ni::packetDisassembly() 
{
    int i;
    flit1_4t id;
    sc_uint<10> burst;
    
    for (;;) {
		queueIn[0] = i_kernel.read();// Read 1st flit header (src + dest + cmd + burst)

                if ( debug >=1 ) cout << "["<< this->name() << "::packetDisassembly]: >>>flit"<<0<<" received: [" << std::hex<<queueIn[0]<<std::dec<<"]"<<endl;
		
		burst = queueIn[0].range(flit_size-23, flit_size-32);

        for (i=1; i<= burst; i++) {
            
            queueIn[i] = i_kernel.read();

            if ( debug >=1 ) cout << "["<< this->name() << "::packetDisassembly]: >>>flit"<<i<<" received: [" << std::hex<<queueIn[i]<<std::dec<<"]"<<endl;
            
        }
        
        for (i=0; i<= burst; i++) {
            bufferPD_port.write(queueIn[i]);
        }
        
    }
        
}
