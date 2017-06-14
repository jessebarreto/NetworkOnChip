#ifndef NETWORKINTERFACEFRONTEND_H
#define NETWORKINTERFACEFRONTEND_H

#include <systemc.h>

#include "inetworkinterfacefrontend.h"

class NetworkInterfaceFrontEnd : public sc_module, public INetworkInterfaceFrontEnd
{
    SC_HAS_PROCESS(NetworkInterfaceFrontEnd);

    void _threadRead();

    void _threadWrite();

    bool _backEndReadyStatus;
    unsigned _receivedDestination;
    std::vector<unsigned> _receivedMessage;

    bool _frontEndReadyStatus;
    unsigned _sendDestination;
    std::vector<unsigned> _sendMessage;

public:
    sc_in<bool> processorReady;
    sc_fifo_in< sc_uint<32> > inFifo;
    sc_fifo_out<sc_uint<32> > outFifo;

    std::vector<unsigned> getMessage() override;

    void setMessage(const std::vector<unsigned> &message) override;

    unsigned getDestination() override;

    void setDestination(unsigned destinationId) override;

    bool getFrontEndReady() override;

    void setBackEndReady(bool backEndReadyStatus) override;
};

#endif // NETWORKINTERFACEFRONTEND_H

//void NetworkInterfaceFrontEnd::_threadRead()
//{
//    while (true) {
//        wait(SC_ZERO_TIME);
//        if (_backEndReadyStatus) {
////            out.write(); _receivedDestination _receivedMessage
//        }
//    }
//}

//void NetworkInterfaceFrontEnd::_threadWrite()
//{
//    while (true) {
//        wait(SC_ZERO_TIME);
//        if (processorReady.read()) {
////            in.write(); _sendDestination _sendMessage
//            _frontEndReadyStatus = true;
//        } else {
//            _frontEndReadyStatus = false;
//        }
//    }
//}

//std::vector<unsigned> NetworkInterfaceFrontEnd::getMessage()
//{
//    return _sendMessage;
//}


//void NetworkInterfaceFrontEnd::setMessage(const std::vector<unsigned> &message)
//{
//    _receivedMessage = message;
//}

//unsigned NetworkInterfaceFrontEnd::getDestination()
//{
//    return _sendDestination;
//}

//void NetworkInterfaceFrontEnd::setDestination(unsigned destinationId)
//{
//    _receivedDestination = destinationId;
//}

//bool NetworkInterfaceFrontEnd::getFrontEndReady()
//{
//    return _frontEndReadyStatus;
//}

//void NetworkInterfaceFrontEnd::setBackEndReady(bool backEndReadyStatus)
//{
//    _backEndReadyStatus = backEndReadyStatus;
//}
