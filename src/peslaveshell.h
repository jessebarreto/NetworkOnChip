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

#ifndef PESLAVESHELL_H
#define PESLAVESHELL_H

#include <systemc.h>

#include "networkinterfacefrontendbase.h"

/*!
 * \brief The ProcessorElementSlaveShell class is responsible to work as a shell (front-end) to the connection between
 * a \c ProcessorElementSlave and a default \c NetworkInterface.
 */
class ProcessorElementSlaveShell : public sc_module, public NetworkInterfaceFrontEndBase
{
    SC_HAS_PROCESS(ProcessorElementSlaveShell);

    /*!
     * \brief The thread used to simulate this module behaviour.
     */
    void _threadRun();

    /*!
     * \brief The position of this module to the NoC.
     */
    unsigned _position;

    /*!
     * \brief The position of the master slave to the slave element connected to this shell.
     */
    unsigned _masterPosition;

public:
    // IO
    sc_fifo_in<char> shellIn;
    sc_fifo_out<int> shellOut;

    /*!
     * \brief ProcessorElementSlaveShell Constructor.
     * \param name The name of this shell.
     * \param position The position which this module is in the NoC.
     * \param masterPosition The position of the master module which this module's slave element will
     * send/receive payloads.
     */
    ProcessorElementSlaveShell(sc_module_name name, unsigned position, unsigned masterPosition);
};

#endif // PESLAVESHELL_H
