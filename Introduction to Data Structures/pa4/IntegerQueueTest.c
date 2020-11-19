//-----------------------------------------------------------------------------
// IntegerQueueTest.c
// Test client for the IntegerQueue ADT
//-----------------------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include"IntegerQueue.h" 
// #include"IntegerQueue.c"

int main(){

   int i, j;
   char* strA;
   char* strB;

   IntegerQueue A = newIntegerQueue();
   IntegerQueue B = newIntegerQueue();

   printf("%s\n", isEmpty(A)?"true":"false");
   printf("%s\n", isEmpty(B)?"true":"false");

   enqueue(A, 5);
   enqueue(A, 3);
   enqueue(A, 9);
   enqueue(A, 7);
   enqueue(A, 8);

   printf("%s\n", isEmpty(A)?"true":"false");
   strA = IntegerQueueToString(A);
   printf("%s\n", strA);
   free(strA);

   printf("%d\n", peek(A));
   dequeue(A);
   dequeue(A);
   dequeue(A);
   printf("%d\n", peek(A));

   strA = IntegerQueueToString(A);
   printf("%s\n", strA);
   free(strA);
   enqueue(B, 7);
   enqueue(B, 8);
   strB = IntegerQueueToString(B);
   printf("%s\n", strB);
   free(strB);



   printf("%s\n", equals(A, B)?"true":"false");
   enqueue(A, 12);
   enqueue(B, 13); 


   strA = IntegerQueueToString(A);
   printf("%s\n", strA);
   free(strA);

   strB = IntegerQueueToString(B);
   printf("%s\n", strB);
   free(strB);

   printf("%s\n", equals(A, B)?"true":"false");

   dequeueAll(A);
   dequeueAll(B);
   printf("%s\n", isEmpty(A)?"true":"false");
   printf("%s\n", isEmpty(B)?"true":"false");

   freeIntegerQueue(&A);
   freeIntegerQueue(&B);

   A = newIntegerQueue();
   B = newIntegerQueue();

   for(i=0; i<10; i++){
      enqueue(A, i);
   }

   strA = IntegerQueueToString(A);
   strB = IntegerQueueToString(B);
   printf("A: %s\n", strA);
   printf("B: %s\n", strB);
   free(strA);
   free(strB);  

   while( !isEmpty(A) ){
      j = dequeue(A);
      enqueue(B, j);
      if( j%3==0 ){
         j = dequeue(B);
         enqueue(A, j);
      }
      strA = IntegerQueueToString(A);
      strB = IntegerQueueToString(B);
      printf("A: %s\n", strA);
      printf("B: %s\n", strB);
      free(strA);
      free(strB);
   }

   /***********************/
   // Kill Program //
   freeIntegerQueue(&A);
   freeIntegerQueue(&B);
   return EXIT_SUCCESS;
      // Kill Program //
   /**********************/ 

}

/* Output of this program: ****************************************************
true                            
true 
false
5 3 9 7 8
5
7
7 8
7 8
true
7 8 12
7 8 13
false
true
true
A: 0 1 2 3 4 5 6 7 8 9
B:
A: 1 2 3 4 5 6 7 8 9 0
B:
A: 2 3 4 5 6 7 8 9 0
B: 1
A: 3 4 5 6 7 8 9 0
B: 1 2
A: 4 5 6 7 8 9 0 1
B: 2 3
A: 5 6 7 8 9 0 1
B: 2 3 4
A: 6 7 8 9 0 1
B: 2 3 4 5
A: 7 8 9 0 1 2
B: 3 4 5 6
A: 8 9 0 1 2
B: 3 4 5 6 7
A: 9 0 1 2
B: 3 4 5 6 7 8
A: 0 1 2 3
B: 4 5 6 7 8 9
A: 1 2 3 4
B: 5 6 7 8 9 0
A: 2 3 4
B: 5 6 7 8 9 0 1
A: 3 4
B: 5 6 7 8 9 0 1 2
A: 4 5
B: 6 7 8 9 0 1 2 3
A: 5
B: 6 7 8 9 0 1 2 3 4
A:
B: 6 7 8 9 0 1 2 3 4 5
******************************************************************************/