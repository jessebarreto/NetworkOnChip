#ifndef ROUTER_H
#define ROUTER_H

#include <systemc.h>

#include "noc_common.h"
#include "routerchannel.h"

/*!
 * \brief The Router class for the NoC.
 */
class Router : public sc_module
{
    SC_HAS_PROCESS(Router);

    /*!
     * \brief Unique identifier for this Router.
     */
    const unsigned _routerId;


    /*!
     * \brief Main thread for the router.
     */
    void _run();

public:
    // Port Connections
    sc_port<RouterChannel> localChannel;
    sc_port<RouterChannel> northChannel;
    sc_port<RouterChannel> southChannel;
    sc_port<RouterChannel> westChannel;
    sc_port<RouterChannel> eastChannel;

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
