#ifndef ROUTERCHANNEL_H
#define ROUTERCHANNEL_H

#include <systemc.h>

#include "irouterchannel.h"
#include "flit.h"

/*!
 * \brief The RouterChannel class which is responsible for connecting routers and network interface modules and transmit
 * data back and forth between these routers.
 *
 * Note: To use the router channel it's necessary to follow the following steps:
 *      1. Sender calls validSender.
 *      2. Sender calls sendFlit.
 *      3. (Optional) Sender waits for acknowledge status from channel - calling acknowledgeSender.
 *
 *      4. Receiver calls validReceiver.
 *      5. Receiver calls receiveFlit.
 *      6. (Optional) Receiver waits for acknowledge status from channel - calling acknowledgeReceiver.
 */
class RouterChannel : public IRouterChannel, public sc_prim_channel
{
    /*!
     * \brief The channel unique identification number in the NoC.
     */
    const unsigned _channelId;

    /*!
     * \brief It counts the number of channels in the system.
     */
    static unsigned _channelCounter;

    /*!
     * \brief The \c Flit which will be transmitted from the sender to the receiver.
     */
    Flit* _transmittedFlit;

    sc_event _valid, _acknowledge, _busy;

    bool _busyFlag;

public:
    /*!
     * \brief Default Constructor
     * \param name The channel name
     * \param id The unique channel id
     */
    RouterChannel(const sc_module_name &name);

    /*!
     * \brief Getter to this channel name.
     * \return The channel name.
     */
    std::string getName();

    /*!
     * \brief Getter to this channel unique identification name.
     * \return The channel id number.
     */
    unsigned getChannelId();

    void sendFlit(Flit *flit) override;

    Flit *receiveFlit() override;
};

#endif // ROUTERCHANNEL_H
