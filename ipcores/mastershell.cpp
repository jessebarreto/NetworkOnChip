#include "mastershell.h"

#include "nocdebug.h"

using namespace std;

MasterShell::MasterShell(sc_module_name name) :
    sc_module(name)
{
    SC_THREAD(_threadRun);
}

void MasterShell::_threadRun()
{
    vector<int> send;
    int rec;
    for (;;) {
        // Writing
        NoCDebug::printDebug("MShell <- Master", NoCDebug::NI);
        send.push_back(1);
        send.push_back(16);
        send.push_back(5);
        send.push_back(10);
        send.push_back(20);
        send.push_back(30);
        send.push_back(40);
        send.push_back(50);
        vector<uint32_t> payload;
        for(int i=0; i<send.size(); i++)
            payload.push_back(send.at(i));
        int payloadDst = 1;
        NoCDebug::printDebug("MShell -> Channel", NoCDebug::NI);
        sendPayload(payload, payloadDst);
        payload.clear();

        // Reading
        int payloadSrc;
        NoCDebug::printDebug("MShell <- Channel", NoCDebug::NI);
        receivePayload(payload, &payloadSrc);
        rec = payload.at(0);
        NoCDebug::printDebug("MShell -> Master", NoCDebug::NI);
        cout<<"master recebeu ---> "<<rec<<endl;
        shellOut.write(rec);

        // Só lê do Master
//        int readVal;
//        shellIn.read(readVal);
//        std::cout << readVal << std::endl;
//        char writeVal = 'v';
//        shellOut.write(writeVal);
    }
}
