#include "networkinterfacefrontendbase.h"

void NetworkInterfaceFrontEndBase::sendMessage(std::vector<uint32_t> *message)
{
    *message = _message;
}

void NetworkInterfaceFrontEndBase::receiveMessage(std::vector<uint32_t> *message)
{
    _message = *message;
}

void NetworkInterfaceFrontEndBase::sendMessageDestination(unsigned *destinationId)
{
    *destinationId = _msgDestination;
}

void NetworkInterfaceFrontEndBase::receiveMessageSource(unsigned *sourceId)
{
    _msgSource = *sourceId;
}

const sc_event &NetworkInterfaceFrontEndBase::sendFrontEndValidEvent()
{
    return _frontEndValid;
}

const sc_event &NetworkInterfaceFrontEndBase::sendFrontEndAcknowledgeEvent()
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
    _frontEndAcknowledge.notify();
}

const sc_event &NetworkInterfaceFrontEndBase::backEndReceivedEvent()
{
    return _backEndAcknowledge;
}

const sc_event &NetworkInterfaceFrontEndBase::backEndSendEvent()
{
    return _backEndValid;
}
