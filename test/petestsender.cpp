#include "petestsender.h"

#include "nocdebug.h"

PETestSender::PETestSender(sc_module_name name) :
    sc_module(name)
{
    _message = "A really long message which gonna be transmitted through the NoC!";

    SC_THREAD(_threadRun);
}

const std::string &PETestSender::getMessage()
{
    return _message;
}

const std::string PETestSender::getName()
{
    return std::string(name());
}

void PETestSender::_threadRun()
{
    for (char c : _message) {
        NoCDebug::printDebug(std::string("Test Sender filling fifo: ") + c, NoCDebug::PE);
         fifoOutput.write(c);
    }
}
