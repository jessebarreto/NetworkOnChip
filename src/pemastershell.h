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

#ifndef PEMASTERSHELL_H
#define PEMASTERSHELL_H

#include <systemc.h>

#include "networkinterfacefrontendbase.h"

/*!
 * \brief The ProcessorElementMasterShell class is responsible to work as a shell (front-end) to the connection between
 * a \c ProcessorElementMaster and a default \c NetworkInterface.
 */
class ProcessorElementMasterShell : public sc_module, public NetworkInterfaceFrontEndBase
{
    SC_HAS_PROCESS(ProcessorElementMasterShell);

    /*!
     * \brief The thread to simulate this module behaviour.
     */
    void _threadRun();

    /*!
     * \brief The position of this module to the NoC.
     */
    unsigned _position;

    /*!
     * \brief The position of the slave module to the master element connected to this shell.
     */
    unsigned _slavePosition;

public:
    // IO
    sc_fifo_in<int> shellIn;
    sc_fifo_out<char> shellOut;

    /*!
     * \brief ProcessorElementMasterShell Constructor
     * \param name The name of this shell.
     * \param position The position which this module is in the NoC.
     * \param slavePosition The position of the slave module which this module's master element will
     * send/receive payloads.
     */
    ProcessorElementMasterShell(sc_module_name name, unsigned position, unsigned slavePosition);
};

#endif // PEMASTERSHELL_H
