/*
 * BCRuntime.h
 *
 *  Created on: 08-02-2011
 *      Author: edhendil
 */

#ifndef BCRUNTIME_H_
#define BCRUNTIME_H_

#include <pthread.h>
#include "BCProgram.h"

void* runBCProgram(void* program);
pthread_t* startBCProgramThread(bcprogram_t* program);

#endif /* BCRUNTIME_H_ */
