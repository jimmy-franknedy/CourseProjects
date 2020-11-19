//-----------------------------------------------------------------------------
// IntegerQueue.h
// Header file for the Integer Queue ADT in C
//-----------------------------------------------------------------------------
#include<stdlib.h>
#include<stdio.h>

#ifndef _Queue_H_INCLUDE_
#define _Queue_H_INCLUDE_


// Exported type --------------------------------------------------------------

// IntegerQueue
// Exported reference type
typedef struct IntegerQueueObj* IntegerQueue;


// Constructors-Destructors ---------------------------------------------------

// newIntegerQueue()
// Constructor for the IntegerQueue ADT
IntegerQueue newIntegerQueue();

// freeIntegerQueue()
// Destructor for the Queue ADT
void freeIntegerQueue(IntegerQueue* pQ);


// ADT operations -------------------------------------------------------------

// isEmpty()
// Returns 1 (true) if Queue Q is empty, 0 (false) otherwise.
int isEmpty(IntegerQueue Q);

// length()
// Returns the number of elements in Q
int length(IntegerQueue Q);

// enqueue()
// Inserts x at back of Q.
void enqueue(IntegerQueue Q, int x);

// dequeue()
// Deletes and returns the item at front of Q.
// Pre: !isEmpty()
int dequeue(IntegerQueue Q);

// peek()
// Returns the item at front of Q.
// Pre: !isEmpty()
int peek(IntegerQueue Q);

// dequeueAll()
// Resets Q to the empty state.
void dequeueAll(IntegerQueue Q);


// Other Operations -----------------------------------------------------------

// IntegerQueueToString()
// Determines a text representation of IntegerQueue Q. Returns a pointer to a 
// char array, allocated from heap memory, containing the integer sequence 
// represented by Q. The sequence is traversed from front to back, each integer
// is added to the string followed by a single space. The array is terminated 
// by a NUL '\n' character. It is the responsibility of the calling function to 
// free this heap memory.
char* IntegerQueueToString(IntegerQueue Q);

// equals()
// Returns true (1) if Q and R are matching sequences of integers, false (0) 
// otherwise.
int equals(IntegerQueue Q, IntegerQueue R);


#endif
