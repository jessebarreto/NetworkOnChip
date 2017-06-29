#ifndef IROUTERCHANNEL_H
#define IROUTERCHANNEL_H

#include <systemc.h>

#include "flit.h"

/*!
 * \brief The IRouterChannel class is an interface for the \c RouterChannel.
 * This interface is responsible for send/receive Flits between the routers and synchronize them using
 * a simple handshaking protocol.
 */
class IRouterChannel : virtual public sc_interface
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
    virtual Flit *receiveFlit() = 0;
};

#endif // IROUTERCHANNEL_H
