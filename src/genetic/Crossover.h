/*
 * Crossover.h
 *
 *  Created on: 08-02-2011
 *      Author: edhendil
 */

#ifndef CROSSOVER_H_
#define CROSSOVER_H_

const int CROSSOVER_RATE = 0.7;

void singleCrossover(unsigned char* bytecodeA, unsigned char* bytecodeB,
		unsigned char* childcodeA, unsigned char* childcodeB,
		unsigned int length);

void doubleCrossover(unsigned char* bytecodeA, unsigned char* bytecodeB,
		unsigned char* childcodeA, unsigned char* childcodeB,
		unsigned int length);

#endif /* CROSSOVER_H_ */
