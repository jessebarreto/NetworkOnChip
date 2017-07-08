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
 *      * valid       - Used to signal that the back-end has write to the front-end.
 *      * ack         - Used to signal that the back-end has read from the front-end.
 *      * writing     - Used to signal that the front-end is writing to the back-end.
 *      * reading     - Used to signal that the front-end is reading from the back-end.
 */
class INetworkInterfaceFrontEnd
{
public:
    /*!
     * \brief This method is used by the kernel to receive data from the shell.
     * Note: The shell has access to this method.
     *       Please, do not call it from the shell.
     * \param payload the data to be read by the kernel from the shell.
     * \param dst The destination of this data.
     */
    virtual void kernelReceivePayload(std::vector<uint32_t> &payload, int *dst) = 0;

    /*!
     * \brief This method is used by the kernel to send data to the shell.
     * Note: The shell has access to this method.
     *       Please, do not call it from the shell.
     * \param payload the data to be write by the kernel to the shell.
     * \param src The source of this data.
     */
    virtual void kernelSendPayload(const std::vector<uint32_t> &payload, int *src) = 0;
};

#endif // INETWORKINTERFACEFRONTEND_H
