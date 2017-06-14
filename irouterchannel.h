#ifndef IROUTERCHANNEL_H
#define IROUTERCHANNEL_H

#include <systemc.h>

#include "noc_common.h"

/*!
 * \brief The IRouterChannel class is an interface for the \c RouterChannel.
 * This interface is responsible for send/receive Flits between the routers and synchronize them using
 * a simple handshaking protocol.
 */
class IRouterChannel : public sc_interface
{
public:
    /*!
     * \brief Writes a flit to the channel.
     * \param flit A reference to the \c Flit that will be written to the channel.
     */
    virtual void sendFlit(Flit *flit) = 0;

    /*!
     * \brief Reads a flit from the channel.
     * \param flit A reference to the \c Flit that will be read from the channel.
     */
    virtual void receiveFlit(Flit *flit) = 0;

    /*!
     * \brief This method should be called by the sender when it's ready to send data.
     */
    virtual void validSender() = 0;

    /*!
     * \brief This method should be called by the receiver when it's ready to receive data.
     */
    virtual void validReceiver() = 0;

    /*!
     * \brief This method returns a reference of the acknowledge event from the channel to the sender.
     * \return A reference to the acknowledge event to the sender.
     */
    virtual sc_event *acknowledgeSender() = 0;

    /*!
     * \brief This method returns a reference of the acknowledge event from the channel to the receiver.
     * \return A reference to the acknowledge event to the receiver.
     */
    virtual sc_event *acknowledgeReceiver() = 0;
};

#endif // IROUTERCHANNEL_H
