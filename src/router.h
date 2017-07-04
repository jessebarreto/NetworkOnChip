#ifndef ROUTER_H
#define ROUTER_H

#include <systemc.h>

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
     * \brief Threads to for each channel.
     */
    void _localChannelThread();
    void _northChannelThread();
    void _southChannelThread();
    void _eastChannelThread();
    void _westChannelThread();

public:
    /*!
     * \brief Ports connections to communicate with other routers/NI.
     */
    sc_port<IRouterChannel> localChannel;
    sc_port<IRouterChannel> northChannel;
    sc_port<IRouterChannel> southChannel;
    sc_port<IRouterChannel> westChannel;
    sc_port<IRouterChannel> eastChannel;

    /*!
     * \brief Router Constructor
     * \param name The router name.
     * \param routerId The unique identifier to this router.
     */
    Router(sc_module_name name, unsigned routerId);

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
    
    void routing();
    
    void arbitrer();
    
    
};

#endif // ROUTER_H
