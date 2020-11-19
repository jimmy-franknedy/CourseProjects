//-----------------------------------------------------------------------------
// SimulationStub.c
//-----------------------------------------------------------------------------
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "Job.h"
#include "IntegerQueue.h"

//-----------------------------------------------------------------------------
// The following function may be of use in assembling the initial backup array.
// You may use it as is, alter it as you see fit, or delete it altogether.
//-----------------------------------------------------------------------------

// getjob()
// Reads two numbers from file in, and returns a new Job with those numbers
// as arrival and duration.
Job getJob(FILE* in)
{
   // a: arrival
   // d: duration
   int a, d;
   fscanf(in, "%d %d\n", &a, &d);
   return newJob(a, d);
}

// Notes ----------------------------------------------------------------------
//
// Arrival Time : the time at which a job becomes available for processing
// 
// Duration     : the amount of time the processor will consume when the job
//                comes int
//
// Finish Time  : the time it takes to reach the head of the processor que
//                finish_time = start_time-duration
//
// Wait time    : (red. finished time of a job) the time it took a job spent
//                waiting in line, not couting processing time.
//                wait_time = finish_time - arrival_time - duration
//       
// Goal         : find the following...
//              a) the total wait time (total time spend by all 𝑚 jobs 
//                 waiting in queues)
//              b) the maximum wait time (the longest wait any of the 𝑚 jobs endured)
//              c) the average wait time over all 𝑚 jobs.
//              d) determine these quantities for 𝑛 processors, 
//                 where 𝑛 ranges from 1 to 𝑚 − 1 
// File I/O     : input  > input_file
//              : output > input_file.rpt (report)
//                       > input_file.trc (trace)
// 
// Given        : Jobs are already ordered from arrival time
//                There are atleast 𝑚 lines!
// 
// Notes ----------------------------------------------------------------------

// main()
int main(int argc, char* argv[])
{
   // check command line arguments

   // check command line for correct number of arguments
   if(argc != 2)
   {
      fprintf(stderr, "Inproper Usage: Simulation input\n");
      exit(EXIT_FAILURE);
   }
   
   FILE* in;         // User input file
   FILE* out_rpt;    // Output file for report
   FILE* out_trc;    // Outpit file for trace

   // open input file for reading 
   in = fopen(argv[1], "r+");
   if(in == NULL)
   {  
      fprintf(stderr,"Unable to read from given input file!\n");
      exit(EXIT_FAILURE);
   }   

   // create 2 output files for writing into

      // create the output file for report
      char report[] = "";
      strcpy(report,argv[1]);
      strcat(report, ".rpt");
      out_rpt = fopen(report,"wr+");
      if(report == NULL)
      {  
         fprintf(stderr,"Unable to read & write from created report file!\n");
         exit(EXIT_FAILURE);
      }

      // create the output file for trace
      char trace[] = "";
      strcpy(trace,argv[1]);
      strcat(trace, ".trc");
      out_trc = fopen(trace,"wr+");
      if(trace == NULL)
      {  
         fprintf(stderr,"Unable to read & write from created trace file!\n");
         exit(EXIT_FAILURE);
      }

   // read in m jobs from input file and place them in backup array (an array of type job)

      // get the integer of the number of jobs
      char string_num_jobs[1];
      fgets(string_num_jobs,100,in);
      int int_num_jobs = atoi(string_num_jobs);

      // create an array of type job (i.e this is the backup array)
      // treat this as a saved copy of the array of jobs in order! (i.e copy array for use)
      Job* job_arr = calloc(int_num_jobs,sizeof(Job));

      // loop through the input array and create new jobs
      for(int i = 0; i<int_num_jobs; i++)
      {
         job_arr[i] = getJob(in);
      }

      // set up the report file (now that you have the number of jobs!)
      fprintf(out_rpt,"Report file: %s.rpt\n",argv[1]);
      fprintf(out_rpt,"%d Jobs:\n",int_num_jobs);
      for(int i = 0; i <int_num_jobs; i++)
      {
         printJob(out_rpt,job_arr[i]);
      }
      fprintf(out_rpt,"\n***********************************************************\n");

      // set up the trace file (now that you have the number of jobs!)
      fprintf(out_trc,"Trace file: %s.trc\n",argv[1]);
      fprintf(out_trc,"%d Jobs:\n",int_num_jobs);
      for(int i = 0; i <int_num_jobs; i++)
      {
         printJob(out_trc,job_arr[i]);
      }
      fprintf(out_trc,"\n"); 
      // declare and initialize an array of m-1 processor Queues along with
      // any necessary storage queues
      
      // Create an array of type IntegerQueue
      IntegerQueue* ProcessorQueue = calloc(int_num_jobs,sizeof(IntegerQueue));

      // Loop through the input array and create new IntegerQueues!
      for(int i = 0; i<int_num_jobs; i++)
      {
         ProcessorQueue[i] = newIntegerQueue();
      }

   // loop : run simulation with n processors for n=1 to n=m-1
   for(int num_processors = 1; num_processors <= int_num_jobs-1; num_processors++)
   {
      // check number of processors running
      fprintf(out_trc,"\n*****************************\n");
      if(num_processors == 1)
      {
         fprintf(out_trc,"1 processor:\n");
      }
      else
      {
         fprintf(out_trc,"%d processors:\n",num_processors);
      }
      fprintf(out_trc,"*****************************\n");
      // place Job indices from backup array into storage queue

      for(int i = 0; i <int_num_jobs; i++)
      {
         enqueue(ProcessorQueue[0],i);
      }

      int finishedJobs = 0;
      int time = 0;

      fprintf(out_trc,"time= %d\n",time);
      for(int i = 0; i <=num_processors; i++)
      {
         fprintf(out_trc,"%d: ",i);
         if(isEmpty(ProcessorQueue[i]) == 0)
         {
            int length_to_print = length(ProcessorQueue[i]);
            for(int i = 0; i <length_to_print; i++)
            {
               printJob(out_trc,job_arr[i]);
            }
         }
         fprintf(out_trc,"\n");
      }
      fprintf(out_trc,"\n");

      // loop process all Jobs in this simulation!
      while(finishedJobs != int_num_jobs)
      {
         // loop through the processors (NOT STORAGE and calculate their finish times!)
         for(int i = 0; i < num_processors; i++)
         {
            // if the processor is not empty and the index of job_arr that it holds does not have a finish value
            if(!(isEmpty(ProcessorQueue[i+1])) &&
               getFinish(job_arr[peek(ProcessorQueue[i+1])]) == -1)
            {
               // compute the finish time of the item to be dequeued from the storage!
               computeFinishTime(job_arr[peek(ProcessorQueue[i+1])],time);
            }
         }

         // loop variables
         int loop = 0;
         int loop_saved = 0;
         int tt_1 = 0;
         int tt_2 = 0;

         // make sure storage is not empty and that the item has NOT been queued!
         if(isEmpty(ProcessorQueue[0]) == 0 && getFinish(job_arr[peek(ProcessorQueue[0])]) == -1)
         {
            // set tt_1 to the head of the storageque arrival time
            tt_1 = getArrival(job_arr[peek(ProcessorQueue[0])]);
         }
         else // an early arrival time was not found :(
         {
            // loop through the processors
            for(loop = 0; loop < num_processors; loop++)
            {
               // make sure processors are not empty
               if(!(isEmpty(ProcessorQueue[loop+1])))
               {
                  // check to make sure the processor finish time is defined
                  if(getFinish(job_arr[peek(ProcessorQueue[loop+1])]) != -1)
                  {
                     // set the starting time to the earliest finishing time of a processor
                     tt_1 = getFinish(job_arr[peek(ProcessorQueue[loop+1])]);

                     // save the value of the loop
                     loop_saved = loop;

                     // leave the loop
                     loop = num_processors;
                  }
               }         
            }
         }
         // loop where you left off!
         for(int i = loop_saved; i<num_processors; i++)
         {
            // make sure processors are not empty
            if(isEmpty(ProcessorQueue[i+1]) == 0)
            {
               // check to make sure the processor finish time is defined
               if(getFinish(job_arr[peek(ProcessorQueue[i+1])]) != -1)
               {
                  // get the processor's finish time
                  tt_2 = getFinish(job_arr[peek(ProcessorQueue[i+1])]);

                  // if the processor finish time < (initially) the head storage arrival time
                  if(tt_1 > tt_2)
                  {
                     // set tt_1 to the lower time
                     tt_1 = tt_2;
                  }
               }
            }
         }
         // set time to the lowest "next" time
         time = tt_1;

         // if any Jobs finish now, then complete them in the order they appear in 
         // the queue array, i.e. lowest index first.
         for(int i = 0; i < num_processors; i++)
         {
            // make sure the processor is NOT empty
            if(!(isEmpty(ProcessorQueue[i+1])))
            {
               for(int p = 0; p < length(ProcessorQueue[i+1]); p++)
               {
                  // if processor finish time matches with "global" time
                  if(getFinish(job_arr[peek(ProcessorQueue[i+1])]) == time)
                  {
                     // dequeue the index of the job OFF the processor queue
                     int dequeued = dequeue(ProcessorQueue[i+1]);

                     // enqueue the index of the job ON the storage queue
                     enqueue(ProcessorQueue[0],dequeued);

                     // if applicable; update the finish time for the head of the curr. processor
                     // make sure procoessor is not Empty
                     if(!(isEmpty(ProcessorQueue[i+1])))
                     {
                        if(getFinish(job_arr[peek(ProcessorQueue[i+1])]) == -1)
                        {
                           computeFinishTime(job_arr[peek(ProcessorQueue[i+1])],time);
                        }
                     }
                     finishedJobs++;
                  }
               }
            }
         }

         if(finishedJobs == int_num_jobs)
         {
            fprintf(out_trc,"time= %d\n",time);
            for(int i = 0; i <=num_processors; i++)
            {
               fprintf(out_trc,"%d: ",i);
               if(!(isEmpty(ProcessorQueue[i])))
               {
                  int length_to_print = length(ProcessorQueue[i]);
                  for(int j = 0; j <length_to_print; j++)
                  {
                     // get the index of job_arr ar the current ProcessorQue
                     int index_to_print = dequeue(ProcessorQueue[i]);

                     // using the index collected from the processor que access the job_arr
                     printJob(out_trc,job_arr[index_to_print]);

                     // push back the value onto the processor
                     enqueue(ProcessorQueue[i],index_to_print);
                  }
               }
               fprintf(out_trc,"\n");
            }
            break;
         }

         // if any Jobs arrive now, then assign them to a processor queue 
         // of minimum length and with lowest index in the queue array.
         // (and if they're at the head then compute finish time?)
   
         // start by making sure that the storage queue is NOT empty
         if(!(isEmpty(ProcessorQueue[0])))
         {
            // make sure that the storage queue's head's arrival time == current time &&
            // make sure that storage queue's head finish time == -1 (i.e has NOT been queued)
            if(getArrival(job_arr[peek(ProcessorQueue[0])]) == time &&
               getFinish(job_arr[peek(ProcessorQueue[0])]) == -1)
            {
               // get the length of the storage que
               int storageLength = length(ProcessorQueue[0]);

               // loop through the storage que "storageLength" times
               for(int i = 0; i <storageLength; i++)
               {
                  // if the head of storage's arrival time == current time
                  if(getArrival(job_arr[peek(ProcessorQueue[0])]) == time)
                  {
                     // dequeue from the storage queue
                     int dequeued = dequeue(ProcessorQueue[0]);

                     // variable to check if an item has been sucessfully enqueued
                     int check_enq = 0;

                     // check to see if any processors are open!
                     for(int i = 0; i<num_processors; i++)
                     {
                        // this means that a processor has not been used!
                        if(isEmpty(ProcessorQueue[i+1]))
                        {
                           // put the item in the OPEN/FREE processor!
                           enqueue(ProcessorQueue[i+1], dequeued);
                           computeFinishTime(job_arr[peek(ProcessorQueue[i+1])],time);
                           // printf("enqueued[processors opened]\n");

                           // check that the item has succesfully been enqueued
                           check_enq = 1;

                           // get out of the loop now that you have sucessfully enqueued an item
                           i = num_processors;
                        }
                     }
                     // special case: ONLY 1 Processor! that means just load everything onto i
                     if(num_processors == 1 && !(isEmpty(ProcessorQueue[1])) && check_enq == 0)
                     {
                        // put the item in the ONLY processor!
                        enqueue(ProcessorQueue[1], dequeued);
                        check_enq = 1;
                     }
                     // variable used to save the index of the shortest processor queue
                     int saved_index;
                     if(check_enq == 0)
                     {
                        // get the length of the LAST processor queue
                        int shortLength = length(ProcessorQueue[num_processors]);

                        // get the index of the LAST processor queue
                        int short_index = num_processors;

                        // loop through the processor que (starting from last to first)
                        for(int i = num_processors-1; i != 0; i--)
                        {
                           saved_index = short_index;
                           // if the processor that we are looking at is not empty
                           if(!(isEmpty(ProcessorQueue[i])))
                           {
                              // get the length of the processor
                              int prcLength = length(ProcessorQueue[i]);
                              if(prcLength <= shortLength)
                              {
                                 // update the new shortest length
                                 shortLength = prcLength;

                                 // save the index of the processor with the new shortest length
                                 saved_index = i;
                                 short_index = i;
                              }
                           }
                        }
                        // now that we have found the shortest processor queue, we can finally enqueue!
                        enqueue(ProcessorQueue[saved_index],dequeued);
                        check_enq = 1;
                     }
                  }
               }
            }
         }
         fprintf(out_trc,"time= %d\n",time);
         for(int i = 0; i <=num_processors; i++)
         {
            fprintf(out_trc,"%d: ",i);
            if(!(isEmpty(ProcessorQueue[i])))
            {
               int length_to_print = length(ProcessorQueue[i]);
               for(int j = 0; j <length_to_print; j++)
               {
                  // get the index of job_arr ar the current ProcessorQue
                  int index_to_print = dequeue(ProcessorQueue[i]);

                  // using the index collected from the processor que access the job_arr
                  printJob(out_trc,job_arr[index_to_print]);

                  // push back the value onto the processor
                  enqueue(ProcessorQueue[i],index_to_print);
               }
            }
            fprintf(out_trc,"\n");
         }
         fprintf(out_trc,"\n");
      } 
   // calculate the totalWait , maxWait, and averageWait
   int totalWait = 0;
   int maxWait = 0;
   double averageWait = 0;

   // calculate the wait times
   for(int i = 0; i< int_num_jobs; i++)
   {
      // calculate the current wait time
      int result = getWaitTime(job_arr[i]);

      // add the calculated the current wait time to the running wait time
      totalWait +=result;

      // if the calculated maxWait is greater than the current maxWait
      if(maxWait < result)
      {
         // update the the maxWait time
         maxWait = result;
      }
   }

   // calculate the average wait time
   averageWait = (double)totalWait / (double)int_num_jobs;
   if(num_processors == 1)
   {
      fprintf(out_rpt,"1 processor: totalWait=%d, maxWait=%d, averageWait=%.2f\n",totalWait,maxWait,averageWait);
   }
   else
   {
      fprintf(out_rpt,"%d processors: totalWait=%d, maxWait=%d, averageWait=%.2f\n",num_processors,totalWait,maxWait,averageWait);
   }
  
   // place Job indices from backup array into storage queue
      for(int i = 0; i <int_num_jobs; i++)
      {
         resetFinishTime(job_arr[i]);
         dequeue(ProcessorQueue[0]);
      }
   }
   
   // free all heap memory, close input and output files
   for(int i = 0; i<int_num_jobs; i++)
   {
      freeJob(&job_arr[i]);
      freeIntegerQueue(&ProcessorQueue[i]);
   }

   free(job_arr);
   job_arr = NULL;
   free(ProcessorQueue);
   ProcessorQueue = NULL;
   fclose(in);
   fclose(out_trc);
   fclose(out_rpt);
   return EXIT_SUCCESS;
}