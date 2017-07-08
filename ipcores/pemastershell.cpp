#include "pemastershell.h"

#include "nocdebug.h"

ProcessorElementMasterShell::ProcessorElementMasterShell(sc_module_name name, unsigned position, unsigned slavePosition) :
    sc_module(name),
    _position(position),
    _slavePosition(slavePosition)
{
    SC_THREAD(_threadRun);
}

void ProcessorElementMasterShell::_threadRun()
{
    int send;
    char rec;
    for (;;) {
        // Writing
        NoCDebug::printDebug("MShell <- Master", NoCDebug::NI);
        shellIn.read(send);
        std::vector<uint32_t> payload;
        payload.push_back(send);
        int payloadDst = _slavePosition;
        NoCDebug::printDebug("MShell -> NIM", NoCDebug::NI);
        sendPayload(payload, payloadDst);
        payload.clear();

        // Reading
        int payloadSrc;
        NoCDebug::printDebug("MShell <- NIM", NoCDebug::NI);
        receivePayload(payload, &payloadSrc);
        rec = payload.at(0);
        NoCDebug::printDebug("MShell -> Master", NoCDebug::NI);
        shellOut.write(rec);

        // Só lê do Master
//        int readVal;
//        shellIn.read(readVal);
//        std::cout << readVal << std::endl;
//        char writeVal = 'v';
//        shellOut.write(writeVal);
    }
}
