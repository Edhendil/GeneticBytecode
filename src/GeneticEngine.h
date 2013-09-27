/*
 * GeneticEngine.h
 *
 *  Created on: 07-02-2011
 *      Author: edhendil
 */

#ifndef GENETICENGINE_H_
#define GENETICENGINE_H_

#include <vector>
#include "BCProgram.h"
#include "genetic/TestCase.h"
#include "genetic/TestSuite.h"

struct geneticengine_t {

	std::vector<bcprogram_t*>* programs;

	testcase_t* assignedTest;

	testsuite_t* assignedTestSuite;

};

void addProgramToPopulation(geneticengine_t* engine, bcprogram_t* program);

void assignTest(geneticengine_t* engine, testcase_t* test);

void initializePopulation(geneticengine_t* engine, unsigned int size);

void runTests(geneticengine_t* engine);

double testProgram(bcprogram_t* program, testcase_t* test);

void performCrossover(geneticengine_t* engine);

void performMutation(geneticengine_t* engine);

geneticengine_t* initializeEngine(geneticengine_t* engine);

void resetProgramsOutputs(geneticengine_t* engine);

void destroyGeneticEngine(geneticengine_t* engine);

#endif /* GENETICENGINE_H_ */
