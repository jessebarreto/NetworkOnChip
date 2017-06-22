#ifndef ROUTERCHANNEL_H
#define ROUTERCHANNEL_H

#include <systemc.h>

#include "noccommon.h"
#include "irouterchannel.h"

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
class RouterChannel : public sc_channel, public IRouterChannel
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

    /*!
     * \brief The event that indicates that the \c Flit being sent is valid.
     * That is the producer signal to the channel.
     */
    sc_event _writeValid;

    /*!
     * \brief The event that indicates that \c Flit being sent was acknowledge by the channel.
     * That is the channel signal to the producer.
     */
    sc_event _writeAcknowledged;

    /*!
     * \brief The event that indicates that \c Flit being sent was validated by the channel to be send.
     * That is the channel signal to the consumer.
     */
    sc_event _readValid;

    /*!
     * \brief The event that indicates that \c Flit being sent was received by the receiver.
     * That is the consumer signal to the channel.
     */
    sc_event _readAcknowledged;

    bool __readValid, __readAck, __writeValid, __writeAck;
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

    void receiveFlit(Flit *flit) override;

    void validSender() override;

    void validReceiver() override;

    sc_event *acknowledgeSender() override;

    sc_event *acknowledgeReceiver() override;
};

#endif // ROUTERCHANNEL_H
