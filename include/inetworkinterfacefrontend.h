#ifndef INETWORKINTERFACEFRONTEND_H
#define INETWORKINTERFACEFRONTEND_H

#include <systemc.h>

#include <vector>

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
    virtual void kernelReceivePayload(std::vector<uint32_t> &payload, int *dst) = 0;

    virtual void kernelSendPayload(const std::vector<uint32_t> &payload, int *src) = 0;
};

#endif // INETWORKINTERFACEFRONTEND_H
