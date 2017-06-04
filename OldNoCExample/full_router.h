/*
 * - full_router.h
 * 
 * Created by Felipe Cabral on 05/07/16.
 * Copyright 2016 - All rights reserved 
*/
#ifndef full_router_H_
#define full_router_H_
#include "noc_common.h"
#include "systemc.h"
#include "kernel_ni.h"
#include "router.h"
#include "cod.h"
#include "decod.h"

SC_MODULE ( Full_Router ) { 
//Inputs and Outputs
//KERNEL
    sc_fifo_in < flit_t > bufferPM_port;
    sc_fifo_out < flit_t > bufferPD_port;    
//ROUTER
	sc_fifo_in <sc_uint<53> > i_norte, i_oeste, i_sul, i_leste;
	sc_fifo_out<sc_uint<53> > o_sul, o_leste, o_oeste, o_norte;

//FIFOS

	sc_fifo< flit_t > // kernel_ni to cod
        k2c;

	sc_fifo< flit_t > // decod to kernel_ni
        d2k;

	sc_fifo<sc_uint<53> > // cod to router
        c2r;

	sc_fifo<sc_uint<53> > // router to decod
        r2d;

//INSTANTIATIONS
    Router *router;
	Cod *cod;
	Decod *decod;
	Kernel_ni *kernel_ni;
   
//CONSTRUCTOR

	SC_HAS_PROCESS( Full_Router );
    Full_Router (
        sc_module_name _name,
        flit1_4t identify
				):
    sc_module(_name), identify(identify) , k2c(8), d2k(8), c2r(8), r2d(8)
    {

        router= new Router("router");
		cod= new Cod("cod");
		decod= new Decod("decod");
		kernel_ni= new Kernel_ni("kernel_ni",identify);
		
		//ROUTER
		router->i_oeste(i_oeste);
		router->o_oeste(o_oeste);
		router->i_leste(i_leste);
		router->o_leste(o_leste);
		router->i_norte(i_norte);
		router->o_norte(o_norte);
		router->i_sul(i_sul);
		router->o_sul(o_sul);
		router->i_cod(c2r);
		router->o_decod(r2d);

		//COD
		cod->i_cod(k2c);
		cod->o_cod(c2r);

		//DECOD
		decod->i_decod(r2d);
		decod->o_decod(d2k);

		//KERNEL
		kernel_ni->o_kernel(k2c);
		kernel_ni->i_kernel(d2k);
		kernel_ni->bufferPM_port(bufferPM_port);
		kernel_ni->bufferPD_port(bufferPD_port);
    }

	private:
		flit1_4t identify;
}; 

#endif