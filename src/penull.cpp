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

#include "penull.h"

#include "nocdebug.h"

ProcessorElementNull::ProcessorElementNull(sc_module_name name, unsigned position) :
    _position(position)
{
    NoCDebug::printDebug(std::string("> Null: N" + std::to_string(_position)), NoCDebug::Assembly);
}
