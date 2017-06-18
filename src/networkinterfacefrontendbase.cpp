#include "networkinterfacefrontendbase.h"

void NetworkInterfaceFrontEndBase::sendMessage(std::vector<unsigned> *message)
{
    message = &_message;
}

void NetworkInterfaceFrontEndBase::receiveMessage(std::vector<unsigned> *message)
{
    _message = *message;
}

void NetworkInterfaceFrontEndBase::sendMessageDestination(unsigned *destinationId)
{
    destinationId = &_msgDestination;
}

void NetworkInterfaceFrontEndBase::receiveMessageSource(unsigned *sourceId)
{
    _msgSource = *sourceId;
}

const sc_event &NetworkInterfaceFrontEndBase::sendFrontEndValidEvent()
{
    return _frontEndValid;
}

const sc_event &NetworkInterfaceFrontEndBase::sendFrontEndAckEvent()
{

    return _frontEndAcknowledge;
}

void NetworkInterfaceFrontEndBase::receiveBackEndValidEvent()
{
    _backEndValid.notify();
}

void NetworkInterfaceFrontEndBase::receiveBackEndAcknowledgeEvent()
{
    _backEndAcknowledge.notify();
}

void NetworkInterfaceFrontEndBase::frontEndSendEvent()
{
    _frontEndValid.notify();
}

void NetworkInterfaceFrontEndBase::frontEndReceivedEvent()
{
    _message.clear();
    _frontEndAcknowledge.notify();
}

const sc_event &NetworkInterfaceFrontEndBase::backEndReceivedEvent()
{
    _message.clear();
    return _backEndAcknowledge;
}

const sc_event &NetworkInterfaceFrontEndBase::backEndSendEvent()
{
    return _backEndValid;
}
