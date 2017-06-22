#ifndef NETWORKINTERFACEFRONTENDBASE_H
#define NETWORKINTERFACEFRONTENDBASE_H

#include <systemc.h>

#include "inetworkinterfacefrontend.h"

/*!
 * \brief The NetworkInterfaceFrontEndBase class is a Base class that can be used both as an example of how to create a
 * front-end (shell module) to a IP-core or used directly as a Base class for a front-end.
 * It implements the methods from the interface of NetworkInterfaceFrontEnd and also has the obligatory events
 * necessaries for the communication between the front-end and back-end module.
 *
 * It has more easy to use methods for the communication and a message member which can be used for transmission of
 * messages.
 */
class NetworkInterfaceFrontEndBase : public INetworkInterfaceFrontEnd
{
    /*!
     * \brief An event to inform that the front-end module is ready to send a message.
     */
    sc_event _frontEndValid;

    /*!
     * \brief An event to inform that the front-end module has received a message.
     */
    sc_event _frontEndAcknowledge;

    /*!
     * \brief An event to inform that the back-end module is ready to send a message.
     */
    sc_event _backEndValid;
    /*!
     * \brief An event to inform that the back-end module has received a message.
     */
    sc_event _backEndAcknowledge;
protected:
    /*!
     * \brief A message member which can be used for send/receive messages to/from the back-end module.
     */
    std::vector<uint32_t> _message;

    /*!
     * \brief A member used to hold a identification number when sending messages.
     */
    unsigned _msgDestination;

    /*!
     * \brief A member used to hold a identification number when receiving messages.
     */
    unsigned _msgSource;

public:
    void sendMessage(std::vector<uint32_t> *message) override;

    void receiveMessage(std::vector<uint32_t> *message) override;

    void sendMessageDestination(unsigned *destinationId) override;

    void receiveMessageSource(unsigned *sourceId) override;

    const sc_event &sendFrontEndValidEvent() override;

    const sc_event &sendFrontEndAcknowledgeEvent() override;

    void receiveBackEndValidEvent() override;

    void receiveBackEndAcknowledgeEvent() override;

    /*!
     * \brief This method is used to notify the front-end's valid event.
     * This event informs that the front-end is ready to send a message.
     */
    void frontEndSendEvent();

    /*!
     * \brief This method is used to notify the front-end's acknowledge event.
     * This event informs that the front-end has received a message.
     */
    void frontEndReceivedEvent();

    /*!
     * \brief This method is used to wait the back-end's acknowledge event.
     * This event informs that the back-end has received a message.
     * \return
     */
    const sc_event &backEndReceivedEvent();

    /*!
     * \brief This method is used to wait the back-end's valid event.
     * This event informs that the back-end's is ready to send an event.
     * \return
     */
    const sc_event &backEndSendEvent();
};

#endif // NETWORKINTERFACEFRONTENDBASE_H
