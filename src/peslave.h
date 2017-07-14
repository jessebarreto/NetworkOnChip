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

#ifndef PESLAVE_H
#define PESLAVE_H

#include <systemc.h>

/*!
 * \brief The ProcessorElementSlave class is responsible for testing the NoC connections.
 * It works as a slave module connected to the NoC receiving number and replying letters to a master module.
 */
class ProcessorElementSlave : public sc_module
{
    SC_HAS_PROCESS(ProcessorElementSlave);

    /*!
     * \brief The initial character which will be sent to a master module.
     */
    char _send;

    /*!
     * \brief The position of this module in the NoC.
     */
    unsigned _position;

    /*!
     * \brief The position of this module's master.
     */
    unsigned _masterPosition;

    /*!
     * \brief Thread used to simulate the behaviour of this module.
     */
    void _threadRun();

public:
    /*!
     * \brief ProcessorElementSlave Constructor.
     * \param name The name of this module.
     * \param position The position of this module.
     * \param masterPosition The position of the master which this module will connect with.
     * \param letter The initial character which this module will reply to a master module.
     * As this module reply the character changes.
     */
    ProcessorElementSlave(sc_module_name name, unsigned position, unsigned masterPosition, char letter);

    // IO
    sc_fifo_out<char> slaveOut;
    sc_fifo_in<int> slaveIn;
};

#endif // PESLAVE_H
