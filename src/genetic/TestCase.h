/*
 * TestCase.h
 *
 *  Created on: 08-02-2011
 *      Author: edhendil
 */

#ifndef TESTCASE_H_
#define TESTCASE_H_

struct testcase_t {

	unsigned char* input;
	unsigned int inputLength;

	unsigned char* expectedOut;
	unsigned int expectedLength;

};

testcase_t* testcase_initialize(testcase_t* testcase, unsigned int inputLen, unsigned int outputLen);
void testcase_destroy(testcase_t* testcase);

#endif /* TESTCASE_H_ */
