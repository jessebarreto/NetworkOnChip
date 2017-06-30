#include "specialkernel.h"

SpecialKernel::SpecialKernel(sc_module_name name) :
    sc_module(name),
    _frontEndMaster(nullptr),
    _frontEndSlave(nullptr)
{
    SC_THREAD(_threadConnectionMasterSlave);
}

void SpecialKernel::connectMaster(INetworkInterfaceFrontEnd *frontEndMaster)
{
    _frontEndMaster = frontEndMaster;
}

void SpecialKernel::connectSlave(INetworkInterfaceFrontEnd *frontEndSlave)
{
    _frontEndSlave = frontEndSlave;
}

void SpecialKernel::_threadConnectionMasterSlave()
{
    if (!_frontEndMaster && !_frontEndSlave) {
        std::string message("Front-Ends Not Connected NI-Id:");
    } else {
        for (;;) {
            // Receive Message from Front-End
            std::vector<uint32_t> receivedMessage;
            int masterId;
            _frontEndMaster->kernelReceivePayload(receivedMessage, &masterId);
            _frontEndSlave->kernelSendPayload(receivedMessage, &masterId);
            int slaveId;
            _frontEndSlave->kernelReceivePayload(receivedMessage, &slaveId);
            _frontEndMaster->kernelSendPayload(receivedMessage, &slaveId);
        }
    }
}
