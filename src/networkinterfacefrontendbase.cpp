#include "networkinterfacefrontendbase.h"

NetworkInterfaceFrontEndBase::NetworkInterfaceFrontEndBase() :
    _payloadDst(0),
    _payloadSrc(0),
    _ack((std::string(SC_KERNEL_EVENT_PREFIX)+"NIShellBase_ack").c_str()),
    _valid((std::string(SC_KERNEL_EVENT_PREFIX)+"NIShellBase_valid").c_str()),
    _ackFlag(false),
    _validFlag(false),
    _writing((std::string(SC_KERNEL_EVENT_PREFIX)+"NIShellBase_writing").c_str()),
    _reading((std::string(SC_KERNEL_EVENT_PREFIX)+"NIShellBase_reading").c_str()),
    _writingFlag(false),
    _readingFlag(false)
{
}

void NetworkInterfaceFrontEndBase::sendPayload(const std::vector<uint32_t> &payload, int dst)
{
    _payloadDst = dst;
    _payload = payload;
    _writing.notify(SC_ZERO_TIME);
    _writingFlag = true;
    for (;!_ackFlag;) {
        wait(_ack);
    }
    _ackFlag = false;
}

void NetworkInterfaceFrontEndBase::receivePayload(std::vector<uint32_t> &payload, int *src)
{
    _reading.notify(SC_ZERO_TIME);
    _readingFlag = true;

    for (;!_validFlag;) {
        wait(_valid);
    }
    _validFlag = false;

    payload = _payload;
    *src = _payloadSrc;
}

void NetworkInterfaceFrontEndBase::kernelReceivePayload(std::vector<uint32_t> &payload, int *dst)
{
    for (;!_writingFlag;) {
        wait(_writing);
    }
    _writingFlag = false;

    payload = _payload;
    *dst = _payloadDst;
    _ack.notify(SC_ZERO_TIME);
    _ackFlag = true;
}

void NetworkInterfaceFrontEndBase::kernelSendPayload(const std::vector<uint32_t> &payload, int *src)
{
    for (;!_readingFlag;) {
        wait(_reading);
    }
    _readingFlag = false;

    _valid.notify();
    _validFlag = true;

    _payload = payload;
    _payloadSrc = *src;
}
