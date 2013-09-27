/*
 * TestCase.cpp
 *
 *  Created on: 05-02-2011
 *      Author: edhendil
 */

#include "TestCase.h"

testcase_t* testcase_initialize(testcase_t* testcase, unsigned int inputLen, unsigned int outputLen) {
	testcase->inputLength = inputLen;
	testcase->expectedLength = outputLen;
	testcase->input = new unsigned char[inputLen];
	testcase->expectedOut = new unsigned char[outputLen];
	return testcase;
}

void testcase_destroy(testcase_t* testcase) {
	delete testcase->input;
	delete testcase->expectedOut;
	delete testcase;
}
