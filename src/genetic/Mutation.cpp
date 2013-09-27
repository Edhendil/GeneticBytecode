/*
 * Mutation.cpp
 *
 *  Created on: 05-02-2011
 *      Author: edhendil
 *
 * Mutation generator
 */

#include <cstdlib>
#include <ctime>
#include "Mutation.h"

/**
 * possibly with another argument - mutation mode
 * this way mutation can be performed on any part
 * will work only for length < 2^28 (3 for 8 bits, 1 for signed value of rand)
 */
void mutationPerBit(unsigned char* bytecode, unsigned int length) {
	unsigned int mutationTimes = (double) length * MUTATION_RATE;
	unsigned int bitIndex, byteIndex, bitOffset;
	unsigned int bitLength = length * 8;
	for (unsigned int i = 0; i < mutationTimes; i++) {
		bitIndex = rand() % bitLength;
		byteIndex = bitIndex / 8;
		bitOffset = bitIndex - byteIndex * 8;
		bytecode[byteIndex] = bytecode[byteIndex] ^ xorMasks[bitOffset];
	}
}

void mutationPerByte(unsigned char* bytecode, unsigned int length) {
	unsigned int mutationTimes = (double) length * MUTATION_RATE;
	unsigned int byteIndex;
	for (unsigned int i = 0; i < mutationTimes; i++) {
		byteIndex = rand() % length;
		bytecode[byteIndex] = rand() % 256;
	}
}
