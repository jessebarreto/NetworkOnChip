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
 *      1. Sender sends data using sendFlit().
 *      2. Receiver receives data using receiveFlit().
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

    /*!
     * \brief This event notifies the channel that a module is sending a flit to it.
     */
    sc_event _valid;

    /*!
     * \brief This event notifies the channel that a module sending data has been read by a receiver
     * module.
     */
    sc_event _acknowledge;

    /*!
     * \brief This event notifies the channel that it is busy.
     */
    sc_event _busy;

    /*!
     * \brief This flag hlds whether the channel is valid.
     */
    bool _validFlag;

    /*!
     * \brief This flag holds whether the channel is acknowled.
     */
    bool _acknowledgeFlag;

    /*!
     * \brief This flag holds whether the channel is busy.
     */
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
