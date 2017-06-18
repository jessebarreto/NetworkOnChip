#ifndef INETWORKINTERFACEFRONTEND_H
#define INETWORKINTERFACEFRONTEND_H

#include <systemc.h>

#include "noccommon.h"

/*!
 * \brief The INetworkInterfaceFrontEnd class is an Interface for a FrontEnd (Shell) module which works as a connection
 * bridge between a custom Processor Element (IP-Core) and a NetworkInteface module of the Network on Chip.
 */
class INetworkInterfaceFrontEnd
{
public:
    virtual void sendMessage(std::vector<unsigned> *message) = 0;

    virtual void receiveMessage(std::vector<unsigned> *message) = 0;

    virtual void sendMessageDestination(unsigned *destinationId) = 0;

    virtual void receiveMessageSource(unsigned *sourceId) = 0;

    virtual const sc_event &sendFrontEndValidEvent() = 0;

    virtual const sc_event &sendFrontEndAckEvent() = 0;

    virtual void receiveBackEndValidEvent() = 0;

    virtual void receiveBackEndAcknowledgeEvent() = 0;
};

#endif // INETWORKINTERFACEFRONTEND_H
