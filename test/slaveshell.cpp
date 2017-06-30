#include "slaveshell.h"

#include "nocdebug.h"

SlaveShell::SlaveShell(sc_module_name name) :
    sc_module(name)
{
    SC_THREAD(_threadRun);
}

void SlaveShell::_threadRun()
{
    int rec;
    char send;
    for (;;) {
        // Reading
        std::vector<uint32_t> payload;
        int payloadSrc;
        NoCDebug::printDebug("SShell <- Channel", NoCDebug::NI);
        receivePayload(payload, &payloadSrc);
        rec = payload.at(0);
        NoCDebug::printDebug("SShell -> Slave", NoCDebug::NI);
        shellOut.write(rec);

        // Writing
        NoCDebug::printDebug("SShell <- Slave", NoCDebug::NI);
        send = shellIn.read();
        payload.clear();
        payload.push_back(static_cast<uint32_t>(send));
        int payloadDst = 0;
        NoCDebug::printDebug("SShell -> Channel", NoCDebug::NI);
        sendPayload(payload, payloadDst);
        payload.clear();
    }
}
