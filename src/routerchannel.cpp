#include "routerchannel.h"

#include "nocdebug.h"

unsigned RouterChannel::_channelCounter = 0;

RouterChannel::RouterChannel(const sc_module_name &name) :
    sc_prim_channel(name),
    _channelId(_channelCounter),
    _transmittedFlit(nullptr),
    _valid((std::string(SC_KERNEL_EVENT_PREFIX)+"_val_event" + std::to_string(_channelId)).c_str()),
    _acknowledge((std::string(SC_KERNEL_EVENT_PREFIX)+"_ack_event" + std::to_string(_channelId)).c_str()),
    _busy((std::string(SC_KERNEL_EVENT_PREFIX)+"_busy_event" + std::to_string(_channelId)).c_str()),
    _busyFlag(false)
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
    if (_busyFlag) {
        wait(_busy);
        _busyFlag = false;
    } else {
        _busyFlag = true;
    }

    _valid.notify(SC_ZERO_TIME);
    _transmittedFlit = nullptr;
    NoCDebug::printDebug(std::string("Sending Flit: ") + std::to_string(flit->getUniqueId())  +
                         std::string(" to Channel: ") + this->name() + std::string("-Id: ") + std::to_string(_channelId),
                         NoCDebug::Channel);
    _transmittedFlit = flit;
    wait(_acknowledge);
}

Flit *RouterChannel::receiveFlit()
{
    wait(_valid);
    NoCDebug::printDebug(std::string("Receiving Flit: ") + std::to_string(_transmittedFlit->getUniqueId())  +
                         std::string(" from Channel: ") + this->name()
                         + std::string("-Id: ") + std::to_string(_channelId), NoCDebug::Channel);
    _acknowledge.notify(SC_ZERO_TIME);
    _busy.notify(SC_ZERO_TIME);
    return _transmittedFlit;
}
