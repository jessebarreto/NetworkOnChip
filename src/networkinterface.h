#ifndef NETWORKINTERFACE_H
#define NETWORKINTERFACE_H

#include <systemc.h>

#include "flit.h"
#include "inetworkinterfacefrontend.h"
#include "irouterchannel.h"

/*!
 * \brief The NetworkInterface class is responsible for connecting a Processor element to its router which are connect
 * to the Network. It works basically as a connection element between the PE and the NoC.
 */
class NetworkInterface : public sc_module
{
    SC_HAS_PROCESS(NetworkInterface);

    /*!
     * \brief Unique identifier for this Network Interface.
     */
    const unsigned _networkInterfaceId;

    /*!
     * \brief The wrapper between the PE and the common implemented Network Interface.
     */
    INetworkInterfaceFrontEnd* _frontEnd;

    /*!
     * \brief The packet to be sent to the NoC.
     */
    std::vector<Flit *> _sendPacket;

    /*!
     * \brief The packet to be received from the NoC.
     */
    std::vector<Flit *> _receivePacket;

    sc_mutex _keyThread;

    /*!
     * \brief Thread to read data from the shell.
     */
    void _threadReadFromShell();

    /*!
     * \brief Thread to write data to the shell.
     */
    void _threadWriteToShell();

    /*!
     * \brief This method is used to pack the payload to be sent as packet of flits through the
     * NoC.
     * \param destinationId The destination to this payload.
     * \param payload the payload data.
     */
    void _packMessage(unsigned destinationId, const std::vector<uint32_t> &payload);

    /*!
     * \brief This method is used to unpack a packet of flits received from the NoC as a payload.
     * \param sourceId The source of this payload.
     * \param payload The payload data.
     */
    const void _unpackMessage(int *sourceId, std::vector<uint32_t> *payload);

    /*!
     * \brief This method is used to send a packet of flits to the NoC.
     */
    void _sendToRouter();

    /*!
     * \brief This method is used to receive a packet of flits from the NoC.
     */
    void _receiveFromRouter();

public:
    // IO
    sc_port<IRouterChannel> localChannelIn, localChannelOut;

    /*!
     * \brief Constructor
     * \param name The name of this module.
     * \param id the identification number of this module.
     */
    NetworkInterface(sc_module_name name, unsigned id);

    /*!
     * \brief This method is used to connect a shell to the kernel.
     * \param networkInterfaceFrontEnd A reference of to the shell module.
     */
    void connectFrontEnd(INetworkInterfaceFrontEnd *networkInterfaceFrontEnd);
};

#endif // NETWORKINTERFACE_H
