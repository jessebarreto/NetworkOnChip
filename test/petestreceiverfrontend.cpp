#include "petestreceiverfrontend.h"

#include "nocdebug.h"

PETestReceiverFrontEnd::PETestReceiverFrontEnd(sc_module_name name) :
    sc_module(name)
{
    SC_THREAD(_threadRun);
}

void PETestReceiverFrontEnd::_threadRun()
{
    char sendChar;
    for (;;) {
        std::vector<uint32_t> payload;
        int payloadSrc;
        receivePayload(payload, &payloadSrc);
        sendChar = static_cast<char>(payload.at(0));
        payload.clear();
        NoCDebug::printDebug(std::string("PE Test Shell Received Char: ") + static_cast<char>(sendChar), NoCDebug::NI);
        fifoOutput.write(sendChar);
    }
}

