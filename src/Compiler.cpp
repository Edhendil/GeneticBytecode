/*
 * compiler.cpp
 *
 *  Created on: 05-02-2011
 *      Author: edhendil
 */

#include <string.h>
#include "Compiler.h"
#include "BCProgram.h"

const unsigned int INSTR_LIMIT = 1000;

void compileNext(bcprogram_t* program) {
	unsigned char *start = (unsigned char *) (program->run) + 20;
	unsigned char opcode;
	// first and second operand
	unsigned short fOp, sOp;
	// is the operation to be executed set?
	bool opToExec;
	// clear it with NOPs
	memset(start, 0x90, 9);

	//printf("start pointer: %p", start);

	do {

		opcode = program->bytecode[program->ipoint];
		fOp = program->bytecode[program->ipoint + 1];
		sOp = program->bytecode[program->ipoint + 3];

		opToExec = true;

		// if there are not enough bytes to form full instruction then exit
		if ((program->ipoint > program->bytecodeSize - 5) || (program->icount
				> INSTR_LIMIT)) {
			*start++ = 0xC9;
			*start++ = 0xC3;
		} else {

			switch (opcode) {

			case ADD_RI8:
				*start++ = 0x80;
				*start++ = 192 + (fOp / 8192); // 0xC0 = 192, modrm byte
				*start++ = program->bytecode[program->ipoint + 3];
				break;

			case ADD_MI8:
				*start++ = 0x80;
				*start++ = 0x05;
				*(long *) start = (long) (program->bytecode) + sOp;
				start += sizeof(long);
				*start++ = program->bytecode[program->ipoint + 3];
				break;

			case ADD_RR8:
				*start++ = 0x00;
				*start++ = 192 + ((sOp / 8192) << 3) + (fOp / 8192); // dest jest w dalszej czesci
				break;

			case ADD_MR8:
				*start++ = 0x00;
				*start++ = 5 + ((sOp / 8192) << 3); // 5 = 0b101
				*(long *) start = (long) (program->bytecode) + fOp;
				start += sizeof(long);
				break;

			case ADD_RM8:
				*start++ = 0x02;
				*start++ = 5 + ((fOp / 8192) << 3); // 5 = 0b101
				*(long *) start = (long) (program->bytecode) + sOp;
				start += sizeof(long);
				break;

			case AND_RI8:
				*start++ = 0x80;
				*start++ = 224 + (fOp / 8192); // 0xE0 = 224, modrm byte
				*start++ = program->bytecode[program->ipoint + 3];
				break;

			case AND_MI8:
				*start++ = 0x80;
				*start++ = 0x25;
				*(long *) start = (long) (program->bytecode) + sOp;
				start += sizeof(long);
				*start++ = program->bytecode[program->ipoint + 3];
				break;

			case AND_RR8:
				*start++ = 0x20;
				*start++ = 192 + ((sOp / 8192) << 3) + (fOp / 8192); // dest jest w dalszej czesci
				break;

			case AND_MR8:
				*start++ = 0x20;
				*start++ = 5 + ((sOp / 8192) << 3); // 5 = 0b101
				*(long *) start = (long) (program->bytecode) + fOp;
				start += sizeof(long);
				break;

			case AND_RM8:
				*start++ = 0x22;
				*start++ = 5 + ((fOp / 8192) << 3); // 5 = 0b101
				*(long *) start = (long) (program->bytecode) + sOp;
				start += sizeof(long);
				break;

			case CMP_RI8:
				*start++ = 0x80;
				*start++ = 0xF8 + (fOp / 8192); // modrm byte
				*start++ = program->bytecode[program->ipoint + 3];
				break;

			case CMP_MI8:
				*start++ = 0x80;
				*start++ = 0x3D;
				*(long *) start = (long) (program->bytecode) + sOp;
				start += sizeof(long);
				*start++ = program->bytecode[program->ipoint + 3];
				break;

			case CMP_RR8:
				*start++ = 0x38;
				*start++ = 192 + ((sOp / 8192) << 3) + (fOp / 8192); // dest jest w dalszej czesci
				break;

			case CMP_MR8:
				*start++ = 0x38;
				*start++ = 5 + ((sOp / 8192) << 3); // 5 = 0b101
				*(long *) start = (long) (program->bytecode) + fOp;
				start += sizeof(long);
				break;

			case CMP_RM8:
				*start++ = 0x3A;
				*start++ = 5 + ((fOp / 8192) << 3); // 5 = 0b101
				*(long *) start = (long) (program->bytecode) + sOp;
				start += sizeof(long);
				break;

			case TEST_RI8:
				*start++ = 0xF6;
				*start++ = 0xC0 + (fOp / 8192); // modrm byte
				*start++ = program->bytecode[program->ipoint + 3];
				break;

			case TEST_MI8:
				*start++ = 0xF6;
				*start++ = 0x05;
				*(long *) start = (long) (program->bytecode) + sOp;
				start += sizeof(long);
				*start++ = program->bytecode[program->ipoint + 3];
				break;

			case TEST_RR8:
				*start++ = 0x84;
				*start++ = 192 + ((sOp / 8192) << 3) + (fOp / 8192); // dest jest w dalszej czesci
				break;

			case TEST_MR8:
			case TEST_RM8:
				*start++ = 0x84;
				*start++ = 5 + ((sOp / 8192) << 3); // 5 = 0b101
				*(long *) start = (long) (program->bytecode) + fOp;
				start += sizeof(long);
				break;

			case OR_RI8:
				*start++ = 0x80;
				*start++ = 200 + (fOp / 8192); // 0xC8 = 200, modrm byte
				*start++ = program->bytecode[program->ipoint + 3];
				break;

			case OR_MI8:
				*start++ = 0x80;
				*start++ = 0x0D;
				*(long *) start = (long) (program->bytecode) + sOp;
				start += sizeof(long);
				*start++ = program->bytecode[program->ipoint + 3];
				break;

			case OR_RR8:
				*start++ = 0x08;
				*start++ = 192 + ((sOp / 8192) << 3) + (fOp / 8192); // dest jest w dalszej czesci
				break;

			case OR_MR8:
				*start++ = 0x08;
				*start++ = 5 + ((sOp / 8192) << 3); // 5 = 0b101
				*(long *) start = (long) (program->bytecode) + fOp;
				start += sizeof(long);
				break;

			case OR_RM8:
				*start++ = 0x0A;
				*start++ = 5 + ((fOp / 8192) << 3); // 5 = 0b101
				*(long *) start = (long) (program->bytecode) + sOp;
				start += sizeof(long);
				break;

			case XOR_RI8:
				*start++ = 0x80;
				*start++ = 0xF0 + (fOp / 8192); // modrm byte
				*start++ = program->bytecode[program->ipoint + 3];
				break;

			case XOR_MI8:
				*start++ = 0x80;
				*start++ = 0x35;
				*(long *) start = (long) (program->bytecode) + sOp;
				start += sizeof(long);
				*start++ = program->bytecode[program->ipoint + 3];
				break;

			case XOR_RR8:
				*start++ = 0x30;
				*start++ = 192 + ((sOp / 8192) << 3) + (fOp / 8192); // dest jest w dalszej czesci
				break;

			case XOR_MR8:
				*start++ = 0x30;
				*start++ = 5 + ((sOp / 8192) << 3); // 5 = 0b101
				*(long *) start = (long) (program->bytecode) + fOp;
				start += sizeof(long);
				break;

			case XOR_RM8:
				*start++ = 0x32;
				*start++ = 5 + ((fOp / 8192) << 3); // 5 = 0b101
				*(long *) start = (long) (program->bytecode) + sOp;
				start += sizeof(long);
				break;

			case SUB_RI8:
				*start++ = 0x80;
				*start++ = 232 + (fOp / 8192); // 0xE8 = 232, modrm byte
				*start++ = program->bytecode[program->ipoint + 3];
				break;

			case SUB_MI8:
				*start++ = 0x80;
				*start++ = 0x2D;
				*(long *) start = (long) (program->bytecode) + sOp;
				start += sizeof(long);
				*start++ = program->bytecode[program->ipoint + 3];
				break;

			case SUB_RR8:
				*start++ = 0x28;
				*start++ = 192 + ((sOp / 8192) << 3) + (fOp / 8192); // dest jest w dalszej czesci
				break;

			case SUB_MR8:
				*start++ = 0x28;
				*start++ = 5 + ((sOp / 8192) << 3); // 5 = 0b101
				*(long *) start = (long) (program->bytecode) + fOp;
				start += sizeof(long);
				break;

			case SUB_RM8:
				*start++ = 0x2A;
				*start++ = 5 + ((fOp / 8192) << 3); // 5 = 0b101
				*(long *) start = (long) (program->bytecode) + sOp;
				start += sizeof(long);
				break;

			case DEC_R8:
				*start++ = 0xFE;
				*start++ = 0xC8 + (fOp / 8192); // modrm byte
				break;

			case DEC_M8:
				*start++ = 0xFE;
				*start++ = 0x0D;
				*(long *) start = (long) (program->bytecode) + sOp;
				start += sizeof(long);
				break;

			case INC_R8:
				*start++ = 0xFE;
				*start++ = 0xC0 + (fOp / 8192); // modrm byte
				break;

			case INC_M8:
				*start++ = 0xFE;
				*start++ = 0x05;
				*(long *) start = (long) (program->bytecode) + sOp;
				start += sizeof(long);
				break;

			case NOT_R8:
				*start++ = 0xF6;
				*start++ = 0xD0 + (fOp / 8192); // modrm byte
				break;

			case NOT_M8:
				*start++ = 0xF6;
				*start++ = 0x15;
				*(long *) start = (long) (program->bytecode) + sOp;
				start += sizeof(long);
				break;

			case NEG_R8:
				*start++ = 0xF6;
				*start++ = 0xD8 + (fOp / 8192); // modrm byte
				break;

			case NEG_M8:
				*start++ = 0xF6;
				*start++ = 0x1D;
				*(long *) start = (long) (program->bytecode) + sOp;
				start += sizeof(long);
				break;

			case MOV_RI8:
				*start++ = 0xB0 + (fOp / 8192);
				*start++ = program->bytecode[program->ipoint + 3];
				break;

			case MOV_MI8:
				*start++ = 0xC6;
				*start++ = 0x05;
				*(long *) start = (long) (program->bytecode) + fOp;
				start += sizeof(long);
				*start++ = program->bytecode[program->ipoint + 3];
				break;

			case MOV_RR8:
				*start++ = 0x88;
				*start++ = 192 + ((sOp / 8192) << 3) + (fOp / 8192); // dest jest w dalszej czesci
				break;

			case MOV_MR8:
				*start++ = 0x88;
				*start++ = 5 + ((sOp / 8192) << 3); // 5 = 0b101
				*(long *) start = (long) (program->bytecode) + fOp;
				start += sizeof(long);
				break;

			case MOV_RM8:
				*start++ = 0x8A;
				*start++ = 5 + ((fOp / 8192) << 3); // 5 = 0b101
				*(long *) start = (long) (program->bytecode) + sOp;
				start += sizeof(long);
				break;

			case MUL_R8:
				*start++ = 0xF6;
				*start++ = *start++ = 0xE0 + (fOp / 8192); // modrm byte
				break;

			case MUL_M8:
				*start++ = 0xF6;
				*start++ = 0x25; // mulb
				*(long *) start = (long) (program->bytecode) + sOp;
				start += sizeof(long);
				break;

			case IMUL_R8:
				*start++ = 0xF6;
				*start++ = *start++ = 0xE8 + (fOp / 8192); // modrm byte
				break;

			case IMUL_M8:
				*start++ = 0xF6;
				*start++ = 0x2D; // mulb
				*(long *) start = (long) (program->bytecode) + sOp;
				start += sizeof(long);
				break;

			case INPUT_R8: // jak mov RI8
				if (program->inputIndex < program->inputSize) {
					*start++ = 0xB0 + (fOp / 8192); // do jakiego rejestru
					*start++ = program->input[program->inputIndex]; // co
					program->inputIndex++;
				} else {
					opToExec = false;
					program->ipoint += 5; // jump to next instruction
				}
				break;

			case INPUT_M8: // jak mov MI8 tak naprawde
				if (program->inputIndex < program->inputSize) {
					*start++ = 0xC6;
					*start++ = 0x05;
					*(long *) start = (long) (program->bytecode) + (long) fOp; // dokad
					start += sizeof(long);
					*start++ = program->input[program->inputIndex]; // co
					program->inputIndex++;
				} else {
					opToExec = false;
					program->ipoint += 5;
				}
				break;

			case OUTPUT_R8: // tez mov
				if (program->outputIndex < program->outputSize) {
					*start++ = 0x88;
					*start++ = 5 + ((fOp / 8192) << 3); // 5 = 0b101
					*(long *) start = (long) (program->output)
							+ (long) program->outputIndex;
					start += sizeof(long);
					program->outputIndex++;
				} else {
					opToExec = false;
					program->ipoint += 5;
				}
				break;

			case OUTPUT_M8: // kopiowanie tutaj, nie w machine code
				if (program->outputIndex < program->outputSize) {
					program->output[program->outputIndex]
							= program->bytecode[fOp];
					program->outputIndex++;
				} else {
					opToExec = false;
					program->ipoint += 5;
				}
				break;

			case OUTPUT_I8: // kopiowanie tutaj, nie w machine code
				if (program->outputIndex < program->outputSize) {
					program->output[program->outputIndex]
							= program->bytecode[program->ipoint + 1];
					program->outputIndex++;
				} else {
					opToExec = false;
					program->ipoint += 5;
				}
				break;

			case JMP_I16:
				program->ipoint = fOp;
				opToExec = false;
				// important part
				program->icount++;
				break;

			case JMP_M16:
				if (fOp == 65535) { // musze czyms dopelnic, bytecode to char
					program->ipoint = (unsigned short) program->bytecode[fOp]
							<< 8;
				} else {
					program->ipoint = fOp;
				}
				opToExec = false;
				// important part
				program->icount++;
				break;

			case JMPCC_I16:
				if (program->compState == NORMAL) { // set jump sequence
					program->conditionCheck = true;
					program->compState = JUMPCC;
					program->ipoint -= 5; // dzieki temu wroci na to samo miejsce
					// delegowanie zadania, troche czystosci w kodzie
					compileJmpcc(program);
				} else {
					opToExec = false;
					program->compState = NORMAL;
					if (program->conditionCheck) {
						program->ipoint = sOp;
					} else {
						program->ipoint += 5;
					}
				}
				break;

			case JMPCC_M16:
				if (program->compState == NORMAL) { // set jump sequence
					program->conditionCheck = true;
					program->compState = JUMPCC;
					program->ipoint -= 5; // dzieki temu wroci na to samo miejsce
					// delegowanie zadania, troche czystosci w kodzie
					compileJmpcc(program);
				} else {
					opToExec = false;
					program->compState = NORMAL;
					if (program->conditionCheck) {
						if (sOp == 65535) {
							// uzupelnij do short
							program->ipoint
									= ((unsigned short) program->bytecode[sOp])
											<< 8;
						} else {
							program->ipoint
									= (unsigned short) program->bytecode[sOp];
						}
					} else {
						program->ipoint += 5;
					}
				}
				break;

			case BCCALL:
				opToExec = false;
				if (program->callStackIndex < program->stackSize) {
					program->callStack[program->callStackIndex]
							= program->ipoint + 5;
					program->callStackIndex++;
					program->ipoint = fOp;
					program->icount++;
				} else {
					program->ipoint += 5;
				}
				break;

			case RET: // takes call stack into account
				if (program->callStackIndex == 0) {
					*start++ = 0xC9;
					*start++ = 0xC3;
				} else {
					opToExec = false;
					program->callStackIndex--;
					program->ipoint
							= program->callStack[program->callStackIndex];
					program->icount++;
				}
				break;

			default:
				opToExec = false;
				program->ipoint += 5;
			}

		}

	} while (!opToExec);

	// increase instruction offset
	program->ipoint += 5;

	program->icount++;

}

/*
 * Funkcja wpisujaca wielobajtowe instrukcje NOP od startu na dlugosc length
 * moze potem
 */
void fillNop(void* start, char length) {

}

/**
 * Zeby oddzielic switche, inaczej za duza funkcja kompilujaca, i tak juz srednio czytelne
 */
void compileJmpcc(bcprogram_t* program) {
	unsigned char *start = (unsigned char *) (program->run) + 20;
	unsigned short fOp = program->bytecode[program->ipoint + 1];
	switch (fOp % 32) {
	case A:
		*start++ = 0x77;
		*start++ = 7;
		break;
	case AE:
		*start++ = 0x73;
		*start++ = 7;
		break;
	case B:
		*start++ = 0x72;
		*start++ = 7;
		break;
	case BE:
		*start++ = 0x76;
		*start++ = 7;
		break;
	case C:
		*start++ = 0x72;
		*start++ = 7;
		break;
	case CXZ:
		*start++ = 0xE3;
		*start++ = 7;
		break;
	case E:
		*start++ = 0x74;
		*start++ = 7;
		break;
	case G:
		*start++ = 0x7F;
		*start++ = 7;
		break;
	case GE:
		*start++ = 0x7D;
		*start++ = 7;
		break;
	case L:
		*start++ = 0x7C;
		*start++ = 7;
		break;
	case LE:
		*start++ = 0x7E;
		*start++ = 7;
		break;
	case NA:
		*start++ = 0x76;
		*start++ = 7;
		break;
	case NAE:
		*start++ = 0x72;
		*start++ = 7;
		break;
	case NB:
		*start++ = 0x73;
		*start++ = 7;
		break;
	case NBE:
		*start++ = 0x77;
		*start++ = 7;
		break;
	case NC:
		*start++ = 0x73;
		*start++ = 7;
		break;
	case NE:
		*start++ = 0x75;
		*start++ = 7;
		break;
	case NG:
		*start++ = 0x7E;
		*start++ = 7;
		break;
	case NGE:
		*start++ = 0x7C;
		*start++ = 7;
		break;
	case NL:
		*start++ = 0x7D;
		*start++ = 7;
		break;
	case NLE:
		*start++ = 0x7F;
		*start++ = 7;
		break;
	case NO:
		*start++ = 0x71;
		*start++ = 7;
		break;
	case NP:
		*start++ = 0x7B;
		*start++ = 7;
		break;
	case NS:
		*start++ = 0x79;
		*start++ = 7;
		break;
	case NZ:
		*start++ = 0x75;
		*start++ = 7;
		break;
	case O:
		*start++ = 0x70;
		*start++ = 7;
		break;
	case P:
		*start++ = 0x7A;
		*start++ = 7;
		break;
	case PE:
		*start++ = 0x7A;
		*start++ = 7;
		break;
	case PO:
		*start++ = 0x7B;
		*start++ = 7;
		break;
	case S:
		*start++ = 0x78;
		*start++ = 7;
		break;
	case Z:
		*start++ = 0x74;
		*start++ = 7;
		break;
	default:
		// modulo 32 wiec kilka opcji jest niezagospodarowanych, ale dziala szybciej
		// dzielenie przez potege 2
		break;
	}
	// przypisz false do conditionCheck
	// jesli default lub jmp nie zadziala to w nastepnym kolku tylko sie ipoint zwiekszy
	// jesli true to ipoint zostanie zmieniony na wartosc z drugiego argumentu
	// zwykle mov_mi8

	*start++ = 0xC6;
	*start++ = 0x05;
	// adres zmiennej
	*(long *) start = (long) (&(program->conditionCheck));
	start += sizeof(long);
	// false, bool to jeden bajt
	*start++ = 0;
}
