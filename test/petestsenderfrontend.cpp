#include "petestsenderfrontend.h"

PETestSenderFrontEnd::PETestSenderFrontEnd(sc_module_name name) :
    sc_module(name)
{
    _msgDestination = 1;

    SC_THREAD(_threadRun);
}

void PETestSenderFrontEnd::_threadRun()
{
    char receivedChar;
    for (;;) {
        fifoInput.read(receivedChar);
        NoCDebug::printDebug(std::string("PE Test Shell Send Char: ") + receivedChar, NoCDebug::NI);
        _message.push_back(static_cast<uint32_t>(receivedChar));
        frontEndSendEvent();
        wait(backEndReceivedEvent());
    }
}
