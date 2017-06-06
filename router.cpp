#include "router.h"

void Router::_run()
{
    wait(localChannel->readValid());
    localChannel->writeValid();
    wait(northChannel->readValid());
    northChannel->writeValid();
    wait(southChannel->readValid());
    southChannel->writeValid();
    wait(eastChannel->readValid());
    eastChannel->writeValid();
    wait(westChannel->readValid());
    westChannel->writeAcknowledge();
}

Router::Router(sc_module_name name, unsigned routerId) :
    sc_module(name),
    _routerId(routerId)
{
    SC_THREAD(_run);
}

std::__cxx11::string Router::getName()
{
    return std::string(this->get_parent()->basename());
}

const int Router::getIdNumber()
{
    return _routerId;
}
