#include "pemastershell.h"

#include "nocdebug.h"

ProcessorElementMasterShell::ProcessorElementMasterShell(sc_module_name name, unsigned slavePosition) :
    sc_module(name),
    _slavePosition(slavePosition)
{
    _name = this->basename();
    NoCDebug::printDebug(std::string("> MasterShell: " + _name), NoCDebug::Assembly);

    SC_THREAD(_threadRun);
}

void ProcessorElementMasterShell::_threadRun()
{
    int send;
    char rec;
    for (;;) {
        // Writing
        NoCDebug::printDebug(std::string(_name + ": MShell <- Master"), NoCDebug::NI);
        shellIn.read(send);
        std::vector<uint32_t> payload;
        payload.push_back(send);
        int payloadDst = _slavePosition;
        NoCDebug::printDebug(std::string(_name + ": MShell -> MKernel"), NoCDebug::NI);
        sendPayload(payload, payloadDst);
        payload.clear();

        // Reading
        int payloadSrc;
        NoCDebug::printDebug(std::string(_name + ": MShell <- MKernel"), NoCDebug::NI);
        receivePayload(payload, &payloadSrc);
        rec = payload.at(0);
        NoCDebug::printDebug(std::string(_name + ": MShell -> Master"), NoCDebug::NI);
        shellOut.write(rec);
    }
}
