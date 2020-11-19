//-----------------------------------------------------------------------------
// IntegerQueue.h
// Header file for the Integer Queue ADT in C
//-----------------------------------------------------------------------------
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "IntegerQueue.h"

// Exported type --------------------------------------------------------------

// NodeObj 
typedef struct NodeObj
{
	// value of the integer in the Node
	int value;

	// pointer to the next item in the linked list
	struct NodeObj* next;

	// pointer to the prev item in the linked list
	struct NodeObj* prev;

} NodeObj;

// creating instance of Node
typedef struct NodeObj* Node;

// newNode()
// Constructor for Node Type
// Node newNode(char* key, char* value)
Node newNode(int input)
{
	// allocate space on the heap for the size of NodeObj
	Node N = malloc(sizeof(NodeObj));
	// check to see if allocation was valid
	assert(N!=NULL);

	// set the input value into the Node
	N->value = input;

	// isolate the node by setting it's next and previous to NULL
	N->next = N->prev = NULL;

	// return the created node
	return N;
}

// freeNode()
// Destructor for Node Type
void freeNode(Node* pN)
{
	// check to see if the values of pN and *pN are not NULL
	if( pN!=NULL && *pN!=NULL )
	{
		// free the memory pointed to by pN
		free(*pN);

		// set pN to point to Null
		*pN = NULL;
	}
}

// IntegerQueue
// Exported reference type
typedef struct IntegerQueueObj
{
	// Node for the head of the array
	Node head;

	// Node for the tail of the array
	Node tail;

	// Counter to hold the number of nodes in the que
	int length;

}IntegerQueueObj;

void deleteAll(Node N);

// Pre: make sure you are starting at the head!
void deleteAll(Node N)
{
	// if you haven't reach the tail yet
	if(N != NULL)
	{
		// recurse until you find the tail
		deleteAll(N->next);

		// recurse back and free the memory on the heap
		freeNode(&N);
	}
}


// Constructors-Destructors ---------------------------------------------------

// makeEmpty()
// Reset Q to the empty state.
void makeEmpty(IntegerQueue Q)
{
	// check to see if the Dictionary is not NULL
	if(Q == NULL)
	{
		fprintf(stderr, "IntegerQueue Error: makeEmpty() called on NULL "\
		"IntegerQueue reference");
		exit(EXIT_FAILURE);
	}
	deleteAll(Q->head);
	Q->head = Q->tail = NULL;
	Q->length = 0;
}

// newIntegerQueue()
// Constructor for the IntegerQueue ADT
IntegerQueue newIntegerQueue()
{
	IntegerQueue Q = malloc(sizeof(IntegerQueueObj));
	Q->head = Q->tail = NULL;
	Q->length = 0;
	return Q;
}

// freeIntegerQueue()
// Destructor for the Queue ADT
void freeIntegerQueue(IntegerQueue* pQ)
{
	if(pQ != NULL && *pQ != NULL)
	{
		makeEmpty(*pQ);
		free(*pQ);
		*pQ = NULL;
	}
}


// ADT operations -------------------------------------------------------------

// isEmpty()
// Returns 1 (true) if Queue Q is empty, 0 (false) otherwise.
int isEmpty(IntegerQueue Q)
{
	if( Q==NULL )
	{
		fprintf(stderr, "IntegerQueue Error: isEmpty() called on NULL "\
		"IntegerQueue reference");
		exit(EXIT_FAILURE);
	}
	if(Q->length == 0) return 1;
	return 0;
}

// length()
// Returns the number of elements in Q
int length(IntegerQueue Q)
{
	if( Q==NULL )
	{
		fprintf(stderr, "IntegerQueue Error: length() called on NULL "\
			"IntegerQueue reference");
		exit(EXIT_FAILURE);
	}
	if(!isEmpty(Q)) return Q->length;
	return 0;
}

// enqueue()
// Inserts x at back of Q.
void enqueue(IntegerQueue Q, int x)
{
	if( Q==NULL )
	{
		fprintf(stderr, "IntegerQueue Error: enqueue() called on NULL "\
		"IntegerQueue reference");
		exit(EXIT_FAILURE);
	}

	// Create a new que!
	Node new = newNode(x);

	// if the HEAD & TAIL are BOTH NULL
	if(Q->head == NULL && Q->tail == NULL && Q->length == 0)
	{
		Q->head = Q->tail = new;
	}

	// if the HEAD and TAIL are ONE
	else if(Q->head == Q->tail && Q->length == 1)
	{
		Q->tail = new;
		Q->head->next = Q->tail;
		Q->tail->prev = Q->head;
	}
	
	// if neither HEAD OR TAIL are NULL (i.e the head and tail are already established)
	else if(Q->head != Q->tail && Q->length > 1)
	{
		// Link the new Node after the tail
		Q->tail->next = new;
		new->prev = Q->tail;
		Q->tail = new;
	}

	// increment the length of the integerQue!
	Q->length++;
}

// dequeue()
// Deletes and returns the item at front of Q.
// Pre: !isEmpty()
int dequeue(IntegerQueue Q)
{
	if( Q==NULL )
	{
		fprintf(stderr, "IntegerQueue Error: dequeue() called on NULL "\
		"IntegerQueue reference");
		exit(EXIT_FAILURE);
	}
	Q->length--;
	Node temp = Q->head;
	int output = temp->value;
	if(Q->head == Q->tail)
	{
		Q->head = Q->tail = NULL;
	}
	else
	{
		Q->head = Q->head->next;
	}
	freeNode(&temp);
	return output;
}

// peek()
// Returns the item at front of Q.
// Pre: !isEmpty()
int peek(IntegerQueue Q)
{
	if( Q==NULL )
	{
		fprintf(stderr, "IntegerQueue Error: peek() called on NULL "\
		"IntegerQueue reference");
		exit(EXIT_FAILURE);
	}
	return (Q->head->value);
}

// dequeueAll()
// Resets Q to the empty state.
void dequeueAll(IntegerQueue Q)
{
	if( Q==NULL )
	{
		fprintf(stderr, "IntegerQueue Error: dequeueAll() called on NULL "\
		"IntegerQueue reference");
		exit(EXIT_FAILURE);
	}
	deleteAll(Q->head);
	Q->head = Q->tail = NULL;
	Q->length = 0;
}


// Other Operations -----------------------------------------------------------

// IntegerQueueToString()
// Determines a text representation of IntegerQueue Q. Returns a pointer to a 
// char array, allocated from heap memory, containing the integer sequence 
// represented by Q. The sequence is traversed from front to back, each integer
// is added to the string followed by a single space. The array is terminated 
// by a NUL '\n' character. It is the responsibility of the calling function to 
// free this heap memory.
char* IntegerQueueToString(IntegerQueue Q)
{
	if(Q == NULL)
	{
		fprintf(stderr, "IntegerQueue Error: IntegerQueueToString() called on NULL "\
		"IntegerQueue reference");
		exit(EXIT_FAILURE);
	}
	Node temp = Q->head;
	char* string;
	int digit_count = 0;
	int Q_length = Q->length;

	// make a f(x) that counts the digits in an integer = digit_count
	for(int i = 0; i < Q->length; i++)
	{
		int digit_test = 1;
		int int_to_be_counted = temp->value;
		if(int_to_be_counted != 0)
		{
			while (int_to_be_counted % digit_test != int_to_be_counted)
			{
				digit_test *= 10;
				digit_count++;
			}			
		}
		else if (int_to_be_counted == 0) digit_count++;
		temp = temp->next;
	}
	freeNode(&temp);
	digit_count += Q_length;
	digit_count++;
	Node test = Q->head;

	// make a f(x) that allocates memory on the heap for the size of the int string
	string = calloc(digit_count, sizeof(char));
	assert(string!=NULL);

	for(int i = 0; i < Q_length; i++)
	{
		char convert[] = "";
	   	char space[] = " ";
		char* cvrt = convert; 
		sprintf(cvrt,"%d",test->value);
	 	strcat(string,convert);
	 	strcat(string,space);
	   	test = test->next;
	}
	string[digit_count-1] = '\0';
	free(test);
    return string;
}

// equals()
// Returns true (1) if Q and R are matching sequences of integers, false (0) 
// otherwise.
int equals(IntegerQueue Q, IntegerQueue R)
{
	if(Q == NULL || R == NULL)
	{
		fprintf(stderr, "IntegerQueue Error: equals() called on NULL "\
		"IntegerQueue reference");
		exit(EXIT_FAILURE);
	}	
	char* string1 = IntegerQueueToString(Q);
	char* string2 = IntegerQueueToString(R);
	int value = strcmp(string1, string2);
	free(string1);
	free(string2);
	if(value == 0) return 1;
	return 0;
}