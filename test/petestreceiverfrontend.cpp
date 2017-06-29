#include "petestreceiverfrontend.h"

#include "nocdebug.h"

PETestReceiverFrontEnd::PETestReceiverFrontEnd(sc_module_name name) :
    sc_module(name)
{
    SC_THREAD(_threadRun);
}

void PETestReceiverFrontEnd::_threadRun()
{
//    char sendChar;
//    for (;;) {
//        wait(backEndSendEvent());
//        sendChar = _payload.back();
//        _payload.pop_back();
//        NoCDebug::printDebug(std::string("PE Test Shell Received Char: ") + static_cast<char>(sendChar), NoCDebug::NI);
//        fifoOutput.write(sendChar);
//        frontEndReceivedEvent();
//    }
}

