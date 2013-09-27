/*
 * TestSuiteGenerator.h
 *
 *  Created on: 13-02-2011
 *      Author: edhendil
 */

#ifndef TESTSUITEGENERATOR_H_
#define TESTSUITEGENERATOR_H_

#include "TestSuite.h"

testsuite_t* createInEOutSuite(unsigned int length);

testsuite_t* createSimpleMathSuite(unsigned int length);

testsuite_t* createInERevOutSuite(unsigned int length);

#endif /* TESTSUITEGENERATOR_H_ */
