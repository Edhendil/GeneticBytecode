/*
 * TestSuite.cpp
 *
 *  Created on: 13-02-2011
 *      Author: edhendil
 *
 *  Zestaw testów, w tym dynamicznie zmieniajace sie testy, losowy input i generowanie do niego output
 */

#include "TestSuite.h"
#include "TestCase.h"

#include <cstdlib>

void testsuite_initialize(testsuite_t* suite, unsigned int length) {
	suite->testSize = length;
	suite->testCases = new testcase_t*[length];
}

void testsuite_destroy(testsuite_t* suite) {
	for (unsigned int i = 0; i < suite->testSize; i++) {
		testcase_destroy(suite->testCases[i]);
	}
	delete suite->testCases;
	delete suite;
}
