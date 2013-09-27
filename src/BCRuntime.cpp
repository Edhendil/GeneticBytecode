/*
 * BCRuntime.cpp
 *
 *  Created on: 08-02-2011
 *      Author: edhendil
 */

#include "BCRuntime.h"
#include "BCProgram.h"
#include <pthread.h>

void* runBCProgram(void* program) {
	bcprogram_t* prog = (bcprogram_t*) program;
	prog->run();
	pthread_exit( NULL);
}

pthread_t* startBCProgramThread(bcprogram_t* program) {
	pthread_t* progThread = new pthread_t();
	int rc;
	// zwraca kod, 0 dobrze, -1 zle
	rc = pthread_create(progThread, NULL, runBCProgram, program);
	return progThread;
}
