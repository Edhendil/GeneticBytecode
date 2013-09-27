/*
 Description : JIT genetic, instrukcje 8 bitowe, adresy 16 bitowe
 */

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <pthread.h>

#include "Genetic.h"
#include "Compiler.h"
#include "BCProgram.h"
#include "BCRuntime.h"
#include "GeneticEngine.h"
#include "genetic/TestCase.h"
#include "genetic/Fitness.h"
#include "genetic/TestSuite.h"
#include "genetic/TestSuiteGenerator.h"

void testing();

int main(void) {
	//ExecJIT_M();

	//	unsigned char one[5] = {'a','a','a','a','a'};
	//	unsigned char two[5] = {'a','b','c','d','e'};
	//	std::cout << evaluateFitness(one, 7, two, 5);
	//	printf("%f", evaluateFitness(one, 5, two, 5));

	//	char aaa = 42;
	//	printf("%c", aaa);

	testing();
	//printf("!!!Hello World!!!\n"); /* prints !!!Hello World!!! */
	return 0;
}

void testing() {
	srand((unsigned) time(0));
	geneticengine_t* engine = new geneticengine_t;
	initializeEngine(engine);
	initializePopulation(engine, 100);

//	engine->assignedTestSuite = createInEOutSuite(5);

	std::vector<bcprogram_t*>::iterator it;

	double max, avg, avgInstrCount;
	unsigned char* bestOutput;
	unsigned int bestOutLength = 0, bestICounter = 0;

	for (int j = 0; true; j++) {
		max = -1;
		bestICounter = -1;
		avg = 0;
		avgInstrCount = 0;
//		engine->assignedTestSuite = createInEOutSuite(50);
//		engine->assignedTestSuite = createInERevOutSuite(1);
		engine->assignedTestSuite = createSimpleMathSuite(100);
		runTests(engine);
		for (it = engine->programs->begin(); it != engine->programs->end(); it++) {
			if ((*it)->fitnessValue > max) {
				max = (*it)->fitnessValue;
				bestOutput = (*it)->output;
				bestOutLength = (*it)->outputIndex;
				bestICounter = (*it)->icount;
			}
			avg += (*it)->fitnessValue;
			avgInstrCount += (*it)->icount;
		}
		avg /= engine->programs->size();
		avgInstrCount /= engine->programs->size();
		printf(
				"%i M fit: %f. Avg fit: %f Best icount: %i Avg icount: %f Best: ",
				j + 1, max, avg, bestICounter, avgInstrCount);
//		for (unsigned int i = 0; i < bestOutLength; i++) {
//			printf("%c", bestOutput[i]);
//		}
//		printf(" In: ");
//		for (unsigned int i = 0; i < engine->assignedTestSuite->testCase->inputLength; i++) {
//			printf("%c", engine->assignedTestSuite->testCase->input[i]);
//		}
		printf("\n");
		if (max >= 100)
			break;
		testsuite_destroy(engine->assignedTestSuite);
		performCrossover(engine);
		performMutation(engine);
	}

	destroyGeneticEngine(engine);

}

void ExecJIT_M() {
	bcprogram_t test;

	bcprogram_initialize(&test);

	// testowy bytecode
	unsigned char* inputp = test.bytecode;
	*inputp = INPUT_R8;
	inputp += 5;

	*inputp++ = ADD_RI8;
	inputp += 2;
	*(unsigned short *) inputp = (unsigned short) 4;
	inputp += 2;

	*inputp = OUTPUT_R8;
	inputp += 5;

	*inputp = RET;
	inputp += 5;

	// testowy input
	test.input[0] = 'a';

	pthread_join(*startBCProgramThread(&test), NULL);

	std::cout << test.output[0];

	//int pthread_cancel(pthread_t thread); usuwa watek
}
