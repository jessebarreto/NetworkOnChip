#ifndef IROUTERCHANNEL_H
#define IROUTERCHANNEL_H

#include <systemc.h>

#include "noc_common.h"

/*!
 * \brief The IRouterChannel class is an interface for the \c RouterChannel.
 * This interface is responsible for send/receive data between the routers and synchronize them.
 */
class IRouterChannel : public virtual sc_interface
{
public:
    /*!
     * \brief Write a valid event when the flit being sent is valid.
     */
    virtual void writeValid() = 0;

    /*!
     * \brief Read a valid event for a router wait.
     * \return the valid event.
     */
    virtual sc_event &readValid() = 0;

    /*!
     * \brief Write an acknowledge event to inform a router that the sent flit arrived with success.
     */
    virtual void writeAcknowledge() = 0;

    /*!
     * \brief Read an acknowledge event.
     * \return the acknowledge event.
     */
    virtual sc_event &readAcknowledge() = 0;

    /*!
     * \brief Write a flit.
     * \param flit The flit to be sent.
     */
    virtual void writeFlit(flit_t &flit) = 0;

    /*!
     * \brief Read a flit.
     * \return The flit being read.
     */
    virtual flit_t &readFlit() = 0;
};

#endif // IROUTERCHANNEL_H
