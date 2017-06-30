
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
    receiverKernel.connectFrontEnd(&receiverShell);

    // Connect Kernels
    RouterChannel channel("Channel");
    senderKernel.localChannel(channel);
    receiverKernel.localChannel(channel);

    sc_start();

    return 0;
}
