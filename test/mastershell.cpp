#include "mastershell.h"

MasterShell::MasterShell(sc_module_name name) :
    sc_module(name)
{
    SC_THREAD(_threadRun);
}

void MasterShell::_threadRun()
{
    int send;
    char rec;
    for (;;) {
        // Writing
        std::cout << "MShell <- Master - " << shellIn.num_available() << std::endl;
        shellIn.read(send);
        std::vector<uint32_t> payload;
        payload.push_back(send);
        int payloadDst = 1;
        std::cout << "MShell -> Channel" << std::endl;
        sendPayload(payload, payloadDst);
        payload.clear();

        // Reading
        int payloadSrc;
        std::cout << "MShell <- Channel" << std::endl;
        receivePayload(payload, &payloadSrc);
        rec = payload.at(0);
        std::cout << "MShell -> Master" << std::endl;
        shellOut.write(rec);

        // Só lê do Master
//        int readVal;
//        shellIn.read(readVal);
//        std::cout << readVal << std::endl;
//        char writeVal = 'v';
//        shellOut.write(writeVal);
    }
}
