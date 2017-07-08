#include "NOC_MEM_SHELL.h"

#include "nocdebug.h"

using namespace std;

NocMemShell::NocMemShell(sc_module_name name) :
    sc_module(name)
{
    SC_THREAD(_threadRun);
}

void NocMemShell::_threadRun()
{
    
    for (;;) {
        // Reading
        vector<uint32_t> payload;
        vector<int> dataIn;
        vector<int> dataOut;
        int payloadSrc;
        NoCDebug::printDebug("SShell <- Channel", NoCDebug::NI);
        receivePayload(payload, &payloadSrc);
        //opcode
        dataIn.push_back(payload.at(0));
        memshellOut.write(dataIn.at(0));
        
        if(dataIn.at(0) == 0){ //read
            //address
            dataIn.push_back(payload.at(1));
            memshellOut.write(dataIn.at(1));
            //numero de palavras
            dataIn.push_back(payload.at(2));
            memshellOut.write(dataIn.at(2));
        }
        else if(dataIn.at(0) == 1){ //write
            //address
            dataIn.push_back(payload.at(1));
            memshellOut.write(dataIn.at(1));
            //numero de palavras
            dataIn.push_back(payload.at(2));
            memshellOut.write(dataIn.at(2));
            //palavras
            for(int h = 3; h < (dataIn.at(2)+3); h++){
                dataIn.push_back(payload.at(h));
                memshellOut.write(dataIn.at(h));
            }
        }
        else if(dataIn.at(0) == 2){ //move
            //start address
            dataIn.push_back(payload.at(1));
            memshellOut.write(dataIn.at(1));
            //numero de palavras
            dataIn.push_back(payload.at(2));
            memshellOut.write(dataIn.at(2));
            //end address
            dataIn.push_back(payload.at(3));
            memshellOut.write(dataIn.at(3));
        }
        else{ //opcode desconhecido
            dataIn.clear();
            payload.clear();
            payload.push_back(static_cast<uint32_t>(false));
            sendPayload(payload, payloadSrc);
        }
        NoCDebug::printDebug("SShell -> Slave", NoCDebug::NI);
        //memshellOut.write(rec);

        // Writing
        NoCDebug::printDebug("SShell <- Slave", NoCDebug::NI);
        payload.clear();
        dataOut.push_back(memshellIn.read());
        //payload.push_back(dataOut.at(0));
        if(dataOut.at(0) == 1){ // TASK_OK
            payload.push_back(static_cast<uint32_t>(true));
            if(dataIn.at(0) == 0){ // read
                for(int h = 1; h < (dataIn.at(2)+1); h++){
                    dataOut.push_back(memshellIn.read());
                    payload.push_back(dataOut.at(h));
                }
            }
        }
        else{ // TASK_FAIL
            payload.push_back(static_cast<uint32_t>(false));
        }

        NoCDebug::printDebug("SShell -> Channel", NoCDebug::NI);
        sendPayload(payload, payloadSrc);
        payload.clear();
        dataIn.clear();
        dataOut.clear();
    }
}
