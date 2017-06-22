#ifndef INETWORKINTERFACEFRONTEND_H
#define INETWORKINTERFACEFRONTEND_H

#include <systemc.h>

#include "noccommon.h"

/*!
 * \brief The INetworkInterfaceFrontEnd class is an Interface for a FrontEnd (Shell) module which works as a connection
 * bridge between a custom Processor Element (IP-Core) and a NetworkInteface module of the Network on Chip.
 *
 * Note: It's expected from a classe that implements this class to have four basic events to handle the communication
 * between the front-end and the back-end. This event are:
 *      * frontEndValidEvent    - Used to signal that the front-end is ready to send a message.
 *      * frontEndAckEvent      - Used to signal that the front-end has received a message
 *      * backEndValidEvent     - Used to signal that the back-end is ready to send a message.
 *      * backEndAckEvent       - Used to signal that the back-end has received a message.
 */
class INetworkInterfaceFrontEnd
{
public:
    /*!
     * \brief The front-end sends a message to the back-end.
     * \param message The message to be sent.
     */
    virtual void sendMessage(std::vector<uint32_t> *message) = 0;

    /*!
     * \brief The front-end receives a message to the back-end.
     * \param message The message to be received.
     */
    virtual void receiveMessage(std::vector<uint32_t> *message) = 0;

    /*!
     * \brief The front-end sends the message's destination identification number.
     * \param destinationId The message's destination.
     */
    virtual void sendMessageDestination(unsigned *destinationId) = 0;

    /*!
     * \brief The front-end receives the message's source identification number.
     * \param sourceId The message's source identification.
     */
    virtual void receiveMessageSource(unsigned *sourceId) = 0;

    /*!
     * \brief The front-end sends an event to inform that its ready to send a message.
     * \return The valid event.
     */
    virtual const sc_event &sendFrontEndValidEvent() = 0;

    /*!
     * \brief The front-end sends an event to inform that it has received a message from the back-end.
     * \return The acknowledge event.
     */
    virtual const sc_event &sendFrontEndAcknowledgeEvent() = 0;

    /*!
     * \brief The front-end receives from the back-end an event informing that its ready to send a message.
     */
    virtual void receiveBackEndValidEvent() = 0;

    /*!
     * \brief The front-end receives from the back-end an event informing that it has received a messsage.
     */
    virtual void receiveBackEndAcknowledgeEvent() = 0;
};

#endif // INETWORKINTERFACEFRONTEND_H
