
#include <systemc.h>

#include "routerchannel.h"
#include "networkinterface.h"

#include "petestsender.h"
#include "petestsenderfrontend.h"

#include "petestreceiver.h"
#include "petestreceiverfrontend.h"

int main()
{
    NetworkInterface senderKernel("SenderNI", 0);
    PETestSender senderPE("SenderPE");
    PETestSenderFrontEnd senderShell("SenderShell");
    // Connect PE and Shell
    sc_fifo<char> senderFIFO(1);
    senderPE.fifoOutput(senderFIFO);
    senderShell.fifoInput(senderFIFO);
    // Connect Kernel and Shell
    senderKernel.connectFrontEnd(&senderShell);


    NetworkInterface receiverKernel("ReceiverNI", 0);
    PETestReceiver receiverPE("ReceiverPE");
    PETestReceiverFrontEnd receiverShell("ReceiverShell");
    // Connect PE and Shell
    sc_fifo<char> receiverFIFO(1);
    receiverShell.fifoOutput(receiverFIFO);
    receiverPE.fifoInput(receiverFIFO);
    // Connect Kernel and Shell
    senderKernel.connectFrontEnd(&receiverShell);

    // Connect Kernels
    RouterChannel channel("Channel");
    senderKernel.localChannel(channel);
    receiverKernel.localChannel(channel);

    sc_start();

    return 0;
}


//#if NOC_CONNECTION_TEST
////    PETestSender *testSender = new PETestSender("TestSender");
////    PROCESSORS_MAP[testSender->getName()] = 0;
////    PETestReceiver *testReceiver = new PETestReceiver("TestReceiver");
////    PROCESSORS_MAP[testReceiver->getName()] = 1;

////    PETestSenderFrontEnd *testSenderShell = new PETestSenderFrontEnd("TestSenderFrontEnd");
////    NetworkInterface *ni = networkInterfaces.at(0);
////    ni->connectFrontEnd(testSenderShell);

////    PETestReceiverFrontEnd *testReceiverShell = new PETestReceiverFrontEnd("TestReceiverFrontEnd");
////    ni = networkInterfaces.at(1);
////    ni->connectFrontEnd(testReceiverShell);

////    sc_fifo<char> *senderFifo = new sc_fifo<char>(1);
////    sc_fifo<char> *receiverFifo = new sc_fifo<char>(1);

////    testSender->fifoOutput(*senderFifo);
////    testSenderShell->fifoInput(*senderFifo);
////    testReceiver->fifoInput(*receiverFifo);
////    testReceiverShell->fifoOutput(*receiverFifo);

//    ChannelTester channelTester1("ChannelTester1", 0, true);
//    ChannelTester channelTester2("ChannelTester2", 1, false);

//    RouterChannel channel("RouterChannelTest1");
//    channelTester1.channel(channel);
//    channelTester2.channel(channel);
//#endif //NOC_CONNECTION_TEST
