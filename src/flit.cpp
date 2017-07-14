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

#include "flit.h"

uint64_t Flit::_globalFlitCounter = 0;

Flit::Flit(flit_t data, uint64_t packetId) :
    _globalId(_globalFlitCounter),
    _data(data),
    _packetId(packetId)
{
    // Count the flits
    _globalFlitCounter++;
}

flit_t Flit::getData()
{
    return _data;
}

void Flit::setData(flit_t data)
{
    _data = data;
}

uint64_t Flit::getUniqueId()
{
    return _globalId;
}

uint64_t Flit::getPacketId()
{
    return _packetId;
}
