/*
 *  router.cpp
 *  NoC router
 *
 *  Created by Ricardo Jacobi on 27/5/15.
 *
 *  Modified by Felipe Cabral on 25/06/16.
 *  Copyright 2015 Universidade de Brasilia. All rights reserved.
 *
 */

#include "router.h"
#include <iostream>
#include "cod.h"
#include "noc_common.h"

//Thread para leitura da entrada norte do modulo de roteamento

void Router::lerNorte() {
    for (;;) {
        eh_norte = false;
        dado_norte = i_norte->read();

			if ( debug >=2 ) cout <<"["<< this->name() << "]"<< "Leu Norte " << endl;
        eh_norte = true;
        dado_norte_evt.notify(SC_ZERO_TIME); 
        wait(norte_ack_evt);
    }
}

//Thread para leitura da entrada sul do modulo de roteamento

void Router::lerSul() {
    for (;;) {
        eh_sul = false;
        dado_sul = i_sul->read();

        if ( debug >=2 ) cout <<"["<< this->name() << "]"<< "Leu Sul " << endl;
        eh_sul = true;
        dado_sul_evt.notify(SC_ZERO_TIME);
        wait(sul_ack_evt);
    }
}

//Thread para leitura da entrada leste do modulo de roteamento

void Router::lerLeste() {
    for (;;) {
        eh_leste = false;
        dado_leste = i_leste->read();

        if ( debug >=2 ) cout <<"["<< this->name() << "]"<< "Leu Leste " << endl;
        eh_leste = true;
        dado_leste_evt.notify(SC_ZERO_TIME);
        wait(leste_ack_evt);
    }
}

//Thread para leitura da entrada oeste do modulo de roteamento

void Router::lerOeste() {
    for (;;) {
        eh_oeste = false;
        dado_oeste = i_oeste->read();

        if ( debug >=2 ) 	cout <<"["<< this->name() << "]"<< "Leu Oeste " << endl;
        eh_oeste = true;
        dado_oeste_evt.notify(SC_ZERO_TIME); 
        wait(oeste_ack_evt);
    }
}


//Thread para leitura da entrada do COD do modulo de roteamento

void Router::lerCod() {
    for (;;) {
        eh_cod = false;
        dado_cod = i_cod->read();

        if ( debug >=2 ) cout <<"["<< this->name() << "]"<< "Leu coder " << endl;
        eh_cod = true;
        dado_cod_evt.notify(SC_ZERO_TIME); 
        wait(cod_ack_evt);
    }
}

//Threads principais
void Router::Norte() {
    sc_uint<53> tmp_norte;
    for (;;) {
            //Aguarda a ocorrencia de um evento em uma das entradas do modulo de roteamento
        wait (dado_norte_evt);
            //Se o evento ocorreu na entrada norte do modulo de roteamento
        tmp_norte = dado_norte;
            //Notifica o evento principal, bloqueando a presente thread
            Run(tmp_norte);
		norte_ack_evt.notify(SC_ZERO_TIME);

                if ( debug >=2 ) cout <<"["<< this->name() << "]"<< "Norte terminou " << endl;
    }//Fim do for
}//Fim da thread


void Router::Sul() {
    sc_uint<53> tmp_sul;
    for (;;) {
            //Aguarda a ocorrencia de um evento em uma das entradas do modulo de roteamento
        wait (dado_sul_evt);
            //Se o evento ocorreu na entrada norte do modulo de roteamento
        tmp_sul = dado_sul;
            //Notifica o evento principal, bloqueando a presente thread
            Run(tmp_sul);
        sul_ack_evt.notify(SC_ZERO_TIME);

        if ( debug >=2 ) cout <<"["<< this->name() << "]"<< "Sul terminou " << endl;
    }//Fim do for
}//Fim da thread


void Router::Leste() {
    sc_uint<53> tmp_leste;
    for (;;) {
            //Aguarda a ocorrencia de um evento em uma das entradas do modulo de roteamento
        wait (dado_leste_evt);
            //Se o evento ocorreu na entrada norte do modulo de roteamento
        tmp_leste = dado_leste;
            //Notifica o evento principal, bloqueando a presente thread
            Run(tmp_leste);
		leste_ack_evt.notify(SC_ZERO_TIME);

			if ( debug >=2 ) cout <<"["<< this->name() << "]"<< "Leste terminou " << endl;
    }//Fim do for
}//Fim da thread


void Router::Oeste() {
    sc_uint<53> tmp_oeste;
    for (;;) {
            //Aguarda a ocorrencia de um evento em uma das entradas do modulo de roteamento
        wait (dado_oeste_evt);
            //Se o evento ocorreu na entrada norte do modulo de roteamento
        tmp_oeste = dado_oeste;
            //Notifica o evento principal, bloqueando a presente thread
            Run(tmp_oeste);
		oeste_ack_evt.notify(SC_ZERO_TIME);
                if ( debug >=2 ) 
			cout <<"["<< this->name() << "]"<< "Oeste terminou " << endl;
    }//Fim do for
}//Fim da thread


void Router::Cod() {
    sc_uint<53> tmp_cod;
    for (;;) {
            //Aguarda a ocorrencia de um evento em uma das entradas do modulo de roteamento
        wait (dado_cod_evt);
            //Se o evento ocorreu na entrada norte do modulo de roteamento
        tmp_cod = dado_cod;
            //Notifica o evento principal, bloqueando a presente thread
            Run(tmp_cod);
		cod_ack_evt.notify(SC_ZERO_TIME);
                if ( debug >=2 ) 
			cout <<"["<< this->name() << "]"<< "Cod terminou " << endl;
    }//Fim do for
}//Fim da thread


// Função que executa o roteamento
void Router::Run(sc_uint<53> tmp){
			// x <-- coordenada x a ser decrementada
        x = (int) tmp.range(15, 8);
            // y <-- coordenada y a ser decrementada
        y = (int) tmp.range(7, 0);
            // ent <-- Entrado do roteador pela qual o flit entrou
        ent = (int) tmp.range(18, 16);
            // saida <-- Bit de controle indicando o sentido do roteamento
        saida = (int) tmp.range(20,20);
            //Bit de controle da saida do flit
        said = (int) tmp.range(19, 19);
		
            //Algoritmo de roteamento x,y por decremento
            //Se o flit entrou pelo elemento de roteamento 0
        if(ent == 0){
		//Se o x for maior que zero decrementa e escreve na saida sul do elemento de roteamento
            if (x > 0) {
                x = x - 1;
                    //Saida de debug
		if ( debug >=2 ) 
                    cout <<"["<< this->name() << "]:Saida SUL (Saida de Debug) x: " << tmp.range(15, 8) << " y: "<< tmp.range(7, 0) << " ID de origem: " << tmp.range(18, 16) << "\n";
                tmp.range(15, 8) = x;
                o_sul->write(tmp);
                    //Se o y for maior que zero decrementa e escreve na saida leste do elemento de roteamento
            } else if (y > 0) {
                y = y - 1;
                    //Saida de debug
		if ( debug >=2 ) 
                    cout <<"["<< this->name() << "]:Saida LESTE (Saida de Debug) x: " << tmp.range(15, 8) << " y: "<< tmp.range(7, 0) << " ID de origem: " << tmp.range(18, 16) << "\n";
                tmp.range(7, 0) = y;
                o_leste->write(tmp);
                    //Se o x e y forem zero, achou o elemento de roteamento ao qual esta conectado o modulo de destino
            } else {
                    //Saida de Debug
                if(debug>=2)
                    cout << "["<< this->name() << "]:(Saida de Debug) Achou o elemento de roteamento." << " ID de origem: " << tmp.range(18, 16) << "\n";
                o_decod->write(tmp);
            }
                //Se o flit entrou pelo elemento de roteamento 1.(Procedimeto analogo ao explicado para a entrada 0
        }else if (ent == 1){
                //Se o roteador de destino do flit esta acima do elemento de roteamento em questao
            if (said == 1){
                if (x > 0) {
                    x = x - 1;
                        //Saida de Debug
                    if(debug>=2)
                        cout <<"["<< this->name() << "]:Saida NORTE (Saida de Debug) x: " << tmp.range(15, 8) << " y: "<< tmp.range(7, 0) << " ID de origem: " << tmp.range(18, 16) << "\n";
                    tmp.range(15, 8) = x;
                    o_norte->write(tmp);
                } else if (y > 0) {
                    y = y - 1;
                        //Saida de Debug
                    if(debug>=2)
                        cout <<"["<< this->name() << "]:Saida LESTE (Saida de Debug) x: " << tmp.range(15, 8) << " y: "<< tmp.range(7, 0) << " ID de origem: " << tmp.range(18, 16) << "\n";
                    tmp.range(7, 0) = y;
                    o_leste->write(tmp);
                } else {
                        //Saida de Debug
                    if(debug>=2)
						cout << "["<< this->name() << "]:(Saida de Debug) Achou o elemento de roteamento." << " ID de origem: " << tmp.range(18, 16) << "\n";
                    o_decod->write(tmp);
                }
                    //Se o roteador de destino do flit esta abaixo do elemento de roteamento em questao
            }else if (said == 0){
                if (x > 0) {
                    x = x - 1;
                        //Saida de Debug
                    if(debug>=2)
						cout <<"["<< this->name() << "]:Saida SUL (Saida de Debug) x: " << tmp.range(15, 8) << " y: "<< tmp.range(7, 0) << " ID de origem: " << tmp.range(18, 16) << "\n";
                    tmp.range(15, 8) = x;
                    o_sul->write(tmp);
                } else if (y > 0) {
                    y = y - 1;
                        //Saida de Debug
                    if(debug>=2)
						cout <<"["<< this->name() << "]:Saida LESTE (Saida de Debug) x: " << tmp.range(15, 8) << " y: "<< tmp.range(7, 0) << " ID de origem: " << tmp.range(18, 16) << "\n";
                    tmp.range(7, 0) = y;
                    o_leste->write(tmp);
                } else {
                        //Saida de Debug
                    if(debug>=2)
                        cout << "["<< this->name() << "]:(Saida de Debug) Achou o elemento de roteamento." << " ID de origem: " << tmp.range(18, 16) << "\n";
                    o_decod->write(tmp);
                }
            }
                //Se o flit entrou pelo elemento de roteamento 2.(Procedimeto analogo ao explicado para a entrada 0)
        }else if (ent == 2){
            if (x > 0) {
                x = x - 1;
                    //Saida de Debug
                if(debug>=2)
                    cout <<"["<< this->name() << "]:Saida NORTE (Saida de Debug) x: " << tmp.range(15, 8) << " y: "<< tmp.range(7, 0) << " ID de origem: " << tmp.range(18, 16) << "\n";
                tmp.range(15, 8) = x;
                o_norte->write(tmp);
            } else if (y > 0) {
                y = y - 1;
                    //Saida de Debug
                if(debug>=2)
                    cout <<"["<< this->name() << "]:Saida LESTE (Saida de Debug) x: " << tmp.range(15, 8) << " y: "<< tmp.range(7, 0) << " ID de origem: " << tmp.range(18, 16) << "\n";
                tmp.range(7, 0) = y;
                o_leste->write(tmp);
            } else {
                    //Saida de Debug
                if(debug>=2)
                    cout << "["<< this->name() << "]:(Saida de Debug) Achou o elemento de roteamento." << " ID de origem: " << tmp.range(18, 16) << "\n";
                o_decod->write(tmp);
            }
                //Se o flit entrou pelo elemento de roteamento 3.(Procedimeto analogo ao explicado para a entrada 0)
        }else if(ent == 3){
            if (x > 0) {
                x = x - 1;
                    //Saida de Debug
                if(debug>=2)
                    cout <<"["<< this->name() << "]:Saida SUL (Saida de Debug) x: " << tmp.range(15, 8) << " y: "<< tmp.range(7, 0) << " ID de origem: " << tmp.range(18, 16) << "\n";
                tmp.range(15, 8) = x;
                o_sul->write(tmp);
            } else if (y > 0) {
                y = y - 1;
                    //Saida de Debug
                if(debug>=2)
                    cout <<"["<< this->name() << "]:Saida OESTE (Saida de Debug) x: " << tmp.range(15, 8) << " y: "<< tmp.range(7, 0) << " ID de origem: " << tmp.range(18, 16) << "\n";
                tmp.range(7, 0) = y;
                o_oeste->write(tmp);
            } else {
                    //Saida de Debug
                if(debug>=2)
                    cout << "["<< this->name() << "]:(Saida de Debug) Achou o elemento de roteamento." << " ID de origem: " << tmp.range(18, 16) << "\n";
                o_decod->write(tmp);
            }
                //Se o flit entrou pelo elemento de roteamento 4.(Procedimeto analogo ao explicado para a entrada 0)
        }else if (ent == 4){
                //Se o roteador de destino do flit esta acima do elemento de roteamento em questao
            if (said == 1){
                if (x > 0) {
                    x = x - 1;
                        //Saida de Debug
                    if(debug>=2)
                        cout <<"["<< this->name() << "]:Saida NORTE (Saida de Debug) x: " << tmp.range(15, 8) << " y: "<< tmp.range(7, 0) << " ID de origem: " << tmp.range(18, 16) << "\n";
                    tmp.range(15, 8) = x;
                    o_norte->write(tmp);
                } else if (y > 0) {
                    y = y - 1;
                        //Saida de Debug
                    if(debug>=2)
                        cout <<"["<< this->name() << "]:Saida OESTE (Saida de Debug) x: " << tmp.range(15, 8) << " y: "<< tmp.range(7, 0) << " ID de origem: " << tmp.range(18, 16) << "\n";
                    tmp.range(7, 0) = y;
                    o_oeste->write(tmp);
                } else {
                        //Saida de Debug
                    if(debug>=2)
                        cout << "["<< this->name() << "]:(Saida de Debug) Achou o elemento de roteamento." << " ID de origem: " << tmp.range(18, 16) << "\n";
                    o_decod->write(tmp);
                }
                    //Se o roteador de destino do flit esta abaixo do elemento de roteamento em questao
            }else if (said == 0){
                if (x > 0) {
                    x = x - 1;
                        //Saida de Debug
                    if(debug>=2)
                        cout <<"["<< this->name() << "]:Saida SUL (Saida de Debug) x: " << tmp.range(15, 8) << " y: "<< tmp.range(7, 0) << " ID de origem: " << tmp.range(18, 16) << "\n";
                    tmp.range(15, 8) = x;
                    o_sul->write(tmp);
                } else if (y > 0) {
                    y = y - 1;
                        //Saida de Debug
                    if(debug>=2)
                        cout <<"["<< this->name() << "]:Saida OESTE (Saida de Debug) x: " << tmp.range(15, 8) << " y: "<< tmp.range(7, 0) << " ID de origem: " << tmp.range(18, 16) << "\n";
                    tmp.range(7, 0) = y;
                    o_oeste->write(tmp);
                } else {
                        //Saida de Debug
                    if(debug>=2)
                        cout << "["<< this->name() << "]:(Saida de Debug) Achou o elemento de roteamento." << " ID de origem: " << tmp.range(18, 16) << "\n";
                    o_decod->write(tmp);
                }
            }
                //Se o flit entrou pelo elemento de roteamento 5.(Procedimeto analogo ao explicado para a entrada 0)
        }else if (ent == 5){
            if (x > 0) {
                x = x - 1;
                    //Saida de Debug
                if(debug>=2)
                    cout <<"["<< this->name() << "]:Saida NORTE (Saida de Debug) x: " << tmp.range(15, 8) << " y: "<< tmp.range(7, 0) << " ID de origem: " << tmp.range(18, 16) << "\n";
                tmp.range(15, 8) = x;
                o_norte->write(tmp);
            } else if (y > 0) {
                y = y - 1;
                    //Saida de Debug
                if(debug>=2)
                    cout <<"["<< this->name() << "]:Saida OESTE (Saida de Debug) x: " << tmp.range(15, 8) << " y: "<< tmp.range(7, 0) << " ID de origem: " << tmp.range(18, 16) << "\n";
                tmp.range(7, 0) = y;
                o_oeste->write(tmp);
            } else {
                    //Saida de Debug
                if(debug>=2)
                    cout << "["<< this->name() << "]:(Saida de Debug) Achou o elemento de roteamento." << " ID de origem: " << tmp.range(18, 16) << "\n";
                o_decod->write(tmp);
            }
        }//fim do algoritmo de roteamento
}
