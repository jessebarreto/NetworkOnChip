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

#ifndef ROUTER_H
#define ROUTER_H

#include <systemc.h>

#include "noccommon.h"

#include "irouterchannel.h"

/*!
 * \brief The Router class is responsible for routing messages from the IP-Cores inside of the NoC.
 */
class Router : public sc_module
{
    SC_HAS_PROCESS(Router);

    /*!
     * \brief Unique identifier for this Router.
     */
    const unsigned _routerId;

    /*!
     * \brief Buffers used at each channel input.
     */
    std::vector<std::pair<sc_fifo<Flit *> *, Link>> _inputBuffers;

    /*!
     * \brief This events are responsible for synchronize and work as flags to indicate that individual channels
     * can be written.
     */
    sc_event _writeLocal, _writeNorth, _writeSouth, _writeEast, _writeWest;

    /*!
     * \brief Each link hlds where each output channel can read from.
     */
    Link _srcLocal, _srcNorth, _srcSouth, _srcEast, _srcWest;

    /*!
     * \brief This vector of mutex holds whether each output channel is available to be written to.
     */
    std::vector<sc_mutex *> _mutexInputChannels;

    /*!
     * \brief Identification number pf the current link being used by the arbiter.
     */
    int _arbiterLinkId;

    /*!
     * \brief A pair of threads for each read/write channel.
     */
    void _localChannelReadThread();
    void _localChannelWriteThread();
    void _northChannelReadThread();
    void _northChannelWriteThread();
    void _southChannelReadThread();
    void _southChannelWriteThread();
    void _eastChannelReadThread();
    void _eastChannelWriteThread();
    void _westChannelReadThread();
    void _westChannelWriteThread();

    /*!
     * \brief Thread to the arbiter.
     */
    void _arbiterThread();

    /*!
     * \brief This method is responsible for routing a packet to the correct destination channel.
     * \param flit The head flit which holds information about the source and destination of this packet.
     * \return The link which all this packet's flits will be routed.
     */
    Link _routingMethod(Flit *flit);

    /*!
     * \brief Initialize the channel buffer pairs.
     *
     * Note: This method should be called just once at the constructor of a Router object.
     */
    void _initChannelBuffers();

    /*!
     * \brief This method is responsible for read flits from a generic channel.
     * \param inputChannel The input channel used to read the flits.
     * \param localBuffer The internal buffer used to temporary hold the flits.
     * \param localBufferFlitsDstLink The destination identification of the flits inside of the buffer.
     */
    void _readFromChannel(sc_port<IRouterChannel> *inputChannel, sc_fifo<Flit *> *localBuffer, Link &localBufferFlitsDstLink);

public:
    /*!
     * \brief Ports connections to communicate with other routers/NI.
     */
    sc_port<IRouterChannel> localChannelIn, localChannelOut;
    sc_port<IRouterChannel> northChannelIn, northChannelOut;
    sc_port<IRouterChannel> southChannelIn, southChannelOut;
    sc_port<IRouterChannel> westChannelIn, westChannelOut;
    sc_port<IRouterChannel> eastChannelIn, eastChannelOut;

    /*!
     * \brief Router Constructor
     * \param name The router name.
     * \param routerId The unique identifier to this router.
     */
    Router(sc_module_name name, unsigned routerId);

    /*!
     * \brief Router Destructor.
     */
    ~Router();

    /*!
     * \brief Getter to this router name.
     * \return This router name as std::string.
     */
    std::string getName();

    /*!
     * \brief Getter to this router unique identification number.
     * \return This router unique identification name.
     */
    const int getIdNumber();
};

#endif // ROUTER_H
