/*
 * TestSuite.h
 *
 *  Created on: 13-02-2011
 *      Author: edhendil
 */

#ifndef TESTSUITE_H_
#define TESTSUITE_H_

#include "TestCase.h"

struct testsuite_t {

	unsigned int testSize;
	testcase_t** testCases;

};

void testsuite_initialize(testsuite_t* suite, unsigned int length);

void testsuite_destroy(testsuite_t* suite);

#endif /* TESTSUITE_H_ */
