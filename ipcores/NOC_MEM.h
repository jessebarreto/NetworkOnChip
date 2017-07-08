#ifndef NOC_MEM_H
#define NOC_MEM_H

#include <systemc.h>
#include <vector>

using namespace std;

class nocmem : public sc_module{
	
	SC_HAS_PROCESS(nocmem);
	bool mem_read(int ad, int *data);
	bool mem_write(int ad, int data);
	bool mem_burst_read(int start_ad, int tam, vector<int>* r_data);
	bool mem_burst_write(int start_ad, int tam, vector<int>* w_data);
	bool mem_move(int start_ad, int tam, int end_ad);
	void notice();

public:
	nocmem(sc_module_name name);

	sc_fifo_in<int> memIn;
    sc_fifo_out<int> memOut;

};

#endif