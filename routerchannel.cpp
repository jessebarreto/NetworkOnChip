#include "routerchannel.h"

unsigned RouterChannel::_channelCounter = 0;

RouterChannel::RouterChannel(const std::string &name) :
    _channelName(name),
    _channelId(_channelCounter),
    _transmittedFlit(NULL)
{
    // Counts the number of channels
    _channelCounter++;
}

const std::string &RouterChannel::getName()
{
    return _channelName;
}

unsigned RouterChannel::getChannelId()
{
    return _channelId;
}

void RouterChannel::sendFlit(Flit *flit)
{
    wait(_writeValid);
    NoCDebug::printDebug(std::string("Sending Flit to Channel: ") + _channelName
                         + std::string(" Id: ") + std::to_string(_channelId), NoCDebug::Channel);
    _transmittedFlit = flit;
    _writeAcknowledged.notify();
}

void RouterChannel::validSender()
{
    _writeValid.notify();
}

void RouterChannel::validReceiver()
{
    _readValid.notify();
}

sc_event *RouterChannel::acknowledgeSender()
{
    return &_writeAcknowledged;
}

sc_event *RouterChannel::acknowledgeReceiver()
{
    return &_readAcknowledged;
}

void RouterChannel::receiveFlit(Flit *flit)
{
    wait(_readValid);
    NoCDebug::printDebug(std::string("Receiving Flit from Channel: ") + _channelName
                         + std::string(" Id: ") + std::to_string(_channelId), NoCDebug::Channel);
    if (_transmittedFlit == NULL) {
        NoCDebug::printDebug(std::string("Flit transmitted reference is NULL."), NoCDebug::Channel, true);
        exit(1);
    }
    flit = _transmittedFlit;
    _readAcknowledged.notify();
    _transmittedFlit = NULL;
}
