/******************************************************************************************
 * Universidade de Brasília – UnB
 * Instituto de Ciências Exatas – IE
 * Departamento de Ciência da Computação – CIC
 * Modelagem de Sistemas em Silício – Professor R. Jacobi
 *
 * Projeto: Simple System-C NoC.
 *
 * Nome: Jessé Barreto de Barros, Javier Urresty Sanches, João Carlos Passos
 * Matrícula: 17/0067033
 * Copyright 2017 - All rights reserved
 ******************************************************************************************
*/

#ifndef IROUTERCHANNEL_H
#define IROUTERCHANNEL_H

#include <systemc.h>

#include "flit.h"

/*!
 * \brief The IRouterChannel class is an interface for the \c RouterChannel.
 * This interface is responsible for send/receive Flits between the routers and synchronize them using
 * a simple handshaking protocol.
 */
class IRouterChannel : virtual public sc_interface
{
public:
    /*!
     * \brief Writes a flit to the channel.
     * \param flit A reference to the \c Flit that will be written to the channel.
     */
    virtual void sendFlit(Flit *flit) = 0;

    /*!
     * \brief Reads a flit from the channel.
     * \param flit A reference to the \c Flit that will be read from the channel.
     */
    virtual Flit *receiveFlit() = 0;
};

#endif // IROUTERCHANNEL_H
