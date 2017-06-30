#include "flit.h"

uint64_t Flit::_globalFlitCounter = 0;

Flit::Flit(flit_t data, uint64_t packetId) :
    _globalId(_globalFlitCounter),
    _data(data),
    _packetId(packetId)
{
    // Count the flits
    _globalFlitCounter++;
}

flit_t Flit::getData()
{
    return _data;
}

void Flit::setData(flit_t data)
{
    _data = data;
}

uint64_t Flit::getUniqueId()
{
    return _globalId;
}

uint64_t Flit::getPacketId()
{
    return _packetId;
}
