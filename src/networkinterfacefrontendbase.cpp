#include "networkinterfacefrontendbase.h"


void NetworkInterfaceFrontEndBase::sendPayload(const std::vector<uint32_t> &payload, int dst)
{
    _payloadDst = dst;
    _payload = payload;
    _writing.notify(SC_ZERO_TIME);
    wait(_ack);
}

void NetworkInterfaceFrontEndBase::receivePayload(std::vector<uint32_t> &payload, int *src)
{
    _reading.notify(SC_ZERO_TIME);
    wait(_valid);
    payload = _payload;
    *src = _payloadSrc;
}

void NetworkInterfaceFrontEndBase::kernelReceivePayload(std::vector<uint32_t> &payload, int *dst)
{
    wait(_writing);
    payload = _payload;
    *dst = _payloadDst;
    _ack.notify(SC_ZERO_TIME);
}

void NetworkInterfaceFrontEndBase::kernelSendPayload(const std::vector<uint32_t> &payload, int *src)
{
    wait(_reading);
    _valid.notify();
    _payload = payload;
    _payloadSrc = *src;
}
