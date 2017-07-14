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

#ifndef PENULL_H
#define PENULL_H

#include <systemc.h>

/*!
 * \brief The ProcessorElementNull class is a dummy empty module. Used only to test the connection of the NoC to
 * an empty element.
 */
class ProcessorElementNull : public sc_module
{
    SC_HAS_PROCESS(ProcessorElementNull);

    /*!
     * \brief Position of the element in the NoC.
     */
    unsigned _position;
public:
    /*!
     * \brief ProcessorElementNull Constructor.
     * \param name The name of this module.
     * \param position The position of this module in the NoC.
     */
    ProcessorElementNull(sc_module_name name, unsigned position);
};

#endif // PENULL_H
