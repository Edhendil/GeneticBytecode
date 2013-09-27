/*
 * Mutation.h
 *
 *  Created on: 08-02-2011
 *      Author: edhendil
 */

#ifndef MUTATION_H_
#define MUTATION_H_

#include <cstdlib>

const double MUTATION_RATE = 0.05;
const int MUTATION_LEVEL = MUTATION_RATE * RAND_MAX;

const unsigned char xorMasks[] = { 1, 2, 4, 8, 16, 32, 64, 128 };

/**
 * possibly with another argument - mutation mode
 * this way mutation can be performed on any part
 */
void mutationPerBit(unsigned char* bytecode, unsigned int length);
void mutationPerByte(unsigned char* bytecode, unsigned int length);

#endif /* MUTATION_H_ */
