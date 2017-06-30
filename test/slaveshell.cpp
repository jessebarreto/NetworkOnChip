#include "slaveshell.h"

SlaveShell::SlaveShell(sc_module_name name) :
    sc_module(name)
{
    SC_THREAD(_threadRun);
}

void SlaveShell::_threadRun()
{
    int rec;
    char send;
    for (;;) {
        // Reading
        std::vector<uint32_t> payload;
        int payloadSrc;
        std::cout << "SShell <- Channel" << std::endl;
        receivePayload(payload, &payloadSrc);
        rec = payload.at(0);
        std::cout << "SShell -> Slave" << std::endl;
        shellOut.write(rec);

        // Writing
        std::cout << "SShell <- Slave" << std::endl;
        send = shellIn.read();
        payload.clear();
        payload.push_back(static_cast<uint32_t>(send));
        int payloadDst = 0;
        std::cout << "SShell -> Channel" << std::endl;
        sendPayload(payload, payloadDst);
        payload.clear();
    }
}
