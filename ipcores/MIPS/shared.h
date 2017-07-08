#ifndef SHARED_H_
#define SHARED_H_

#define MEM_WORD_SIZE 1024 // Tamanho da memória em número de palavras para teste
//#define MEM_WORD_SIZE 134217728 // Tamanho da memória em número de palavras
#define CACHE_BLOCKS 256 // Número de blocos na cache
#define CACHE_WORDS 16 // Número de palavras em cada bloco da cache
#define DEBUG_MODE // Flag para indicar necessidade de imprimir PC, campos de instrução e o banco de registradores

// Formatos de instrução
enum FORMAT
{
	fm_R=6, fm_I=4, fm_J=2
};

// Opcodes das instruções
enum OPCODES
{
	i_FUN=0x00, i_LW=0x23, i_LB=0x20, i_LH=0x21,
	i_LBU=0x24, i_LHU=0x25, i_LUI=0x0F, i_SW=0x2B,
	i_SB=0x28, i_SH=0x29, i_BEQ=0x04, i_BNE=0x05,
	i_BLEZ=0x06, i_BGTZ=0x07, i_ADDI=0x08, i_ADDIU=0x09,
	i_SLTI=0x0A, i_SLTIU=0x0B, i_ANDI=0x0C, i_ORI=0x0D,
	i_XORI=0x0E, i_J=0x02, i_JAL=0x03, i_BLTZ=0x01
};

// Functs das instruções
enum FUNCT
{
	fn_ADD=0x20, fn_ADDU=0x21, fn_SUB=0x22, fn_MULT=0x18,
	fn_DIV=0x1A, fn_AND=0x24, fn_OR=0x25, fn_XOR=0x26,
	fn_NOR=0x27, fn_SLT=0x2A, fn_JR=0x08, fn_SLL=0x00,
	fn_SRL=0x02, fn_SRA=0x03, fn_SYSCALL=0x0c, fn_MFHI=0x10,
	fn_MFLO=0x12, fn_SLLV=0x04, fn_SRAV=0x07, fn_SRLV=0x06,
	fn_SLTU=0x2B
};

// Códigos de syscall
enum SYSCALL
{
	s_EXIT=0x0A
};

// Designações dos registradores do banco de registradores
enum REGISTERS
{
	r_ZERO=0, r_AT=1, r_V0=2, r_V1=3,r_A0=4, r_A1=5, r_A2=6, r_A3=7,
	r_T0=8, r_T1=9, r_T2=10, r_T3=11, r_T4=12, r_T5=13, r_T6=14, r_T7=15,
	r_S0=16, r_S1=17, r_S2=18, r_S3=19,r_S4=20, r_S5=21, r_S6=22, r_S7=23,
	r_T8=24, r_T9=25, r_K0=26, r_K1=27, r_GP=28, r_SP=29, r_FP=30, r_RA=31
};

// Modelo do contexto de execução
struct context
{
	// Registradores especiais
	uint32_t pc, ir;
	int32_t hi, lo;
	// Campos de instrução
	int32_t op, rs, rt, rd, shamt, funct;
	int16_t const16;
	int32_t const26;
};
typedef struct context Context;

#endif
