#include "peslaveshell.h"

#include "nocdebug.h"

ProcessorElementSlaveShell::ProcessorElementSlaveShell(sc_module_name name, unsigned masterPosition) :
    sc_module(name),
    _masterPosition(masterPosition)
{
    _name = this->basename();
    NoCDebug::printDebug(std::string("> SlaveShell: " + _name), NoCDebug::Assembly);
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
        NoCDebug::printDebug(std::string(_name + ": SShell <- SKernel"), NoCDebug::NI);
        receivePayload(payload, &payloadSrc);
        rec = payload.at(0);
        NoCDebug::printDebug(std::string(_name + ": SShell -> Slave"), NoCDebug::NI);
        shellOut.write(rec);

        // Writing
        NoCDebug::printDebug(std::string(_name + ": SShell <- Slave"), NoCDebug::NI);
        send = shellIn.read();
        payload.clear();
        payload.push_back(static_cast<uint32_t>(send));
        int payloadDst = _masterPosition;
        NoCDebug::printDebug(std::string(_name + ": SShell -> SKernel"), NoCDebug::NI);
        sendPayload(payload, payloadDst);
        payload.clear();
    }
}
