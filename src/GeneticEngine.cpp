/*
 * GeneticEngine.cpp
 *
 *  Created on: 07-02-2011
 *      Author: edhendil
 *
 * Holds info on all programs in the environment
 */

#include "GeneticEngine.h"
#include "BCProgram.h"
#include "BCRuntime.h"
#include "genetic/TestCase.h"
#include "genetic/TestSuite.h"
#include "genetic/Fitness.h"
#include "genetic/Crossover.h"
#include "genetic/Mutation.h"

#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>
#include <sys/mman.h>
#include <string.h>
#include <stdio.h>

void addProgramToPopulation(geneticengine_t* engine, bcprogram_t* program) {
	engine->programs->push_back(program);
}

void assignTest(geneticengine_t* engine, testcase_t* test) {
	engine->assignedTest = test;
}

void foreachDelete(bcprogram_t* program) {
	bcprogram_destroy(program);
}

double testProgram(bcprogram_t* program, testcase_t* test) {
	// prep
	program->input = test->input;
	program->inputSize = test->inputLength;
	program->inputIndex = 0;
	program->outputIndex = 0;
	program->callStackIndex = 0;
	program->ipoint = 0;
	program->icount = 0;
	memset(program->output, 0, program->outputSize);
	// run and wait
	pthread_t* thread;
	pthread_join(*(thread = startBCProgramThread(program)), NULL);
	delete thread;
	program->input = NULL;

	// assign fitness
//	return evaluateStringFitness(program->output, program->outputIndex,
//			test->expectedOut, test->expectedLength);
	return evaluateIntegerFitness(program->output, program->outputIndex,
				test->expectedOut, test->expectedLength);
}

/**
 * create programs, randomize their bytecode, add them to population
 *
 * Z jakiegos powodu tworzenie nowego programu jest kosztowne czasowo, tworzenie bytecode?
 */
void initializePopulation(geneticengine_t* engine, unsigned int size) {
	engine->programs->clear();
	for (unsigned int i = 0; i < size; i++) {
		bcprogram_t* program = new bcprogram_t();
		bcprogram_initialize(program);
		for (unsigned int j = 0; j < program->bytecodeSize; j++) {
			program->bytecode[j] = rand() % 256;
		}
		addProgramToPopulation(engine, program);
	}
}

/**
 * copy tests to programs
 * run programs
 * assign fitness value
 */
void runTests(geneticengine_t* engine) {
	std::vector<bcprogram_t*>::iterator it;
	double testValue;

	for (it = engine->programs->begin(); it != engine->programs->end(); it++) {
		(*it)->fitnessValue = 0;
	}

	for (unsigned int i = 0; i < engine->assignedTestSuite->testSize; i++) {
		for (it = engine->programs->begin(); it != engine->programs->end(); it++) {

			testValue = testProgram(*it, engine->assignedTestSuite->testCases[i]);
			//if (testValue > 100)
			//	(*it)->fitnessValue += 200;
			//else
			// this way there wont be any neverending loops
			if ((*it)->icount < 1002)
				(*it)->fitnessValue += testValue;
		}
	}

	for (it = engine->programs->begin(); it != engine->programs->end(); it++) {
		(*it)->fitnessValue = (*it)->fitnessValue
				/ (engine->assignedTestSuite->testSize);
	}
}

/*
 *  first match mates
 second do crossover
 third replace old population with new
 */
void performCrossover(geneticengine_t* engine) {

	std::vector<bcprogram_t*>* oldpop = engine->programs;
	std::vector<bcprogram_t*>* newpop = new std::vector<bcprogram_t*>();
	engine->programs = newpop;

	double fitnessLookup[oldpop->size()];
	unsigned int i = 0;

	std::vector<bcprogram_t*>::iterator it;
	for (it = oldpop->begin(); it != oldpop->end(); it++) {
		fitnessLookup[i] = (*it)->fitnessValue;
		++i;
	}

	unsigned int mateAIndex, mateBIndex;
	bcprogram_t* mateA, *mateB, *childA, *childB;

	for (unsigned int j = 0; j < oldpop->size() / 2; j++) {

		// the best of two technique
		unsigned int potA = rand() % oldpop->size();
		unsigned int potB;
		do {
			potB = rand() % oldpop->size();
		} while (potA == potB);

		if (fitnessLookup[potA] >= fitnessLookup[potB])
			mateAIndex = potA;
		else
			mateAIndex = potB;

		potA = rand() % oldpop->size();
		do {
			potB = rand() % oldpop->size();
		} while (potA == potB);

		if (fitnessLookup[potA] >= fitnessLookup[potB])
			mateBIndex = potA;
		else
			mateBIndex = potB;

		i = 0;
		for (it = oldpop->begin(); it != oldpop->end(); it++) {
			if (i == std::min(mateAIndex, mateBIndex)) {
				mateA = (*it);
			}
			if (i == std::max(mateAIndex, mateBIndex)) {
				mateB = (*it);
				break;
			}
			++i;
		}

		childA = new bcprogram_t();
		childB = new bcprogram_t();
		bcprogram_initialize(childA);
		bcprogram_initialize(childB);

		doubleCrossover(mateA->bytecode, mateB->bytecode, childA->bytecode,
				childB->bytecode, mateA->bytecodeSize);

		newpop->push_back(childA);
		newpop->push_back(childB);

	}

	// delete all former programs
	for_each(oldpop->begin(), oldpop->end(), foreachDelete);

	oldpop->clear();

	delete oldpop;

}

void performMutation(geneticengine_t* engine) {
	std::vector<bcprogram_t*>::iterator it;

	for (it = engine->programs->begin(); it != engine->programs->end(); it++) {
		mutationPerByte((*it)->bytecode, (*it)->bytecodeSize);
	}
}

geneticengine_t* initializeEngine(geneticengine_t* engine) {
	engine->programs = new std::vector<bcprogram_t*>;
	return engine;
}

/**
 * tylko jezeli poza normalnym cyklem testy robione
 */
void resetProgramsOutputs(geneticengine_t* engine) {
	std::vector<bcprogram_t*>::iterator it;

	for (it = engine->programs->begin(); it != engine->programs->end(); it++) {
		(*it)->outputIndex = 0;
		memset((*it)->output, 0, OUTPUT_LENGTH);
	}
}

/**
 * and all programs inside it
 */
void destroyGeneticEngine(geneticengine_t* engine) {
	std::vector<bcprogram_t*>::iterator it;

	for (it = engine->programs->begin(); it != engine->programs->end(); it++) {
		bcprogram_destroy(*it);
	}

	delete engine->programs;
	delete engine->assignedTestSuite;

	delete engine;
}
