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

#include "peslave.h"

#include "nocdebug.h"

ProcessorElementSlave::ProcessorElementSlave(sc_module_name name, unsigned position, unsigned masterPosition, char letter) :
    _position(position),
    _masterPosition(masterPosition),
    _send(letter)
{
    NoCDebug::printDebug(std::string("> Slave: S" + std::to_string(_position) + "M" + std::to_string(_masterPosition)), NoCDebug::Assembly);
    SC_THREAD(_threadRun);

}

void ProcessorElementSlave::_threadRun()
{
    for (;;) {
        int read = slaveIn.read();
        NoCDebug::printDebug("S" + std::to_string(_position) + "M" + std::to_string(_masterPosition) + ": Slave <- SShell       DATA: " + std::to_string(read), NoCDebug::PE);
        NoCDebug::printDebug("S" + std::to_string(_position) + "M" + std::to_string(_masterPosition) + ": Slave -> SShell", NoCDebug::PE);
        slaveOut.write(_send++);
    }
}
