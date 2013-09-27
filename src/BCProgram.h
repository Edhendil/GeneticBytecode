/*
 * BCProgram.h
 *
 *  Created on: 05-02-2011
 *      Author: edhendil
 */

#ifndef BCPROGRAM_H_
#define BCPROGRAM_H_

typedef void (*bcexec_f)(void); // brak arg, brak return value

enum CompilerState {
	NORMAL, JUMPCC
};

enum Opcode {
	ADD_RI8 = 0,
	ADD_MI8 = 1,
	ADD_RR8 = 2,
	ADD_MR8 = 3,
	ADD_RM8 = 4,
	AND_RI8 = 5,
	AND_MI8 = 6,
	AND_RR8 = 7,
	AND_MR8 = 8,
	AND_RM8 = 9,
	BCCALL = 10, // brak
	CMP_RI8 = 11,
	CMP_MI8 = 12,
	CMP_RR8 = 13,
	CMP_MR8 = 14,
	CMP_RM8 = 15,
	DEC_R8 = 16,
	DEC_M8 = 17,
	INC_R8 = 18,
	INC_M8 = 19,
	JMP_I16 = 20,
	JMPCC_M16 = 21,
	MOV_RI8 = 22,
	MOV_MI8 = 23,
	MOV_RR8 = 24,
	MOV_MR8 = 25,
	MOV_RM8 = 26,
	NEG_R8 = 27,
	NEG_M8 = 28,
	NOP = 29, // not really implemented, just left a single number without any instruction
	OR_RI8 = 30,
	OR_MI8 = 31,
	OR_RR8 = 32,
	OR_MR8 = 33,
	OR_RM8 = 34,
	RET = 35,
	SETCC = 36, // brak
	SUB_RI8 = 37,
	SUB_MI8 = 38,
	SUB_RR8 = 39,
	SUB_MR8 = 40,
	SUB_RM8 = 41,
	TEST_RI8 = 42,
	TEST_MI8 = 43,
	TEST_RR8 = 44,
	TEST_MR8 = 45,
	TEST_RM8 = 46,
	XOR_RI8 = 47,
	XOR_MI8 = 48,
	XOR_RR8 = 49,
	XOR_MR8 = 50,
	XOR_RM8 = 51,
	INPUT_R8 = 52,
	INPUT_M8 = 53,
	OUTPUT_R8 = 54,
	OUTPUT_M8 = 55,
	NOT_R8 = 56,
	NOT_M8 = 57,
	JMPCC_R16 = 58, // brak
	JMPCC_I16 = 59,
	OUTPUT_I8 = 60,
	JMP_R16 = 61, // brak
	JMP_M16 = 62,
	MUL_M8 = 63,
	MUL_R8 = 64,
	IMUL_M8 = 65,
	IMUL_R8 = 66,
};

// second byte of SETcc and JMPcc (first operand)
enum JMPCCSubOpcode {
	A = 0, // above
	AE = 1,
	B = 2, // below
	BE = 3,
	C = 4,
	CXZ = 5, //CX zero
	E = 6,
	G = 7,
	GE = 8,
	L = 9,
	LE = 10,
	NA = 11,
	NAE = 12,
	NB = 13,
	NBE = 14,
	NC = 15, // carry
	NE = 16, // equal
	NG = 17,
	NGE = 18,
	NLE = 19,
	NO = 20, //oveflow
	NP = 21, // parity
	NS = 22, // sign
	NZ = 23, // zero
	O = 24,
	PE = 25, // parity even
	PO = 26, // parity odd
	S = 27, // sign
	Z = 28, // zero
	NL = 29,
	P = 30,
};

const unsigned int BYTECODE_LENGTH = 65536;
const unsigned int STACK_LENGTH = 500;
const unsigned int INPUT_LENGTH = 500;
const unsigned int OUTPUT_LENGTH = 500;

struct bcprogram_t {
	// instruction counter
	unsigned int icount;
	// instruction pointer;
	unsigned int ipoint;
	// stack with ret addresses, pointer to array
	unsigned short* callStack;
	unsigned int stackSize;
	// nie jest powiedziane do konca w jaki sposob wczytywanie danych
	unsigned char* input;
	unsigned int inputSize;
	// bytecode loaded from file
	unsigned char* bytecode;
	unsigned int bytecodeSize;
	// program's response
	unsigned char* output;
	unsigned int outputSize;
	// machine code
	bcexec_f run;
	// compiler state, useful for some multistage operations (ie. jumpcc)
	CompilerState compState;
	// to determine if is successful
	bool conditionCheck;
	// number of bytes already consumed by program from input
	unsigned int inputIndex;
	// number of bytes output by program
	unsigned int outputIndex;
	// number of bytes output by program
	unsigned int callStackIndex;
	// fitness value
	double fitnessValue;
};

void bcprogram_initialize(bcprogram_t* program);

void bcprogram_destroy(bcprogram_t* program);

#endif /* BCPROGRAM_H_ */
