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
     * \brief Synchronizing events.
     */
    sc_event _ack, _valid, _writing, _reading;

    /*!
     * \brief Synchronizing flags.
     */
    bool _ackFlag, _validFlag, _writingFlag, _readingFlag;

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
     * \brief This method is used by the kernel to receive a payload from the shell.
     * This method should not be used by the shell.
     * Note: Please, do not use it by the shell.
     */
    void kernelReceivePayload(std::vector<uint32_t> &payload, int *dst) override;

    /*!
     * \brief This method is used by the kernel to send a payload to the shell.
     * This method should not be used by the shell.
     * Note: Please, do not use it by the shell.
     */
    void kernelSendPayload(const std::vector<uint32_t> &payload, int *src) override;

    /*!
     * \brief This method is used by the kernel to get whether the shell has a read request from it.
     * This method should not be used by the shell.
     * Note: Please, do not use it by the shell.
     * \return A boolean flag which indicates whether the shell has a read request from the kernel.
     */
    bool kernelGetFrontEndReadingStatus() override;
};

#endif // NETWORKINTERFACEFRONTENDBASE_H
