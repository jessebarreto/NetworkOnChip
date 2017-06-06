#ifndef ROUTERCHANNEL_H
#define ROUTERCHANNEL_H

#include <systemc.h>

#include "noc_common.h"
#include "irouterchannel.h"

/*!
 * \brief The RouterChannel class is responsible for connecting the routers.
 */
class RouterChannel : public sc_module, public IRouterChannel
{
    SC_HAS_PROCESS(RouterChannel);

    sc_event _validEvent, _ackEvent;
    flit_t _transmitedFlit;

public:
    /*!
     * \brief Default Constructor
     * \param name The module name
     * \param id The unique channel id
     */
    RouterChannel(sc_module_name name);

    void writeValid() override;
    sc_event &readValid() override;
    void writeAcknowledge() override;
    sc_event &readAcknowledge() override;
    void writeFlit(flit_t &flit) override;
    flit_t &readFlit() override;
};

#endif // ROUTERCHANNEL_H
