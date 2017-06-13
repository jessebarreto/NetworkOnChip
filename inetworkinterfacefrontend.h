#ifndef INETWORKINTERFACEFRONTEND_H
#define INETWORKINTERFACEFRONTEND_H

#include <systemc.h>

#include "noc_common.h"

class INetworkInterfaceFrontEnd
{
public:
    /*!
     * \brief This method will be used by the back-end (kernel) to read messages from the front-end (shell).
     * \return
     */
    virtual std::vector<unsigned> getMessage() = 0;

    /*!
     * \brief This method will be used by the back-end (kernel) to send data to the front-end (shell).
     * \param message
     */
    virtual void setMessage(const std::vector<unsigned> &message) = 0;

    /*!
     * \brief This method will be used by the back-end (kernel) to read the message destination to the front-end (shell).
     * \return
     */
    virtual unsigned getDestination() = 0;

    /*!
     * \brief This method will be used by the back-end (kernel) to send the message destination to the front-end (shell).
     * \param
     */
    virtual void setDestination(unsigned destinationId) = 0;

    /*!
     * \brief This method will be used by the back-end (kernel) to read the status from the front-end (shell).
     * \return
     */
    virtual bool getFrontEndReady() = 0;

    /*!
     * \brief This method will be used by the back-end (kernel) to send its ready status to the front-end (shell).
     * \param backEndReadyStatus
     */
    virtual void setBackEndReady(bool backEndReadyStatus) = 0;
};

#endif // INETWORKINTERFACEFRONTEND_H
