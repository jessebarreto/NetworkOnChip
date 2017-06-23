#include "channeltester.h"

ChannelTester::ChannelTester(sc_module_name name, int id, bool begin) :
    _begin(begin)
{
    _0ID = id;
    _packetCounter = 0;

    SC_THREAD(_runThread);
}

void ChannelTester::_runThread()
{
    Flit *flit;
    for (;;) {
        if (_begin) {
            _begin = false;
            flit = new Flit(flit_t(_packetCounter), _packetCounter++);
            std::cout << "tester: " << _0ID << " sending to channel." << std::endl;
            channel->sendFlit(flit);
            std::cout << "tester: " << _0ID << " sending got acknowledged." << std::endl;
        } else {
            std::cout << "tester: " << _0ID << " receiving from channel." << std::endl;
            flit = channel->receiveFlit();
            std::cout << "tester: " << _0ID << " received from channel." << std::endl;
            delete flit;
            _begin = true;
        }
    }
}



