#include "routerchannel.h"

unsigned RouterChannel::_channelCounter = 0;

RouterChannel::RouterChannel(const sc_module_name &name) :
    sc_channel(name),
    _channelId(_channelCounter),
    _transmittedFlit(nullptr)
{
    // Counts the number of channels
    _channelCounter++;

    _valid = false;
    _acknowledge = false;
    _idle = true;
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
    while(!_idle) {
        wait(SC_ZERO_TIME);
    }
    _transmittedFlit = nullptr;
    NoCDebug::printDebug(std::string("Sending Flit: ") + std::to_string(flit->getUniqueId())  +
                         std::string(" to Channel: ") + this->name() + std::string("-Id: ") + std::to_string(_channelId),
                         NoCDebug::Channel);
    _transmittedFlit = flit;
    _valid = true;
    _idle = false;
    while(!_acknowledge) {
        wait(SC_ZERO_TIME);
    }
    _acknowledge = false;
    _idle = true;
}

Flit *RouterChannel::receiveFlit()
{
    while(!_valid) {
        wait(SC_ZERO_TIME);
    }
    NoCDebug::printDebug(std::string("Receiving Flit: ") + std::to_string(_transmittedFlit->getUniqueId())  +
                         std::string(" from Channel: ") + this->name()
                         + std::string("-Id: ") + std::to_string(_channelId), NoCDebug::Channel);
    _valid = false;
    _acknowledge = true;
    return _transmittedFlit;
}
