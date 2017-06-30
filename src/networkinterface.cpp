#include "networkinterface.h"

#include "nocdebug.h"

NetworkInterface::NetworkInterface(sc_module_name name, unsigned id) :
    sc_module(name),
    _networkInterfaceId(id),
    _frontEnd(nullptr)
{
    SC_THREAD(_threadReadFromShell);
    SC_THREAD(_threadWriteToShell);
}

void NetworkInterface::connectFrontEnd(INetworkInterfaceFrontEnd *networkInterfaceFrontEnd)
{
    _frontEnd = networkInterfaceFrontEnd;
}

void NetworkInterface::_threadReadFromShell()
{
    if (!_frontEnd) {
        std::string message("Front-End Not Connected NI-Id:");
        NoCDebug::printDebug(message + std::to_string(_networkInterfaceId) + " Name: " + name(), NoCDebug::NI, true);
    } else {
        for (;;) {
            // Receive Message from Front-End
            std::vector<uint32_t> receivedMessage;
            int destinationId;
            _frontEnd->kernelReceivePayload(receivedMessage, &destinationId);

            // Packet Message
            _packMessage(destinationId, receivedMessage);
            receivedMessage.clear();

            // Send to Router
            _sendToRouter();
        }
    }
}

void NetworkInterface::_threadWriteToShell()
{
    if (!_frontEnd) {
        std::string message("Front-End Not Connected NI-Id:");
        NoCDebug::printDebug(message + std::to_string(_networkInterfaceId) + " Name: " + name(), NoCDebug::NI, true);
    } else {
        for (;;) {
            // Receive from router
            _receiveFromRouter();

            // Unpack message
            int sourceId;
            std::vector<uint32_t> sendMessage;
            _unpackMessage(&sourceId, &sendMessage);

            // Send Message to front-End
            _frontEnd->kernelSendPayload(sendMessage, &sourceId);
        }
    }
}

void NetworkInterface::_packMessage(unsigned destinationId, const std::vector<uint32_t> &payload)
{
    NoCDebug::printDebug("NI-ID:" + std::to_string(_networkInterfaceId) + " packeting message.", NoCDebug::NI);
    _sendPacket.clear();
    uint16_t packetSize = static_cast<uint16_t>(std::min(static_cast<size_t>(std::numeric_limits<uint16_t>::max()),
                                                         payload.size()));
    // Create Head Flit
    flit_t headerData = 0;

    headerData.range(15, 0) = packetSize;
    headerData.range(23, 16) = destinationId;
    headerData.range(31, 24) = _networkInterfaceId;
    Flit *flit = new Flit(headerData, 0);
    _sendPacket.push_back(flit);

    // Create Tail Flits
    for (uint16_t flitIndex = 0; flitIndex < packetSize; flitIndex++) {
        flit_t tailFlit = payload.at(flitIndex);
        flit = new Flit(tailFlit, 0);
        _sendPacket.push_back(flit);
    }

    // Note: It's reponsability of the NetworkInterface receiver of collecting and delete all the references of
    // the Flit objects.
}

const void NetworkInterface::_unpackMessage(int *sourceId, std::vector<uint32_t> *payload)
{
    NoCDebug::printDebug("NI-ID:" + std::to_string(_networkInterfaceId) + " unpacketing message.", NoCDebug::NI);
    // Unpack Head Flit
    Flit *flit = _receivePacket.at(0);
    *sourceId = flit->getData().range(31, 24);
    payload->clear();
    uint16_t packetSize = flit->getData().range(23, 16);
    for (uint16_t flitIndex = 1; flitIndex <= packetSize; flitIndex++) {
        flit = _receivePacket.at(flitIndex);
        payload->push_back(flit->getData().to_uint());
    }

    // Now delete all the flits.
    for (Flit *f : _receivePacket) {
        if (f) {
            delete f;
        }
    }
    _receivePacket.clear();
}

void NetworkInterface::_sendToRouter()
{
    for (Flit *flit : _sendPacket) {
        localChannel->sendFlit(flit);
    }

    // Clear Send Packet
    _sendPacket.clear();
}

void NetworkInterface::_receiveFromRouter()
{
    _receivePacket.clear();
    Flit *flit;
    // Receive Header Flit
    flit = localChannel->receiveFlit();
    _receivePacket.push_back(flit);

    // Receive Tail Flits
    uint16_t packetSize = flit->getData().range(15, 0);
    for (uint16_t flitIndex = 0; flitIndex < packetSize; flitIndex++) {
        flit = localChannel->receiveFlit();
        _receivePacket.push_back(flit);
    }
}

