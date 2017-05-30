/*
 * decod.cpp
 *
 *  Created on: 09/07/2015
 *   *  Modified by José Adalberto F. Gualeve on 30/04/16
 *   *  Modified by Felipe Cabral on 05/07/16.
 *      Author: soudre
 */

#include "decod.h"
#include "noc_common.h"

//Thread para leitura do flit

void Decod::lerDecod() {
    for (;;) {
        eh_decod = false;
        dado_decod = i_decod->read();
        eh_decod = true;
        dado_decod_evt.notify(SC_ZERO_TIME);
        wait(main_ack2_evt);
    }
}

//Thread principal

void Decod::main() {

    sc_uint<32> dado_m;
	sc_uint<10> burst0, burst1, burst2, burst3, burst4, burst5;
    int count0=0, count1=0, count2=0,count3=0, count4=0, count5=0, i;
    for (;;) {
            //Evento de ocorrencia do flit
        wait (dado_decod_evt);
        if (eh_decod){
            dado_m = dado_decod.range(52,21);

			if(dado_decod.range(18,16)==0)
			{
				if (count0 == 0)
					burst0 = dado_m.range(flit_size-23, flit_size-32);

				FIFO0.write(dado_m);
				count0++;
				if(count0==burst0 + 1)
				{
					count0=0;
					for(i=0;i<=burst0;i++)
						{
						o_decod->write(FIFO0.read());
						}
				}
			}

			if(dado_decod.range(18,16)==1)
			{	
				if (count1 == 0)
					burst1 = dado_m.range(flit_size-23, flit_size-32);

				FIFO1.write(dado_m);
				count1++;
				if(count1==burst1 + 1)
				{
					count1=0;
					for(i=0;i<=burst1;i++)
						{
						o_decod->write(FIFO1.read());
						}
				}
			}

			if(dado_decod.range(18,16)==2)
			{	
				if (count2 == 0)
					burst2 = dado_m.range(flit_size-23, flit_size-32);

				FIFO2.write(dado_m);
				count2++;
				if(count2==burst2 + 1)
				{
					count2=0;
					for(i=0;i<=burst2;i++)
						{
						o_decod->write(FIFO2.read());
						}
				}
			}

			if(dado_decod.range(18,16)==3)
			{	
				if (count3 == 0)
					burst3 = dado_m.range(flit_size-23, flit_size-32);

				FIFO3.write(dado_m);
				count3++;
				if(count3==burst3 + 1)
				{
					count3=0;
					for(i=0;i<=burst3;i++)
						{
						o_decod->write(FIFO3.read());
						}
				}
			}

			if(dado_decod.range(18,16)==4)
			{	
				if (count4 == 0)
					burst4 = dado_m.range(flit_size-23, flit_size-32);

				FIFO4.write(dado_m);
				count4++;
				if(count4==burst4 + 1)
				{
					count4=0;
					for(i=0;i<=burst4;i++)
						{
						o_decod->write(FIFO4.read());
						}
				}
			}

			if(dado_decod.range(18,16)==5)
			{	
				if (count5 == 0)
					burst5 = dado_m.range(flit_size-23, flit_size-32);

				FIFO5.write(dado_m);
				count5++;
				if(count5==burst5 + 1)
				{
					count5=0;
					for(i=0;i<=burst5;i++)
						{
						o_decod->write(FIFO5.read());
						}
				}
			}
            //o_decod->write(dado_m);
                //Saida de Debug
        }
        main_ack2_evt.notify(SC_ZERO_TIME);
    }
}
