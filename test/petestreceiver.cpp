#include "petestreceiver.h"

#include "nocdebug.h"

PETestReceiver::PETestReceiver(sc_module_name name) :
    sc_module(name),
    _message("")
{
    SC_THREAD(_threadRun);
}

void PETestReceiver::_threadRun()
{
    for (;;) {
        char c = fifoInput.read();
        NoCDebug::printDebug(std::string("Test Receiver get from fifo: ") + c, NoCDebug::PE);
        _message += c;
    }
}

const std::string PETestReceiver::getName()
{
    return std::string(this->name());
}

const std::string &PETestReceiver::getMessage()
{
    return _message;
}
