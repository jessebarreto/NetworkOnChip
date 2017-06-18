#ifndef NETWORKINTERFACEFRONTENDBASE_H
#define NETWORKINTERFACEFRONTENDBASE_H

#include <systemc.h>

#include "inetworkinterfacefrontend.h"

class NetworkInterfaceFrontEndBase : public INetworkInterfaceFrontEnd
{
    sc_event _frontEndValid;
    sc_event _frontEndAcknowledge;
    sc_event _backEndValid;
    sc_event _backEndAcknowledge;
protected:
    std::vector<unsigned> _message;

    unsigned _msgDestination, _msgSource;

public:
    void sendMessage(std::vector<unsigned> *message) override;

    void receiveMessage(std::vector<unsigned> *message) override;

    void sendMessageDestination(unsigned *destinationId) override;

    void receiveMessageSource(unsigned *sourceId) override;

    const sc_event &sendFrontEndValidEvent() override;

    const sc_event &sendFrontEndAckEvent() override;

    void receiveBackEndValidEvent() override;

    void receiveBackEndAcknowledgeEvent() override;

    void frontEndSendEvent();

    void frontEndReceivedEvent();

    const sc_event &backEndReceivedEvent();

    const sc_event &backEndSendEvent();
};

#endif // NETWORKINTERFACEFRONTENDBASE_H
