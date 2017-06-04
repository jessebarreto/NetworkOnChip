/*                                              
* cod.cpp
 *
 *  Created on: 08/07/2015
 *      Author: soudre
 *  Modified by José Adalberto F. Gualeve on 30/04/16
 *  Modified by Felipe Cabral e Eduardo Mesquita on 05/07/16.
 *  Modified by José Adalberto F. Gualeve on 18/04/17
 */

#include "cod.h"
#include <iostream>

//Thread para leitura do flit

void Cod::lerCod() {
    for (;;) {
        if ( debug >=3 ) cout << "Cod Ler Kernel: " << endl;
        eh_cod = false;
        dado_cod = i_cod->read();
        if ( debug >=3 ) cout << "Cod Leu Kernel: " << endl;
        eh_cod = true;
        dado_cod_evt.notify(SC_ZERO_TIME);
        wait(main_ack_evt);
    }
}

//Thread principal

void Cod::main() {
    	//Variavel para receber o flit proveniente do modulo
    sc_uint<32> tmp;
    	//Variavel para receber o flit modificado
    sc_uint<53> dado_m;
        //Variavel para receber o burst do pacote
    sc_uint<10> burst;
    
    count = 0;
    for (;;) { 
            //Evento de ocorrencia do flit
        wait (dado_cod_evt);
        if (eh_cod){
            tmp = dado_cod;
            if ( debug >=3 ) cout << "Eh_cod:" << eh_cod << endl;
            if ( debug >=3 ) cout << "Count: " << count << endl;
                //Verifica se o flit e de cabecalho ou dado
            if (count == 0){
                    //origem <-- recebe a origem do pacote referente aos flits em questao
                origem = (int)tmp.range(flit_size-1, flit_size-8);
                if ( debug >=3 ) cout << "Origem: " << origem << endl;
                    //destino <-- recebe o destino do pacote referento aos flits em questao
                destino = (int)tmp.range(flit_size-9, flit_size-16);
                if ( debug >=3 ) cout << "Destino: " << destino << endl;
                burst = tmp.range(flit_size-23, flit_size-32);
            }
                //contador de controle
            count++;
                //Se ja chegou todos os flits, formando o pacote, zera o contador
            if (count == burst + 1){
                count = 0;     
                if ( debug >=2 ) cout << "["<< this->name() << "]: will send package from " << origem << " to " << destino << endl;
                
            }
            
                //Tabela de roteamento
            switch(destino){
                    //Se o destino for 0
                case 0:
                        //bit referente a variavel saida (declarada em router.h)
                    dado_m.range(20,20) = 0;
                    
                    if (origem == 1){
                        dado_m.range(20,20) = 1;   //indica o sentido do roteamento
                        dado_m.range(52,21) = tmp; //recebe o dado do flit
                        dado_m.range(15,8) = 1;    //indica o x
                        dado_m.range(7,0) = 0;     //indica o y
                        dado_m.range(18,16) = 1;   //indica a entrada do flit
                        dado_m.range(19,19) = 1;   //Bit de controle da saida do flit

                    }else if (origem == 2){
                        dado_m.range(20,20) = 1;
                        dado_m.range(52,21) = tmp;
                        dado_m.range(15,8) = 2;
                        dado_m.range(7,0) = 0;
                        dado_m.range(18,16) = 2;
                       
                    }else if (origem == 3){
                        dado_m.range(52,21) = tmp;
                        dado_m.range(15,8) = 0;
                        dado_m.range(7,0) = 1;
                        dado_m.range(18,16) = 3;
                        
                    }else if (origem == 4){
                        dado_m.range(52,21) = tmp;
                        dado_m.range(15,8) = 1;
                        dado_m.range(7,0) = 1;
                        dado_m.range(18,16) = 4;
                        dado_m.range(19,19) = 1;
                        
                    }else if (origem == 5){
                        dado_m.range(52,21) = tmp;
                        dado_m.range(15,8) = 2;
                        dado_m.range(7,0) = 1;
                        dado_m.range(18,16) = 5;
                    }
                    break;
                case 1:
                    dado_m.range(20,20) = 0;
                    if (origem == 0){
                        dado_m.range(20,20) = 1;
                        dado_m.range(52,21) = tmp;
                        dado_m.range(15,8) = 1;
                        dado_m.range(7,0) = 0;
                        dado_m.range(18,16) = 0;

                    }else if (origem == 2){
                        dado_m.range(20,20) = 1;
                        dado_m.range(52,21) = tmp;
                        dado_m.range(15,8) = 1;
                        dado_m.range(7,0) = 0;
                        dado_m.range(18,16) = 2;

                    }else if (origem == 3){
                        dado_m.range(52,21) = tmp;
                        dado_m.range(15,8) = 1;
                        dado_m.range(7,0) = 1;
                        dado_m.range(18,16) = 3;

                    }else if (origem == 4){
                        dado_m.range(52,21) = tmp;
                        dado_m.range(15,8) = 0;
                        dado_m.range(7,0) = 1;
                        dado_m.range(18,16) = 4;
                        dado_m.range(19,19) = 1;

                    }else if (origem == 5){
                        dado_m.range(52,21) = tmp;
                        dado_m.range(15,8) = 1;
                        dado_m.range(7,0) = 1;
                        dado_m.range(18,16) = 5;
                    }
                    
                    break;
                case 2:
                    dado_m.range(20,20) = 0;
                    if (origem == 0){
                        dado_m.range(20,20) = 1;
                        dado_m.range(52,21) = tmp;
                        dado_m.range(15,8) = 2;
                        dado_m.range(7,0) = 0;
                        dado_m.range(18,16) = 0;
                        
                    }else if (origem == 1){
                        dado_m.range(20,20) = 1;
                        dado_m.range(52,21) = tmp;
                        dado_m.range(15,8) = 1;
                        dado_m.range(7,0) = 0;
                        dado_m.range(18,16) = 1;
                        dado_m.range(19,19) = 0;
                        
                    }else if (origem == 3){
                        dado_m.range(47,16) = tmp;
                        dado_m.range(15,8) = 2;
                        dado_m.range(7,0) = 1;
                        dado_m.range(18,16) = 3;
                        
                    }else if (origem == 4){

                        dado_m.range(52,21) = tmp;
                        dado_m.range(15,8) = 1;
                        dado_m.range(7,0) = 1;
                        dado_m.range(18,16) = 4;
                        dado_m.range(19,19) = 0;
                        
                    }else if (origem == 5){

                        dado_m.range(52,21) = tmp;
                        dado_m.range(15,8) = 0;
                        dado_m.range(7,0) = 1;
                        dado_m.range(18,16) = 5;

                    }
                    
                    break;
                case 3:
                    dado_m.range(20,20) = 0;
                    if (origem == 0){
                        dado_m.range(52,21) = tmp;
                        dado_m.range(15,8) = 0;
                        dado_m.range(7,0) = 1;
                        dado_m.range(18,16) = 0;
                        
                    }else if (origem == 1){
                        dado_m.range(52,21) = tmp;
                        dado_m.range(15,8) = 1;
                        dado_m.range(7,0) = 1;
                        dado_m.range(18,16) = 1;
                        dado_m.range(19,19) = 1;
                        
                    }else if (origem == 2){
                        dado_m.range(52,21) = tmp;
                        dado_m.range(15,8) = 2;
                        dado_m.range(7,0) = 1;
                        dado_m.range(18,16) = 2;
                        
                    }else if (origem == 4){
                        dado_m.range(20,20) = 1;
                        dado_m.range(52,21) = tmp;
                        dado_m.range(15,8) = 1;
                        dado_m.range(7,0) = 0;
                        dado_m.range(18,16) = 4;
                        dado_m.range(19,19) = 1;
                        
                    }else if (origem == 5){
                        dado_m.range(20,20) = 1;
                        dado_m.range(52,21) = tmp;
                        dado_m.range(15,8) = 2;
                        dado_m.range(7,0) = 0;
                        dado_m.range(18,16) = 5;
                        
                    }
                    break;
                case 4:
                    dado_m.range(20,20) = 0;
                    if (origem == 0){
                        dado_m.range(52,21) = tmp;
                        dado_m.range(15,8) = 1;
                        dado_m.range(7,0) = 1;
                        dado_m.range(18,16) = 0;
                        
                    }else if (origem == 1){
                        dado_m.range(52,21) = tmp;
                        dado_m.range(15,8) = 0;
                        dado_m.range(7,0) = 1;
                        dado_m.range(18,16) = 1;
                        
                    }else if (origem == 2){
                        dado_m.range(52,21) = tmp;
                        dado_m.range(15,8) = 1;
                        dado_m.range(7,0) = 1;
                        dado_m.range(18,16) = 2;
                        
                    }else if (origem == 3){
                        dado_m.range(20,20) = 1;
                        dado_m.range(52,21) = tmp;
                        dado_m.range(15,8) = 1;
                        dado_m.range(7,0) = 0;
                        dado_m.range(18,16) = 3;
                        
                    }else if (origem == 5){
                        dado_m.range(20,20) = 1;
                        dado_m.range(52,21) = tmp;
                        dado_m.range(15,8) = 1;
                        dado_m.range(7,0) = 0;
                        dado_m.range(18,16) = 5;
                        
                    }
                    break;
                case 5:
                    dado_m.range(20,20) = 0;
                    if (origem == 0){
                        dado_m.range(52,21) = tmp;
                        dado_m.range(15,8) = 2;
                        dado_m.range(7,0) = 1;
                        dado_m.range(18,16) = 0;
                        
                    }else if (origem == 1){
                        dado_m.range(52,21) = tmp;
                        dado_m.range(15,8) = 1;
                        dado_m.range(7,0) = 1;
                        dado_m.range(18,16) = 1;
                        dado_m.range(19,19) = 0;
                        
                    }else if (origem == 2){
                        dado_m.range(52,21) = tmp;
                        dado_m.range(15,8) = 0;
                        dado_m.range(7,0) = 1;
                        dado_m.range(18,16) = 2;
                        
                    }else if (origem == 3){
                        dado_m.range(20,20) = 1;
                        dado_m.range(52,21) = tmp;
                        dado_m.range(15,8) = 2;
                        dado_m.range(7,0) = 0;
                        dado_m.range(18,16) = 3;
                        
                    }else if (origem == 4){
                        dado_m.range(20,20) = 1;
                        dado_m.range(52,21) = tmp;
                        dado_m.range(15,8) = 1;
                        dado_m.range(7,0) = 0;
                        dado_m.range(18,16) = 4;
                        dado_m.range(19,19) = 0;
                        
                    }
                    break;
            }//fim do switch

            
            o_cod->write(dado_m);
					
            if ( debug >=2 ) cout << "["<< this->name() << "]: sent " << std::hex << dado_m << std::dec << endl;
        }
        main_ack_evt.notify(SC_ZERO_TIME);
    }//fim do for
}//fim da thread
