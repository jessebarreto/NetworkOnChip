/*
 * - main.cpp
 * 
 * 
 *  Created by Jos� Adalberto F. Gualeve  and Marlon Soudre on 07/07/15.
 *  Modified by Jos� Adalberto F. Gualeve on 05/05/16
 *  Modified by Felipe Cabral e Eduardo Mesquita on 05/07/16.
 * Copyright 2015,2016 - All rights reserved 
 */

#include "systemc.h"
#include "kernel_ni.h"
#include "shell_master_ni.h"
#include "shell_slave_ni.h"
#include "master.h"
#include "slave.h"
#include "router.h"
#include "cod.h"
#include "decod.h"
#include "full_router.h"

#include "globals.h"
#include "memoria.h"
#include "mips.h"
#include "shell_mips.h"
#include "shell_memoria.cpp"

#include <iostream>

using namespace std;

/*
      [master0]  ||        [mem-mips]  ||
              \\ ||                 \\ || 
           ====(r00)===r0001/r0100===(r01)=
                 ||                    ||       
             r0010/r1000           r0111/r1101
                 ||                    ||         
      [master1]  ||            [mips]  ||     
              \\ ||                 \\ ||   
           ====(r10)===r1011/r1110===(r11)==
                 ||                    ||         
             r1020/r2010           r1121/r2111 
                 ||                    ||   
       [slave0]  ||          [slave3]  ||   
              \\ ||                 \\ ||    
           ====(r20)===r2021/r2120===(r21)===
                 ||                    ||

*/

int sc_main ( int argc, char *argv[]) {
    Full_Router r00("r00",0);
    Full_Router r01("r01",1);
    Full_Router r10("r10",2);
    Full_Router r11("r11",3);
    Full_Router r20("r20",4);
    Full_Router r21("r21",5);

    Master master0("master0",0);
    Master master1("master1",2);
    ShellMasterInterface m0_shell("m0_shell", 0);
    ShellMasterInterface m1_shell("m1_shell", 2);

    mips_v0 mips("mips",1);
    shellmi_mips p_shell("p_shell",1);

    shellme_mem_v0 m_shell("m_shell",3);
    mem_mips mem("mem", INT_MEM_SIZE,3);

    Slave slave0("slave0",4);  // associado ao n� 2 (r20)
	//Slave slave1("slave1",3); 
	//Slave slave2("slave2",4); 
    Slave slave3("slave3",5); 
    ShellSlaveInterface s0_shell("s0_shell", 4);
	//ShellSlaveInterface s1_shell("s1_shell", 3);
	//ShellSlaveInterface s2_shell("s2_shell", 4);
    ShellSlaveInterface s3_shell("s3_shell", 5);

    sc_fifo<sc_uint<53> >

            //
            //Channels: out border
            //       
        i_oeste_0("i_oeste_0",1), o_oeste_0("o_oeste_0",1), i_oeste_1("i_oeste_1",1),
	 o_oeste_1("o_oeste_1",1), i_oeste_2("i_oeste_2",1), o_oeste_2("o_oeste_2",1),
	 i_norte_0("i_norte_0",1), o_norte_0("o_norte_0",1), i_norte_1("i_norte_1",1), o_norte_1("o_norte_1",1),
	 i_leste_0("i_leste_0",1), o_leste_0("o_leste_0",1), i_leste_1("i_leste_1",1),
	 o_leste_1("o_leste_1",1), i_leste_2("i_leste_2",1), o_leste_2("o_leste_2",1),
	 i_sul_0("i_sul_0",1), o_sul_0("o_sul_0",1), i_sul_2("i_sul_2",1), o_sul_2("o_sul_2",1),
             //
             //Channels: router .. router
             // 
        c0001("c0001",1), c0100("c0100",1),
        c0010("c0010",1), c1000("c1000",1), c0111("c0111",1), c1101("c1101",1),
        c1011("c1011",1), c1110("c1110",1),
        c1020("c1020",1), c2010("c2010",1), c1121("c1121",1), c2111("c2111",1),
        c2021("c2021",1), c2120("c2120",1);

 
	// FIFOS

    sc_fifo< flit_t > 
        wr_data0("wr_data0",1), wr_data1("wr_data1",1), wr_data2("wr_data2",1), wr_data3("wr_data3",1), wr_data4("wr_data4",1), wr_data5("wr_data5",1),
        addr0("addr0",1), addr1("addr1",1), addr2("addr2",1), addr3("addr3",1), addr4("addr4",1), addr5("addr5",1), 
        rd_data0("rd_data0",1),rd_data1("rd_data1",1), rd_data2("rd_data2",1), rd_data3("rd_data3",1),rd_data4("rd_data4",1), rd_data5("rd_data5",1);

    sc_fifo< flit1_4t>
        cmd0("cmd0",1), cmd1("cmd1",1), cmd2("cmd2",1), cmd3("cmd3",1), cmd4("cmd4",1), cmd5("cmd5",1);

    sc_fifo< flit1_4t>
        wr_resp0("wr_resp0",1), wr_resp1("wr_resp1",1), wr_resp2("wr_resp2",1), wr_resp3("wr_resp3",1), wr_resp4("wr_resp4",1), wr_resp5("wr_resp5",1);

    sc_fifo<sc_uint<10> >
        burst0("burst0", 1), burst1("burst1", 1);

    sc_fifo< flit_t > 
        bufferPM0("bufferPM0",1),bufferPD0("bufferPD0",1),
        bufferPM1("bufferPM1",1),bufferPD1("bufferPD1",1),
        bufferPM2("bufferPM2",1),bufferPD2("bufferPD2",1),
        bufferPM3("bufferPM3",1),bufferPD3("bufferPD3",1),
        bufferPM4("bufferPM4",1),bufferPD4("bufferPD4",1),
        bufferPM5("bufferPM5",1),bufferPD5("bufferPD5",1);

	// full_router r00                                // full_router r01
    //===========================================//       //============================================//
    r00.i_oeste(i_oeste_0); r00.o_oeste(o_oeste_0);       r01.i_oeste(c0001);     r01.o_oeste(c0100);
    r00.i_norte(i_norte_0); r00.o_norte(o_norte_0);       r01.i_norte(i_norte_1); r01.o_norte(o_norte_1);
    r00.i_leste(c0100);     r00.o_leste(c0001);           r01.i_leste(i_leste_0); r01.o_leste(o_leste_0);
    r00.i_sul(c1000);       r00.o_sul(c0010);             r01.i_sul(c1101);       r01.o_sul(c0111);

	// full_router r10                                // full_router r11
    r10.i_oeste(i_oeste_1); r10.o_oeste(o_oeste_1);       r11.i_oeste(c1011);     r11.o_oeste(c1110);
    r10.i_norte(c0010);     r10.o_norte(c1000);           r11.i_norte(c0111);     r11.o_norte(c1101);
    r10.i_leste(c1110);     r10.o_leste(c1011);           r11.i_leste(i_leste_1); r11.o_leste(o_leste_1);
    r10.i_sul(c2010);       r10.o_sul(c1020);             r11.i_sul(c2111);       r11.o_sul(c1121);

	// full_router r20				  // full_router r21
    r20.i_oeste(i_oeste_2); r20.o_oeste(o_oeste_2);       r21.i_oeste(c2021);     r21.o_oeste(c2120);
    r20.i_norte(c1020);     r20.o_norte(c2010);           r21.i_norte(c1121);     r21.o_norte(c2111);
    r20.i_leste(c2120);     r20.o_leste(c2021);           r21.i_leste(i_leste_2); r21.o_leste(o_leste_2);
    r20.i_sul(i_sul_0);     r20.o_sul(o_sul_0);           r21.i_sul(i_sul_2);     r21.o_sul(o_sul_2);

	//Signal from MIPS
    sc_signal<bool> reset;

	//Connecting MIPS and Shell
    mips.reset(reset);
    mips.pshell(p_shell);

	//Connecting Mem and Shell
    m_shell.pmem(mem);

    mem.load_mem("buble.bin", 0);
    mem.load_mem("buble.data", 8192);
	
    if ( debug >=0 ) cout << "Dados originais:" << endl << endl;
    mem.dump_mem(8192, 8224, 'd');

	//MASTERS and SHELLS conecctions
    master0.wr_data_port(wr_data0);  m0_shell.wr_data_port(wr_data0);
    master0.cmd_port(cmd0);          m0_shell.cmd_port(cmd0);      
    master0.addr_port(addr0);	     m0_shell.addr_port(addr0);   
    master0.rd_data_port(rd_data0);  m0_shell.rd_data_port(rd_data0);
    master0.wr_resp_port(wr_resp0);  m0_shell.wr_resp_port(wr_resp0);
    master0.burst_port(burst0);      m0_shell.burst_port(burst0);
	
    master1.wr_data_port(wr_data1);  m1_shell.wr_data_port(wr_data1);
    master1.cmd_port(cmd1);          m1_shell.cmd_port(cmd1);      
    master1.addr_port(addr1);        m1_shell.addr_port(addr1);   
    master1.rd_data_port(rd_data1);  m1_shell.rd_data_port(rd_data1);
    master1.wr_resp_port(wr_resp1);  m1_shell.wr_resp_port(wr_resp1);
    master1.burst_port(burst1);      m1_shell.burst_port(burst1);
	
	//SLAVES and SHELLS connections
    slave0.wr_data_port(wr_data2);  s0_shell.wr_data_port(wr_data2);
    slave0.cmd_port(cmd2);          s0_shell.cmd_port(cmd2);
    slave0.addr_port(addr2);        s0_shell.addr_port(addr2);
    slave0.rd_data_port(rd_data2);  s0_shell.rd_data_port(rd_data2);
    slave0.wr_resp_port(wr_resp2);  s0_shell.wr_resp_port(wr_resp2);

	/*slave1.wr_data_port(wr_data3);  s1_shell.wr_data_port(wr_data3);
	slave1.cmd_port(cmd3);          s1_shell.cmd_port(cmd3);
	slave1.addr_port(addr3);        s1_shell.addr_port(addr3);
	slave1.rd_data_port(rd_data3);  s1_shell.rd_data_port(rd_data3);
	slave1.wr_resp_port(wr_resp3);  s1_shell.wr_resp_port(wr_resp3);*/


    slave3.wr_data_port(wr_data5);  s3_shell.wr_data_port(wr_data5);
    slave3.cmd_port(cmd5);          s3_shell.cmd_port(cmd5);
    slave3.addr_port(addr5);        s3_shell.addr_port(addr5);
    slave3.rd_data_port(rd_data5);  s3_shell.rd_data_port(rd_data5);
    slave3.wr_resp_port(wr_resp5);  s3_shell.wr_resp_port(wr_resp5);

        //SHELLS and ROUTERS connections
    m0_shell.bufferPD_port(bufferPD0); r00.bufferPD_port(bufferPD0); 
    m0_shell.bufferPM_port(bufferPM0); r00.bufferPM_port(bufferPM0);
    	
    m_shell.in(bufferPD1);  r01.bufferPD_port(bufferPD1);
    m_shell.out(bufferPM1); r01.bufferPM_port(bufferPM1);
    
    m1_shell.bufferPD_port(bufferPD2); r10.bufferPD_port(bufferPD2); 
    m1_shell.bufferPM_port(bufferPM2); r10.bufferPM_port(bufferPM2);
    
    p_shell.in(bufferPD3); r11.bufferPD_port(bufferPD3);
    p_shell.out(bufferPM3); r11.bufferPM_port(bufferPM3);
    
    s0_shell.bufferPD_port(bufferPD4); r20.bufferPD_port(bufferPD4);
    s0_shell.bufferPM_port(bufferPM4); r20.bufferPM_port(bufferPM4);

    s3_shell.bufferPD_port(bufferPD5); r21.bufferPD_port(bufferPD5);
    s3_shell.bufferPM_port(bufferPM5); r21.bufferPM_port(bufferPM5);

	
	//routers without masters or slaves

	//r00.bufferPD_port(teste_buff_PD3);
	//r00.bufferPM_port(teste_buff_PM3);

	//r10.bufferPD_port(bufferPD5);
	//r10.bufferPM_port(bufferPM5);

	//r20.bufferPD_port(bufferPD4);
	//r20.bufferPM_port(bufferPM4);

	//r21.bufferPD_port(teste_buff_PD);
	//r21.bufferPM_port(teste_buff_PM);

    sc_start();
    
    if ( debug >=0 ) cout << "Dados processados:" << endl;
    mem.dump_mem(8192, 8224, 'd');
	
    if ( debug >=0 ) cout << "Registradores: " << endl;
    mips.dump_breg();

    return 0;
}
