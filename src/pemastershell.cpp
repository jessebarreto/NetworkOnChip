#include "pemastershell.h"

#include "nocdebug.h"

ProcessorElementMasterShell::ProcessorElementMasterShell(sc_module_name name, unsigned position, unsigned slavePosition) :
    sc_module(name),
    _position(position),
    _slavePosition(slavePosition)
{
    NoCDebug::printDebug(std::string("> MasterShell: M" + std::to_string(position) + "S" + std::to_string(slavePosition)), NoCDebug::Assembly);

    SC_THREAD(_threadRun);
}

void ProcessorElementMasterShell::_threadRun()
{
    int send;
    char rec;
    for (;;) {
        // Writing
        NoCDebug::printDebug("M" + std::to_string(_position) + "S" + std::to_string(_slavePosition) + ": MShell <- Master", NoCDebug::NI);
        shellIn.read(send);
        std::vector<uint32_t> payload;
        payload.push_back(send);
        int payloadDst = _slavePosition;
        NoCDebug::printDebug("M" + std::to_string(_position) + "S" + std::to_string(_slavePosition) + ": MShell -> NIM", NoCDebug::NI);
        sendPayload(payload, payloadDst);
        payload.clear();

        // Reading
        int payloadSrc;
        NoCDebug::printDebug("M" + std::to_string(_position) + "S" + std::to_string(_slavePosition) + ": MShell <- NIM", NoCDebug::NI);
        receivePayload(payload, &payloadSrc);
        rec = payload.at(0);
        NoCDebug::printDebug("M" + std::to_string(_position) + "S" + std::to_string(_slavePosition) + ": MShell -> Master", NoCDebug::NI);
        shellOut.write(rec);

        // Só lê do Master
//        int readVal;
//        shellIn.read(readVal);
//        std::cout << readVal << std::endl;
//        char writeVal = 'v';
//        shellOut.write(writeVal);
    }
}
