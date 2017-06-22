#include "routerchannel.h"

unsigned RouterChannel::_channelCounter = 0;

RouterChannel::RouterChannel(const sc_module_name &name) :
    sc_channel(name),
    _channelId(_channelCounter),
    _transmittedFlit(NULL)
{
    // Counts the number of channels
    _channelCounter++;

    __readValid = 0; __readAck = 0; __writeValid = 0; __writeAck = 0;
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
    __writeValid = false;
    NoCDebug::printDebug(std::string("Sending Flit to Channel: ") + this->name()
                         + std::string("-Id: ") + std::to_string(_channelId), NoCDebug::Channel);
    _transmittedFlit = flit;
    __writeAck = true;
    _writeAcknowledged.notify();
}

void RouterChannel::validSender()
{
    __writeValid = true;
    _writeValid.notify();
}

void RouterChannel::validReceiver()
{
    __readValid = true;
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
    __readAck = true;
    _readAcknowledged.notify();
    _transmittedFlit = NULL;
}
