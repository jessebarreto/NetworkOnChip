#include "pemastershell.h"

#include "nocdebug.h"

MasterShell::MasterShell(sc_module_name name) :
    sc_module(name)
{
    SC_THREAD(_threadRun);
}

void MasterShell::_threadRun()
{
    int send;
    char rec;
    for (;;) {
        // Writing
        NoCDebug::printDebug("MShell <- Master", NoCDebug::NI);
        shellIn.read(send);
        std::vector<uint32_t> payload;
        payload.push_back(send);
        int payloadDst = 1;
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
