/*
 * Compiler.h
 *
 *  Created on: 05-02-2011
 *      Author: edhendil
 */

#ifndef COMPILER_H_
#define COMPILER_H_

#include "BCProgram.h"

void compileNext(bcprogram_t* program);
void fillNop(void* start, char length);
void compileJmpcc(bcprogram_t* program);

#endif /* COMPILER_H_ */
