#include "routerchannel.h"

RouterChannel::RouterChannel(sc_module_name name) :
    sc_module(name)
{

}

void RouterChannel::writeValid()
{
    _validEvent.notify();
}

sc_event &RouterChannel::readValid()
{
    return _validEvent;
}

void RouterChannel::writeAcknowledge()
{
    _ackEvent.notify();
}

sc_event &RouterChannel::readAcknowledge()
{
    return _ackEvent;
}

void RouterChannel::writeFlit(flit_t &flit)
{
    _transmitedFlit = flit;
}

flit_t &RouterChannel::readFlit()
{
    return _transmitedFlit;
}
