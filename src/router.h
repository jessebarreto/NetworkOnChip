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

    sc_event _writeLocal, _writeNorth, _writeSouth, _writeEast, _writeWest;
    Link _srcLocal, _srcNorth, _srcSouth, _srcEast, _srcWest;

    /*!
     * \brief A pair of threads for each channel.
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
     * \brief _routingMethod
     * \param flit
     * \param dst
     */
    Link _routingMethod(Flit *flit);

    void _initChannelBuffers();

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
