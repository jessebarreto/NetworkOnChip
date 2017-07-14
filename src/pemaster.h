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

#ifndef PEMASTER_H
#define PEMASTER_H

#include <systemc.h>

/*!
 * \brief The ProcessorElementMaster class is responsible for testing the NoC connections.
 * It works as a master module connected to the NoC sending numbers and waiting for letters from a slave module.
 */
class ProcessorElementMaster : public sc_module
{
    SC_HAS_PROCESS(ProcessorElementMaster);

    /*!
     * \brief The data which will be send through the NoC.
     */
    int *data;

    /*!
     * \brief The identification number which holds the position of this module.
     */
    unsigned _position;

    /*!
     * \brief The identification number which holds the position of the slave module that this module will
     * send and receive payloads.
     */
    unsigned _slavePosition;

    /*!
     * \brief Thread used to simulate the behaviour of this module.
     */
    void _threadRun();

public:
    /*!
     * \brief ProcessorElementMaster Constructor.
     * \param name The name of this module.
     * \param position The position in the NoC.
     * \param slavePosition The position of the slave which this module will connect with.
     */
    ProcessorElementMaster(sc_module_name name, unsigned position, unsigned slavePosition);

    /*!
     * \brief IO Ports
     */
    sc_fifo_out<int> masterOut;
    sc_fifo_in<char> masterIn;
};

#endif // PEMASTER_H
