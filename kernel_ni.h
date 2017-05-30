/*
 * - kernel_ni.h
 *   
* 
 * Created by José Adalberto F. Gualeve  on 08/07/15.
 *  Modified by Felipe Cabral on 05/07/16.
 * Copyright 2015 - All rights reserved 
*/
#ifndef kernel_ni_h
#define kernel_ni_h
#include "systemc.h"
#include "noc_common.h"

SC_MODULE ( Kernel_ni ) { 
// to shell ports
    sc_fifo_in < flit_t > bufferPM_port;
    sc_fifo_out < flit_t > bufferPD_port;
// to router ports    
    sc_fifo_out< flit_t > o_kernel;
    sc_fifo_in< flit_t > i_kernel;

    flit1_4t identify_tab( flit_t );
    void packetMaker();
    void packetDisassembly();
   
     
    SC_HAS_PROCESS( Kernel_ni );
    Kernel_ni (
        sc_module_name _name,
            //  sc_uint<4> x,
            //  sc_uint<4> y,
        flit1_4t identify
				):
    sc_module(_name), identify(identify) 
    {
        SC_THREAD( packetMaker );
        SC_THREAD( packetDisassembly );
        
    }
  private:

    flit_t queueIn[1024], queueOut[1024];
    
    flit1_4t identify;
        /*
         * buffers PM & PD
         *
         * [ cmd+flags ][ address ][ data ][ ... ][ data ]
         *   cmd=8bits, flags=24bits + addr=32bits + data=(n-2)*32bits
         * */    
}; 
#endif
