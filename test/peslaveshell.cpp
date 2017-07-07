#include "peslaveshell.h"

#include "nocdebug.h"

ProcessorElementSlaveShell::ProcessorElementSlaveShell(sc_module_name name, unsigned position, unsigned masterPosition) :
    sc_module(name),
    _position(position),
    _masterPosition(masterPosition)
{

    NoCDebug::printDebug(std::string("> SlaveShell: S" + std::to_string(position) + "M" + std::to_string(masterPosition)), NoCDebug::Assembly);
    SC_THREAD(_threadRun);
}

void ProcessorElementSlaveShell::_threadRun()
{
    int rec;
    char send;
    for (;;) {
        // Reading
        std::vector<uint32_t> payload;
        int payloadSrc;
        NoCDebug::printDebug("S" + std::to_string(_position) + "M" + std::to_string(_masterPosition) + ": SShell <- SKernel", NoCDebug::NI);
        receivePayload(payload, &payloadSrc);
        rec = payload.at(0);
        NoCDebug::printDebug("S" + std::to_string(_position) + "M" + std::to_string(_masterPosition) + ": SShell -> Slave", NoCDebug::NI);
        shellOut.write(rec);

        // Writing
        NoCDebug::printDebug("S" + std::to_string(_position) + "M" + std::to_string(_masterPosition) + ": SShell <- Slave", NoCDebug::NI);
        send = shellIn.read();
        payload.clear();
        payload.push_back(static_cast<uint32_t>(send));
        int payloadDst = _masterPosition;
        NoCDebug::printDebug("S" + std::to_string(_position) + "M" + std::to_string(_masterPosition) + ": SShell -> SKernel", NoCDebug::NI);
        sendPayload(payload, payloadDst);
        payload.clear();
    }
}
