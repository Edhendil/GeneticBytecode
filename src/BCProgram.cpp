/*
 * BCProgram.cpp
 *
 *  Created on: 05-02-2011
 *      Author: edhendil
 */

#include <sys/mman.h>
#include <string.h>

#include "BCProgram.h"
#include "Compiler.h"

/*
 * Should I reuse run function (memory associated with it)?
 * Many of them are required only if execute them at the same time.
 */
void bcprogram_initialize(bcprogram_t* program) {

	program->ipoint = 0;
	program->icount = 0;

	program->bytecode = new unsigned char[BYTECODE_LENGTH];
	program->bytecodeSize = BYTECODE_LENGTH;

	program->callStack = new unsigned short[STACK_LENGTH];
	program->stackSize = STACK_LENGTH;

	//program->input = new unsigned char[INPUT_LENGTH];
	//program->inputSize = INPUT_LENGTH;

	program->output = new unsigned char[OUTPUT_LENGTH];
	program->outputSize = OUTPUT_LENGTH;

	program->inputIndex = 0;
	program->outputIndex = 0;
	program->callStackIndex = 0;

	program->fitnessValue = 0.0;

	//memset(program->input, 0x00, program->inputSize);
	memset(program->output, 0x00, program->outputSize);
	memset(program->bytecode, 0x00, program->bytecodeSize);

	unsigned char* ncip, *instr = ncip = (unsigned char*) mmap(0, 32, PROT_READ
			| PROT_WRITE | PROT_EXEC, MAP_PRIVATE | MAP_ANON, -1, 0);

	// 3 sposoby na to samo
	// asm ("call *%%eax" : : "a" (compileNext)); // point to int zawierajacy nr pamieci
	// EXEC x = (EXEC)instr; x();
	// ((void(*)(void))instr)();

	*ncip++ = 0x55; // push %ebp
	*ncip++ = 0x89; // mov %esp, %ebp
	*ncip++ = 0xE5; // standardowy poczatek funkcji

	*ncip++ = 0x60; // pusha
	*ncip++ = 0x9C; // pushf

	*ncip++ = 0xB8; // mov eax,
	*(long *) ncip = (long) compileNext; //
	ncip += sizeof(long);

	*ncip++ = 0x68; // PUSH IMM32
	*(long *) ncip = (long) program; // rzut argumentu na stos
	ncip += sizeof(long);

	*ncip++ = 0xFF;
	*ncip++ = 0xD0; // call EAX

	*ncip++ = 0x58; // pop do eax, usuniecie argumentu

	*ncip++ = 0x9D; // popf
	*ncip++ = 0x61; // popa

	// instr NOOP, wiecej jesli bede chcial zlozone instr asm np. sys call jako jednosc
	*ncip++ = 0x66;
	*ncip++ = 0x0F;
	*ncip++ = 0x1F;
	*ncip++ = 0x84;
	*ncip++ = 0x00;
	*ncip++ = 0x00;
	*ncip++ = 0x00;
	*ncip++ = 0x00;
	*ncip++ = 0x00;

	*ncip++ = 0xEB;
	*ncip++ = -28; // JMP relative, to the start

	*ncip++ = 0x90; // NOP for aligning

	program->run = (bcexec_f) instr;

}

void bcprogram_destroy(bcprogram_t* program) {

	delete[] program->bytecode;
	if (program->input != NULL)
		delete[] program->input;
	delete[] program->output;
	delete[] program->callStack;

	munmap((void*) program->run, 32);

	delete program;
}
