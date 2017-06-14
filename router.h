#ifndef ROUTER_H
#define ROUTER_H

#include <systemc.h>

#include "noc_common.h"
#include "routerchannel.h"

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
     * \brief Thread to read each channel
     */
    void _localChannelThread();
    void _northChannelThread();
    void _southChannelThread();
    void _eastChannelThread();
    void _westChannelThread();

public:
    // Port Connections
    sc_port<IRouterChannel> localChannel;
    sc_port<IRouterChannel> northChannel;
    sc_port<IRouterChannel> southChannel;
    sc_port<IRouterChannel> westChannel;
    sc_port<IRouterChannel> eastChannel;

    /*!
     * \brief Router Constructor
     * \param name the module name.
     * \param routerId The unique identifier to this router.
     */
    Router(sc_module_name name, unsigned routerId);

    std::string getName();

    const int getIdNumber();
};

#endif // ROUTER_H
