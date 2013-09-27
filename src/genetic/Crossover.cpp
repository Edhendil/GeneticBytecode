/*
 * Crossover.cpp
 *
 *  Created on: 05-02-2011
 *      Author: edhendil
 *
 *  How to execute crossover, it uses the memory reserved by the parents
 */

#include "Crossover.h"
#include <cstdlib>
#include <ctime>

/**
 * Divides code only at one point
 * Can be made more efficient by moving whole ints instead of chars
 */
void singleCrossover(unsigned char* bytecodeA, unsigned char* bytecodeB,
		unsigned char* childcodeA, unsigned char* childcodeB,
		unsigned int length) {
	unsigned int crossIndex = (unsigned int) ((float) rand() / RAND_MAX
			* length);
	for (unsigned int i = 0; i < crossIndex; i++) {
		childcodeA[i] = bytecodeB[i];
		childcodeB[i] = bytecodeA[i];
	}
	for (unsigned int i = crossIndex; i < length; i++) {
		childcodeA[i] = bytecodeA[i];
		childcodeB[i] = bytecodeB[i];
	}
}

/**
 * Divides code at two points, between them exactly
 */
void doubleCrossover(unsigned char* bytecodeA, unsigned char* bytecodeB,
		unsigned char* childcodeA, unsigned char* childcodeB,
		unsigned int length) {
	unsigned int crossIndexLow = (unsigned int) ((float) rand() / RAND_MAX
			* length);
	unsigned int crossIndexHigh = (unsigned int) ((float) rand() / RAND_MAX
			* length);
	unsigned int crossIndexTemp;
	if (crossIndexLow > crossIndexHigh) {
		crossIndexTemp = crossIndexLow;
		crossIndexLow = crossIndexHigh;
		crossIndexHigh = crossIndexTemp;
	}
	for (unsigned int i = 0; i < crossIndexLow; i++) {
		childcodeA[i] = bytecodeA[i];
		childcodeB[i] = bytecodeB[i];
	}
	// the part that's being switched
	for (unsigned int i = crossIndexLow; i < crossIndexHigh; i++) {
		childcodeA[i] = bytecodeB[i];
		childcodeB[i] = bytecodeA[i];
	}
	for (unsigned int i = crossIndexHigh; i < length; i++) {
		childcodeA[i] = bytecodeA[i];
		childcodeB[i] = bytecodeB[i];
	}
}
