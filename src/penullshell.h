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

#ifndef PENULLSHELL_H
#define PENULLSHELL_H

#include <systemc.h>

#include "networkinterfacefrontendbase.h"

/*!
 * \brief The ProcessorElementNullShell class is responsible to connect an empty module's shell to the NoC.
 */
class ProcessorElementNullShell : public sc_module, public NetworkInterfaceFrontEndBase
{
    SC_HAS_PROCESS(ProcessorElementNullShell);

    /*!
     * \brief Position of the PE in the NoC.
     */
    unsigned _position;

public:
    /*!
     * \brief ProcessorElementNullShell Constructor
     * \param name The name of this shell.
     * \param position The position of this shell.
     */
    ProcessorElementNullShell(sc_module_name name, unsigned position);
};

#endif // PENULLSHELL_H
