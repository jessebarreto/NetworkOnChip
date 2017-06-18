#include "networkinterface.h"

NetworkInterface::NetworkInterface(sc_module_name name, unsigned id) :
    sc_module(name),
    _networkInterfaceId(id),
    _frontEnd(nullptr)
{
    SC_THREAD(_threadRead);
    SC_THREAD(_threadWrite);
}

void NetworkInterface::connectFrontEnd(INetworkInterfaceFrontEnd *networkInterfaceFrontEnd)
{
    _frontEnd = networkInterfaceFrontEnd;
}

void NetworkInterface::_threadRead()
{
    if (!_frontEnd) {
        std::string message("Front-End Not Connected NI-Id:");
        NoCDebug::printDebug(message + std::to_string(_networkInterfaceId) + " Name: " + name(), NoCDebug::NI, true);
    }
    for (;;) {
        // Wait front-end valid event be notified
        wait(_frontEnd->sendFrontEndValidEvent());

        // Receive Message
        std::vector<unsigned> *receivedMessage;
        _frontEnd->sendMessage(receivedMessage);

        // Packet Message
        _packetMessage(*receivedMessage);

        // Send to Router
        _sendToRouter();

        // Send back-end acknowledge event
        _frontEnd->receiveBackEndAcknowledgeEvent();
    }
}

void NetworkInterface::_threadWrite()
{

}

void NetworkInterface::_packetMessage(const std::vector<unsigned> &message)
{
    NoCDebug::printDebug("NI-ID:" + std::to_string(_networkInterfaceId) + " packeting message.", NoCDebug::NI);
}

const std::vector<unsigned> &NetworkInterface::_unpackMessage()
{

}

void NetworkInterface::_sendToRouter()
{

}

