#include "globals.h"
#include "shell_mips.h"

using namespace std;

void shellmi_mips::check_destiny(uint32_t word, uint32_t destiny){
	if ((get_orig(word)) != destiny) {
            cout << "Erro: origem da palavra recebida nao corresponde com o destino em - " << get_orig(word) << " e " << destiny;
		exit(-1);
	}
}

int32_t shellmi_mips::lb(const uint32_t address, uint16_t kte) {
	
	// address + offset
    uint32_t tmp = address + kte;
    
	// send header flit through fifo (size = 1)
    uint32_t	size = 0x1;
    uint32_t	flit_tmp = build_Hflit(P, M0, LB, size);
    out.write(flit_tmp);
	
	// send address data flit through fifo
    flit_tmp = tmp;
    out.write(flit_tmp);

	// receive header flit from destiny
    int32_t word_tmp = in.read();
    check_destiny(word_tmp, M0);	// check if came from actual destiny

	// receive data flit from destiny
    word_tmp = in.read();

    return (int8_t)(word_tmp); // ?????? porque (int8_t) ?????
}

int32_t shellmi_mips::lbu(const uint32_t address, uint16_t kte) {
	
    // address + offset
    uint32_t tmp = address + kte;
    
	// send header flit throug fifo (size = 1)
	uint32_t	size = 0x1;
	uint32_t	flit_tmp = build_Hflit(P, M0, LBU, size);
    out.write(flit_tmp);
	
	// send data flit throug fifo
	flit_tmp = tmp;
    out.write(flit_tmp);

	// receive header flit from destiny
    int32_t word_tmp = in.read();
	check_destiny(word_tmp, M0);	// check if came from actual destiny

	// receive data flit from destiny
    word_tmp = in.read();
    
	return (word_tmp);
}


int32_t shellmi_mips::lhu(const uint32_t address, uint16_t kte) {
    // address + offset
    uint32_t tmp = address + kte;
    
	// send header flit throug fifo (size = 1)
	uint32_t	size = 0x1;
	uint32_t	flit_tmp = build_Hflit(P, M0, LHU, size);
    out.write(flit_tmp);
	
	// send data flit throug fifo
	flit_tmp = tmp;
    out.write(flit_tmp);

	// receive header flit from destiny
    int32_t word_tmp = in.read();
	check_destiny(word_tmp, M0);	// check if came from actual destiny

	// receive data flit from destiny
    word_tmp = in.read();
	
	return (word_tmp);
}

int32_t shellmi_mips::lh(const uint32_t address, uint16_t kte) {
    // address + offset
    uint32_t tmp = address + kte;
    
	// send header flit throug fifo (size = 1)
	uint32_t	size = 0x1;
	uint32_t	flit_tmp = build_Hflit(P, M0, LH, size);
    out.write(flit_tmp);
	
	// send data flit throug fifo
	flit_tmp = tmp;
    out.write(flit_tmp);

	// receive header flit from destiny
    int32_t word_tmp = in.read();
	check_destiny(word_tmp, M0);	// check if came from actual destiny

	// receive data flit from destiny
    word_tmp = in.read();
	
    return (int16_t)(word_tmp);
}

int32_t shellmi_mips::lw(const uint32_t address, uint16_t kte) {
        // address + offset
    uint32_t tmp = address + kte;
    
	// send header flit throug fifo (size = 1)
    uint32_t	size = 0x1;
    uint32_t	flit_tmp = build_Hflit(P, M0, LW, size);
    out.write(flit_tmp);

	// send data flit throug fifo
    flit_tmp = tmp;
    out.write(flit_tmp);

	// receive header flit from destiny
    int32_t word_tmp = in.read();
    check_destiny(word_tmp, M0);	// check if came from actual destiny

	// receive data flit from destiny
    word_tmp = in.read();
    
    return(word_tmp);
}

// int32_t shellmi_mips::instruction_lw(const uint32_t address, uint16_t kte) {
//         // address + offset
//     uint32_t tmp = address + kte;
    
// 	// send header flit throug fifo (size = 1)
//     uint32_t	size = 0x1;
//     uint32_t	flit_tmp = build_Hflit(P, M0, LW, size);
//     out.write(flit_tmp);

// 	// send data flit throug fifo
//     flit_tmp = tmp;
//     out.write(flit_tmp);

// 	// receive header flit from destiny
//     int32_t word_tmp = in.read();
//     check_destiny(word_tmp, M0);	// check if came from actual destiny

// 	// receive data flit from destiny
//     word_tmp = in.read();
    
//     return(word_tmp);

// }

void shellmi_mips::sb(const uint32_t address, uint16_t kte, int8_t dado) {
    // address + offset
    uint32_t tmp = address + kte;
    
	// send header flit throug fifo (size = 1)
	uint32_t	size = 0x2;
	uint32_t	flit_tmp = build_Hflit(P, M0, SB, size);
    out.write(flit_tmp);
	
	// send data flit throug fifo
	flit_tmp = tmp;
    out.write(flit_tmp);

	// send data flit throug fifo
	flit_tmp = dado;
    out.write(flit_tmp);

}

void shellmi_mips::sh(const uint32_t address, uint16_t kte, int16_t dado) {
    // address + offset
    uint32_t tmp = address + kte;
    
	// send header flit throug fifo (size = 1)
	uint32_t	size = 0x2;
	uint32_t	flit_tmp = build_Hflit(P, M0, SH, size);
    out.write(flit_tmp);
	
	// send data flit throug fifo
	flit_tmp = tmp;
    out.write(flit_tmp);

	// send data flit throug fifo
	flit_tmp = dado;
    out.write(flit_tmp);
}

void shellmi_mips::sw(const uint32_t address, uint16_t kte, int32_t dado) {
    // address + offset
    uint32_t tmp = address + kte;
    
	// send header flit throug fifo (size = 1)
	uint32_t	size = 0x2;
	uint32_t	flit_tmp = build_Hflit(P, M0, SW, size);
    out.write(flit_tmp);
	
	// send data flit throug fifo
	flit_tmp = tmp;
    out.write(flit_tmp);

	// send data flit throug fifo
	flit_tmp = dado;
    out.write(flit_tmp);

}
