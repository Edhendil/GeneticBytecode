/*
 * TestSuiteGenerator.cpp
 *
 *  Created on: 13-02-2011
 *      Author: edhendil
 */

#include "TestSuiteGenerator.h"
#include <cstdlib>
#include <cstdio>

testsuite_t* createInEOutSuite(unsigned int length) {
	unsigned int inputSize;
	testsuite_t* suite = new testsuite_t;
	testsuite_initialize(suite, length);

	for (unsigned int i = 0; i < length; i++) {
//		inputSize = (rand() % 20) + 10;
		inputSize = 10;
		testcase_t* test = new testcase_t;
		testcase_initialize(test, inputSize, inputSize);

		suite->testCases[i] = test;

		for (unsigned int i = 0; i < inputSize; i++) {
			unsigned char chara = rand() % 256;
			test->input[i] = chara;
			test->expectedOut[i] = chara;
		}
	}

	return suite;
}

testsuite_t* createInERevOutSuite(unsigned int length) {
	unsigned int inputSize;
	testsuite_t* suite = new testsuite_t;
	testsuite_initialize(suite, length);

	for (unsigned int i = 0; i < length; i++) {
//		inputSize = (rand() % 10) + 1;
		inputSize = 20;
		testcase_t* test = new testcase_t;
		testcase_initialize(test, inputSize, inputSize);

		suite->testCases[i] = test;

		for (unsigned int i = 0; i < inputSize; i++) {
			unsigned char chara = rand() % 256;
			test->input[i] = chara;
			test->expectedOut[inputSize-i-1] = chara;
		}
	}

	return suite;
}

// for now only +
// format: x + y =
// 2-3 digits
// ASCII 48 - 57 - digits
testsuite_t* createSimpleMathSuite(unsigned int length) {
	testsuite_t* suite = new testsuite_t;
	testsuite_initialize(suite, length);
	unsigned int argSize1, argSize2, inputSize, arg1, arg2, result, outputSize;
	char str1[3];
	char str2[3];
	char strres[4];

	for (unsigned int i = 0; i < length; i++) {
		arg1 = (rand() % 90) + 10;
		arg2 = (rand() % 90) + 10;

		result = arg1 + arg2;

		sprintf(str1, "%u", arg1);
		sprintf(str1, "%u", arg2);
		sprintf(strres, "%u", result);

		inputSize = 9;

		if (result > 99)
			outputSize = 3;
		else
			outputSize = 2;

		testcase_t* test = new testcase_t;
		testcase_initialize(test, inputSize, outputSize);

		suite->testCases[i] = test;

		test->input[0] = str1[0];
		test->input[1] = str1[1];
		test->input[2] = ' ';
		test->input[3] = '+';
		test->input[4] = ' ';
		test->input[5] = str2[0];
		test->input[6] = str2[1];
		test->input[7] = ' ';
		test->input[8] = '=';

		test->expectedOut[0] = strres[0];
		test->expectedOut[1] = strres[1];
		if (result > 99)
			test->expectedOut[2] = strres[2];
	}

	return suite;
}
