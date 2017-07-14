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

#ifndef NOCROUTING_H
#define NOCROUTING_H

#include "noccommon.h"

/*!
 * \brief This function implements a routing XY algorithm.
 * \param source Position of the current router.
 * \param dest  Position of the destination router.
 */
routingInfo routingXY(unsigned source, unsigned dest);

/*!
 * \brief This function implements a routing YX algorithm.
 * \param source Position of the current router.
 * \param dest  Position of the destination router.
 */
routingInfo routingYX(unsigned source, unsigned dest);

/*!
 * \brief Function to test the routing algorithms.
 * \param source Position of the current router.
 * \param dest  Position of the destination router.
 */
void routingTest(unsigned source, unsigned dest);

#endif // NOCROUTING_H
