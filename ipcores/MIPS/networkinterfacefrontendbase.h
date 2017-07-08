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
     * \brief A message member which can be used for send/receive messages to/from the back-end module.
     */
    std::vector<uint32_t> _payload;

    /*!
     * \brief A member used to hold a identification number when sending messages.
     */
    unsigned _payloadDst;

    /*!
     * \brief A member used to hold a identification number when receiving messages.
     */
    unsigned _payloadSrc;

    /*!
     * \brief Synchronizing events and flags.
     */
    sc_event _ack, _valid;
    bool _ackFlag, _validFlag;
    sc_event _writing, _reading;
    bool _writingFlag, _readingFlag;

protected:
    /*!
     * \brief This class constructor.
     */
    NetworkInterfaceFrontEndBase();

    /*!
     * \brief This method sends a payload from the shell to the kernel.
     * \param payload The payload to be sent.
     * \param dst The destination of this payload.
     */
    void sendPayload(const std::vector<uint32_t> &payload, int dst);

    /*!
     * \brief This method receives a payload to the shell from the kernel.
     * \param payload The payload to be received.
     * \param src the source of this payload.
     */
    void receivePayload(std::vector<uint32_t> &payload, int *src);
public:
    /*!
     * \brief This method shouldn't not be used by the shell.
     * Note: Please, do not use it by the shell.
     */
    void kernelReceivePayload(std::vector<uint32_t> &payload, int *dst) override;

    /*!
     * \brief This method shouldn't not be used by the shell.
     * Note: Please, do not use it by the shell.
     */
    void kernelSendPayload(const std::vector<uint32_t> &payload, int *src) override;
};

#endif // NETWORKINTERFACEFRONTENDBASE_H
