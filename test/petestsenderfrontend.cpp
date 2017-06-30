#include "petestsenderfrontend.h"

#include "nocdebug.h"

PETestSenderFrontEnd::PETestSenderFrontEnd(sc_module_name name) :
    sc_module(name)
{
    SC_THREAD(_threadRun);
}

void PETestSenderFrontEnd::_threadRun()
{
    char receivedChar;
    for (;;) {
        fifoInput.read(receivedChar);
        NoCDebug::printDebug(std::string("PE Test Shell Send Char: ") + receivedChar, NoCDebug::NI);
        std::vector<uint32_t> payload;
        payload.push_back(static_cast<uint32_t>(receivedChar));
        sendPayload(payload, 1);
    }
}
