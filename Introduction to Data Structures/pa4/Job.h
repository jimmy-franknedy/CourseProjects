//-----------------------------------------------------------------------------
// Job.h
// Header file for a simple ADT encapsulating three integer quantities:
// 
//                    (arrival, duration, finish)
//
//-----------------------------------------------------------------------------
#include<stdlib.h>
#include<stdio.h>

#ifndef _JOB_H_INCLUDE_
#define _JOB_H_INCLUDE_

#define UNDEF -1


// Exported Type --------------------------------------------------------------

typedef struct JobObj* Job;


// Constructors and Destructors -----------------------------------------------

// newJob()
// Constructor for the Job ADT.
Job newJob(int a, int d);

// freeJob()
// Destructor for the Job ADT.
void freeJob(Job* pJ);


// Access Functions -----------------------------------------------------------

// getArrival()
// Returns arrival time of J.
int getArrival(Job J);

// getDuration()
// Returns duration of J.
int getDuration(Job J);

// getFinish()
// Returns finish time of J.
int getFinish(Job J);

// getWaitTime()
// Returns wait time of J. 
// Pre: getFinish(J) != UNDEF.
int getWaitTime(Job J);


// Manipulation Procedures ----------------------------------------------------

// computeFinishTime()
// Sets finish time of J, given the current time.
void computeFinishTime(Job J, int timeNow);

// resetFinishTime()
// Sets finish time of J to UNDEF.
void resetFinishTime(Job J);


// Other Functions ------------------------------------------------------------

// printJob()
// Prints J to file stream out in format:  (arrival, duration, finish)
void printJob(FILE* out, Job J);


#endif
