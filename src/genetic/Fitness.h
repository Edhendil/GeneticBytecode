/*
 * Fitness.h
 *
 *  Created on: 08-02-2011
 *      Author: edhendil
 */

#ifndef FITNESS_H_
#define FITNESS_H_

double evaluateStringFitness(unsigned char* output, unsigned int outLength,
		unsigned char* expected, unsigned int expLength);
double evaluateIntegerFitness(unsigned char* output, unsigned int outLength,
		unsigned char* expected, unsigned int expLength);

#endif /* FITNESS_H_ */
