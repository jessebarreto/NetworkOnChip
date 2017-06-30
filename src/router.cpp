#include "router.h"

void Router::_localChannelThread()
{
    Flit *dataFlit;
//    for (;;) {
//        // Receives Flit from the Local Channel
//        localChannel->
//        localChannel->receiveFlit(dataFlit);
//        wait(*localChannel->acknowledgeReceiver());

//        // RUN
//        // VIRTUAL CHANNEL ALLOCATION USING HEADER FLIT
//        // ARBITER DECIDES WHICH FLIT GOES TO NEXT ROUTER
//        // ROUTING FLIT TO NEXT ROUTER

//        // Sends Flit to the Local Channel
//        localChannel->validSender();
//        localChannel->sendFlit(dataFlit);
//        wait(*localChannel->acknowledgeSender());
//    }
}

void Router::_northChannelThread()
{
//    Flit *dataFlit;
//    for (;;) {
//        // Receives Flit from the North Channel
//        northChannel->validReceiver();
//        northChannel->receiveFlit(dataFlit);
//        wait(*northChannel->acknowledgeReceiver());

//        // RUN
//        // VIRTUAL CHANNEL ALLOCATION USING HEADER FLIT
//        // ARBITER DECIDES WHICH FLIT GOES TO NEXT ROUTER
//        // ROUTING FLIT TO NEXT ROUTER

//        // Sends Flit to the Local Channel
//        northChannel->validSender();
//        northChannel->sendFlit(dataFlit);
//        wait(*northChannel->acknowledgeSender());
//    }
}

void Router::_southChannelThread()
{
    Flit *dataFlit;
//    for (;;) {
//        // Receives Flit from the South Channel
//        southChannel->validReceiver();
//        southChannel->receiveFlit(dataFlit);
//        wait(*southChannel->acknowledgeReceiver());

//        // RUN
//        // VIRTUAL CHANNEL ALLOCATION USING HEADER FLIT
//        // ARBITER DECIDES WHICH FLIT GOES TO NEXT ROUTER
//        // ROUTING FLIT TO NEXT ROUTER

//        // Sends Flit to the Local Channel
//        southChannel->validSender();
//        southChannel->sendFlit(dataFlit);
//        wait(*southChannel->acknowledgeSender());
//    }
}

void Router::_eastChannelThread()
{
//    Flit *dataFlit;
//    for (;;) {
//        // Receives Flit from the East Channel
//        eastChannel->validReceiver();
//        eastChannel->receiveFlit(dataFlit);
//        wait(*eastChannel->acknowledgeReceiver());

//        // RUN
//        // VIRTUAL CHANNEL ALLOCATION USING HEADER FLIT
//        // ARBITER DECIDES WHICH FLIT GOES TO NEXT ROUTER
//        // ROUTING FLIT TO NEXT ROUTER

//        // Sends Flit to the Local Channel
//        eastChannel->validSender();
//        eastChannel->sendFlit(dataFlit);
//        wait(*eastChannel->acknowledgeSender());
//    }
}

void Router::_westChannelThread()
{
    Flit *dataFlit;
//    for (;;) {
//        // Receives Flit from the West Channel
//        westChannel->validReceiver();
//        westChannel->receiveFlit(dataFlit);
//        wait(*westChannel->acknowledgeReceiver());

//        // RUN
//        // VIRTUAL CHANNEL ALLOCATION USING HEADER FLIT
//        // ARBITER DECIDES WHICH FLIT GOES TO NEXT ROUTER
//        // ROUTING FLIT TO NEXT ROUTER

//        // Sends Flit to the Local Channel
//        westChannel->validSender();
//        westChannel->sendFlit(dataFlit);
//        wait(*westChannel->acknowledgeSender());
//    }
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

std::string Router::getName()
{
    return std::string(this->get_parent()->basename());
}

const int Router::getIdNumber()
{
    return _routerId;
}
