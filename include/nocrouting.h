#ifndef NOCROUTING_H
#define NOCROUTING_H

#include "noccommon.h"

/*!
 * \brief Routing XY
 * \param source Position of the current router.
 * \param dest  Position of the destination router.
 */
routingInfo routingXY(unsigned source, unsigned dest);

/*!
 * \brief Routing XY
 * \param source Position of the current router.
 * \param dest  Position of the destination router.
 */
routingInfo routingYX(unsigned source, unsigned dest);

/*!
 * \brief Function to test the routing algorithm
 * \param source Position of the current router.
 * \param dest  Position of the destination router.
 */
void routingTest(unsigned source, unsigned dest);

#endif // NOCROUTING_H
