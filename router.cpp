#include "router.h"

void Router::_localChannelThread()
{
    wait(localChannel->readValid());
    // Run
    localChannel->writeAcknowledge();
}

void Router::_northChannelThread()
{
    wait(northChannel->readValid());
    // Run
    northChannel->writeAcknowledge();
}

void Router::_southChannelThread()
{
    wait(southChannel->readValid());
    // Run
    southChannel->writeAcknowledge();
}

void Router::_eastChannelThread()
{
    wait(eastChannel->readValid());
    // Run
    eastChannel->writeAcknowledge();
}

void Router::_westChannelThread()
{
    wait(westChannel->readValid());
    // Run
    westChannel->writeAcknowledge();
}

Router::Router(sc_module_name name, unsigned routerId) :
    sc_module(name),
    _routerId(routerId)
{
    SC_THREAD(_localChannelThread);
    SC_THREAD(_northChannelThread);
    SC_THREAD(_southChannelThread);
    SC_THREAD(_eastChannelThread);
    SC_THREAD(_westChannelThread);
}

std::__cxx11::string Router::getName()
{
    return std::string(this->get_parent()->basename());
}

const int Router::getIdNumber()
{
    return _routerId;
}
