#include "router.h"

#include <cstdlib>

#include "noccommon.h"
#include "nocdebug.h"

Router::Router(sc_module_name name, unsigned routerId) :
    sc_module(name),
    _routerId(routerId)
{
    _initChannelBuffers();

    SC_THREAD(_localChannelThread);
    SC_THREAD(_northChannelThread);
    SC_THREAD(_southChannelThread);
    SC_THREAD(_eastChannelThread);
    SC_THREAD(_westChannelThread);
    SC_THREAD(_arbiterThread);
}

Router::~Router()
{
    // Destroy the Flit buffers.
    for (std::pair<sc_fifo<Flit *> *, int> &pair : _inputBuffers) {
        if (!pair.first) {
            if (!pair.first->num_available()) {
                Flit *flit;
                for (int i = 0; i < pair.first->num_available(); i++) {
                    pair.first->nb_read(flit);
                    if (!flit) {
                        delete flit;
                        flit = nullptr;
                    }
                }
            }
            delete pair.first;
            pair.first = nullptr;
        }
    }
}

std::string Router::getName()
{
    return std::string(this->get_parent()->basename());
}

const int Router::getIdNumber()
{
    return _routerId;
}

void Router::_arbiterThread()
{
//    for (;;) {
//        for (auto currrentInputBuffer : _inputBuffers) {
//            // Check if its empty
//            if (currrentInputBuffer.first.size() == 0) {
//                continue;
//            }


//        }
//    }
}

void Router::_localChannelThread()
{
    sc_fifo<Flit *> *localBuffer = _inputBuffers[Link::Local].first;
    int &localBufferFlitsDst = _inputBuffers[Link::Local].second;
    for (;;) {
        // Checks whether the internal buffer is empty
        if (localBuffer->num_available() == 0) {
            // Receives the header flit.
            Flit *dataFlit = nullptr;
            dataFlit = localChannel->receiveFlit();

            // Checks the destination
            localBufferFlitsDst = dataFlit->getData().range(23, 16);
            int packageSize = dataFlit->getData().range(15, 0);

            // Put the header flit to the buffer
            localBuffer->write(dataFlit);

            // Put the other flits to the buffer
            for (int i = 0; i < packageSize; i++) {
                dataFlit = localChannel->receiveFlit();
                localBuffer->write(dataFlit);
            }

            // When it finishes to read the package

        }

//        // Receives Flit from the Local Channel
//        Flit *dataFlit = nullptr;
//        dataFlit = localChannel->receiveFlit();

//
//        // Checks if the internal buffer is full
//        if (localBuffer->num_free()) {
//            int packageSize = dataFlit->getData().range(15, 0);

//        }
//        _inputBuffers[Link::Local].first

//        _inputBuffers[0].push_back(dataFlit);


//        // Routing the flit
//        int dst;
//        _routingMethod(dataFlit, &dst);

//        // RUN
//        // VIRTUAL CHANNEL ALLOCATION USING HEADER FLIT
//        // ARBITER DECIDES WHICH FLIT GOES TO NEXT ROUTER
//        // ROUTING FLIT TO NEXT ROUTER

//        // Sends Flit to the Local Channel
//        localChannel->validSender();
//        localChannel->sendFlit(dataFlit);
//        wait(*localChannel->acknowledgeSender());
    }
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


void Router::_routingMethod(Flit *flit, int *dst)
{
    if (flit == nullptr) {
        NoCDebug::printDebug("Router Id-" + std::to_string(_routerId) + " flit is nullptr.", NoCDebug::Router, true);
        std::cerr << "file: " << __FILE__ << " line: " << __LINE__ << std::endl;
    }

    flit_t flitData = flit->getData();
    unsigned flitDst = flitData.range(23, 16);
//    routingInfo info = routingXY(_routerId, flitDst);
//    if (info.link == -1) {
//        NoCDebug::printDebug("Router Id-" + std::to_string(_routerId) + " flit is nullptr.", NoCDebug::Router, true);
//        std::cerr << "file: " << __FILE__ << " line: " << __LINE__ << std::endl;
    //    }
}

void Router::_initChannelBuffers()
{
    for (int i = 0; i < 5; i++) {
        _inputBuffers.push_back(std::make_pair(new sc_fifo<Flit *>, -1));
    }
}
