//-----------------------------------------------------------------------------
// Job.c
// Implementation file for a simple ADT encapsulating three integer quantities:
// 
//                    (arrival, duration, finish)
//
//-----------------------------------------------------------------------------
#include<stdlib.h>
#include<stdio.h>
#include"Job.h"


// Private Type ---------------------------------------------------------------

typedef struct JobObj
{
   int arrival;
   int duration;
   int finish;
} JobObj;


// Constructors and Destructors -----------------------------------------------

// newJob()
// Constructor for the Job ADT.
Job newJob(int a, int d)
{
   Job J = malloc(sizeof(JobObj));
   J->arrival = a;
   J->duration = d;
   J->finish = UNDEF;
   return J;
}

// freeJob()
// Destructor for the Job ADT.
void freeJob(Job* pJ)
{
   if( pJ!=NULL && *pJ!=NULL )
   {
      free(*pJ);
      *pJ = NULL;
   }
}


// Access Functions -----------------------------------------------------------

// getArrival()
// Returns arrival time of J.
int getArrival(Job J)
{
   if( J==NULL )
   {
      fprintf(stderr, 
      "Job Error: calling getArrival() on NULL Job reference\n");
      exit(EXIT_FAILURE);
   }
   return J->arrival;
}

// getDuration()
// Returns duration of J.
int getDuration(Job J)
{
   if( J==NULL )
   {
      fprintf(stderr, 
      "Job Error: calling getDuration() on NULL Job reference\n");
      exit(EXIT_FAILURE);
   }
   return J->duration;
}

// getFinish()
// Returns finish time of J.
int getFinish(Job J)
{
   if( J==NULL )
   {
      fprintf(stderr, 
      "Job Error: calling getFinish() on NULL Job reference\n");
      exit(EXIT_FAILURE);
   }
   return J->finish;
}

// getWaitTime()
// Returns wait time of J. 
// Pre: getFinish(J) != UNDEF.
int getWaitTime(Job J)
{
   if( J==NULL )
   {
      fprintf(stderr, 
      "Job Error: calling getWaitTime() on NULL Job reference\n");
      exit(EXIT_FAILURE);
   }
   if( (J->finish)==UNDEF )
   {
      fprintf(stderr, 
      "Job Error: calling getWaitTime() when finish time undefined\n");
      exit(EXIT_FAILURE);
   }
   return (J->finish) - (J->duration) - (J->arrival);
}


// Manipulation Procedures ----------------------------------------------------

// computeFinishTime()
// Sets finish time of J, given the current time.
void computeFinishTime(Job J, int timeNow)
{
   if( J==NULL )
   {
      fprintf(stderr, 
      "Job Error: computeFinishTime() on NULL Job reference\n");
      exit(EXIT_FAILURE);
   }
   (J->finish) = timeNow + (J->duration);
}

// resetFinishTime()
// Sets finish time of J to UNDEF.
void resetFinishTime(Job J)
{
   if( J==NULL )
   {
      fprintf(stderr, 
      "Job Error: resetFinishTime() on NULL Job reference\n");
      exit(EXIT_FAILURE);
   }
   (J->finish) = UNDEF;
}


// Other Functions ------------------------------------------------------------

// printJob()
// Prints J to file stream out in format:  (arrival, duration, finish)
void printJob(FILE* out, Job J)
{
   if( J==NULL )
   {
      fprintf(stderr, 
         "Job Error: printJob() on NULL Job reference\n");
      exit(EXIT_FAILURE);
   }
   fprintf(out, "(%d, ", J->arrival);
   fprintf(out, "%d, ", J->duration);
   if( (J->finish)==UNDEF )
   {
      fprintf(out, "*) ");
   }
   else
   {
      fprintf(out, "%d) ", J->finish);
   }
}
