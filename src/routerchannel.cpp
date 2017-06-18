#include "routerchannel.h"

unsigned RouterChannel::_channelCounter = 0;

RouterChannel::RouterChannel(const sc_module_name &name) :
    sc_channel(name),
    _channelId(_channelCounter),
    _transmittedFlit(NULL)
{
    // Counts the number of channels
    _channelCounter++;
}

std::string RouterChannel::getName()
{
    return this->name();
}

unsigned RouterChannel::getChannelId()
{
    return _channelId;
}

void RouterChannel::sendFlit(Flit *flit)
{
    wait(_writeValid);
    NoCDebug::printDebug(std::string("Sending Flit to Channel: ") + this->name()
                         + std::string("-Id: ") + std::to_string(_channelId), NoCDebug::Channel);
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
    wait(_writeAcknowledged);
    NoCDebug::printDebug(std::string("Receiving Flit from Channel: ") + this->name()
                         + std::string("-Id: ") + std::to_string(_channelId), NoCDebug::Channel);
    if (_transmittedFlit == NULL) {
        NoCDebug::printDebug(std::string("Flit transmitted reference is NULL."), NoCDebug::Channel, true);
        exit(1);
    }
    flit = _transmittedFlit;
    _readAcknowledged.notify();
    _transmittedFlit = NULL;
}
