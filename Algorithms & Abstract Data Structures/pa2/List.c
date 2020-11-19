/*********************************************************************************
* Name: 			Jimmy Franknedy
* CruzID:			jfrankne
* Course: 			CSE 101 Spring 2020
* File name: 		List.c
* File Description: Function code for List ADT (Doubly-Linked List)
					For organization purposes Head-Body-Tail
*********************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "List.h"

// Typedef-structs ------------------------------------------------------------
typedef struct NodeObj
{
	long data;					// int value holding the index of the array
	struct NodeObj* next;		// node to the right
	struct NodeObj* prev;		// node to the left
}NodeObj;

typedef struct ListObj
{
	Node cursor;				// "temp" Node in the list
	Node front;					// "head" Node in the list
	Node back;					// "tail" Node in the list 
	int length;				// length of the List
	int index; 				// the "index" of the cursor in the list
}ListObj;

// Constructors-Destructors ---------------------------------------------------

// Create a Node and allocating memory
Node newNode()
{
	Node N = malloc(sizeof(NodeObj));
	assert(N!=NULL);
	N->next = N->prev = NULL;
	return N;	
}

// Destroying a Node and deallocating memory
void freeNode(Node* pN)
{
	if( pN!=NULL && *pN!=NULL )
	{
		free(*pN);
		*pN = NULL;
   	}
}

// Creates and returns a new empty List.
List newList(void)
{	
	List L = malloc(sizeof(ListObj));
	assert(L!=NULL);
	L->cursor = L->front = L->back = NULL;
	L->length = 0;
	L->index = -1;
	return L;
}

// Frees all heap memory associated with *pL, and sets *pL to NULL.
void freeList(List* pL)
{
	if(pL != NULL && *pL != NULL)
	{	
		clear(*pL);
		free(*pL);
		*pL = NULL;
	}
}

// Access functions -----------------------------------------------------------

 // Returns the number of elements in L.
int length(List L)
{
	// Checking validity
	if(L == NULL)
	{
		fprintf(stderr, "Access function: calling length() on NULL List reference\n");
		exit(EXIT_FAILURE);			
	}

	// Returns the length of the list
	return L->length;
}

 // Returns index of cursor element if defined, -1 otherwise.
int index(List L)
{
	// Checking validity
	if(L == NULL)
	{
		fprintf(stderr, "Access function: calling index() on NULL List reference\n");
		exit(EXIT_FAILURE);			
	}

	// Return the index
	return L->index;
}

 // Returns front element of L. Pre: length()>0
long front(List L)
{
	// Checking validity
	if(L == NULL)
	{
		fprintf(stderr, "Access function: calling front() on NULL List reference\n");
		exit(EXIT_FAILURE);			
	}

	// Checking precondition
	if(L->length < 0)
	{
		fprintf(stderr, "Access function: calling front() on an empty List reference\n");
		exit(EXIT_FAILURE);			
	}

	// Return the data value held by the 'front' node
	return L->front->data;
}

// Returns back element of L. Pre: length()>0
long back(List L)
{
	// Checking validity
	if(L == NULL)
	{
		fprintf(stderr, "Access function: calling back() on NULL List reference\n");
		exit(EXIT_FAILURE);			
	}

	// Checking precondition
	if(L->length < 0)
	{
		fprintf(stderr, "Access function: calling back() on an empty List reference\n");
		exit(EXIT_FAILURE);			
	}

	// Return the data value held by the 'back' node
	return L->back->data;
}

 // Returns cursor element of L. Pre: length()>0, index()>=0
long get(List L)
{
	// Checking validity
	if(L == NULL)
	{
		fprintf(stderr, "Access function: calling get() on NULL List reference\n");
		exit(EXIT_FAILURE);			
	}

	// Checking precondition
	if(L->length <= 0)
	{
		fprintf(stderr, "Access function: calling get() on an empty List reference\n");
		exit(EXIT_FAILURE);			
	}

	// Checking precondition
	if(index(L) < 0)
	{
		fprintf(stderr, "Access function: calling get() on an NULL index() reference\n");
		exit(EXIT_FAILURE);			
	}

	// Return the data value held by the 'cursor' node
	return L->cursor->data;
}

 // Returns true (1) iff Lists A and B are in same state, and returns false (0) otherwise.
int equalz(List A, List B)
{
	// Checking validity
	if(A == NULL || B == NULL)
	{
		fprintf(stderr, "Access function: calling equals() on NULL List reference\n");
		exit(EXIT_FAILURE);			
	}
	// Create a variable to show if a pair of nodes have a matching value
	int matching = 1;

	// Create a temp node starting at the "front" of the List
	moveFront(A);
	moveFront(B);

	// Loop through both Lists
	while ((index(A) != -1) && (index(B) != -1) && (matching == 1))
	{
		// If the 2 values from the temp nodes match continue!
		if((get(A)) == (get(B)))
		{
			// Increment to the enext nodes for further checking 
			moveNext(A);
			moveNext(B);
		}

		// If the 2 values from the temp nodes do not match, break the loop!
		else
		{
			// Set the "matching" variable to show inconsistency
			matching = 0;
			// printf("mismatch found!\n");
			// printf("A: %ld @ [%d]\n",get(A),index(A));
			// printf("B: %ld @ [%d]\n",get(B),index(B));
			// printf("HERE!\n");
			// exit(EXIT_FAILURE);
			break;
		}
	}

	// Conditions for returning 1 or 0
	if(matching)
	{
		// List 'A' and 'B' match
		return 1;
	}
	// List 'A' and 'B' do not match
	return 0;
}
 // Overwrites the cursor element with x. Pre: length() > 0, index() >= 0
 void set(List L, long x)
 {
 	// Checking validity
	if(L == NULL)
	{
		fprintf(stderr, "Manipulation procedure: calling set() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}

	// Checking validity
	if(length(L) <= 0)
	{
		fprintf(stderr, "Manipulation procedure: calling set() on empty List reference\n");
		exit(EXIT_FAILURE);
	}

	// Checking validity
	if(index(L) < 0)
	{
		fprintf(stderr, "Manipulation procedure: calling set() on invalid index reference\n");
		exit(EXIT_FAILURE);
	}

	// Overwrite the cursor's value
	L->cursor->data = x;	
 }

// Manipulation procedures ----------------------------------------------------
void clear(List L)
{
	// Checking validity
	if(L == NULL)
	{
		fprintf(stderr, "Manipulation procedure: calling clear() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}

	// Passing preconditions-----
	while(L->length != 0)
	{
		// Condition such that the length of the list is 1
		if(L->length == 1)
		{
			// Reset the 'cursor' and it's index value!
			L->cursor = NULL;
			L->index = -1;

			// Reset the 'back' node
			L->back = NULL;

			// Reset the 'front' node
			if(L->front != NULL)
			{
				freeNode(&L->front);
				L->front = NULL;
			}
		}

		// Condition such that the length is greater than 1
		else
		{
			// Hold the "front" node as a temp
			Node temp = L->front;

			// Update the "front" to the next node
			L->front = L->front->next;

			// Free the "temp" node
			freeNode(&temp);

			// Set temp tp NULL
			temp = NULL;
		}

		// Decrement List Length
		L->length--;
	}
}

// If L is non-empty, sets cursor under the front element, otherwise does nothing.
void moveFront(List L)
{
	// Checking validity
	if(L == NULL)
	{
		fprintf(stderr, "Manipulation procedure: calling moveFront() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}

	// Passing pre-condition
	if(L->length > 0)
	{
		L->cursor = L->front;

		// Update the List 'index' value
		L->index = 0;	
	}
}

// If L is non-empty, sets cursor under the back element, otherwise does nothing.
void moveBack(List L)
{
	// Checking validity
	if(L == NULL)
	{
		fprintf(stderr, "Manipulation procedure: calling moveBack() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}

	// Passing pre-condition
	if(L->length > 0)
	{
		L->cursor = L->back;

		// Update the List 'index' value
		L->index = length(L)-1;
	}
}

// if cursor is defined and not at front, move cursor one step toward the front of L; 
// if cursor is defined and at front, cursor becomes undefined;
// if cursor is undefined do nothing;
void movePrev(List L)
{
	// Checking validity
	if(L == NULL)
	{
		fprintf(stderr, "Manipulation procedure: calling movePrev() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}

	// Checking condition
	if(L->cursor != NULL)
	{
		// Condition: 'cursor' is in the front
		if(L->cursor == L->front)
		{
			// Reset the cursor
			L->cursor = NULL;
			L->index = -1;
		}

		// Condition: 'cursor' is not in the front
		else 
		{
			// Move the cursor backwards and decrement it's index
			L->cursor = L->cursor->prev;
			L->index--;
		}
	}
}

// if cursor is defined and not at back, move cursor one step toward the back of L;
// if cursor is defined and at back, cursor becomes undefined; 
// if cursor is undefined do nothing;
void moveNext(List L)
{
	// Checking validity
	if(L == NULL)
	{
		fprintf(stderr, "Manipulation procedure: calling moveNext() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}

	// Checking condition
	if(L->cursor != NULL)
	{
		// Condition: 'cursor' is in the back
		if(L->cursor == L->back)
		{
			// Reset the cursor
			L->cursor = NULL;
			L->index = -1;
		}
		// Condition: 'cursor' is not in the back
		else 
		{
			// Move the cursor forwards and increment it's index
			L->cursor = L->cursor->next;
			L->index++;
		}		
	}
}

// Insert new element into L. If L is non-empty,
// insertion takes place before front element.
void prepend(List L, long data)
{
	// Checking validity
	if(L == NULL)
	{
		fprintf(stderr, "Manipulation procedure: calling prepend() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}

	// Passing precondtions-----

	// Empty List
	if(L->length == 0)
	{
		L->front = L->back = newNode();
		L->front->data = L->back->data = data;
		L->index = 0;
	}

	// Only 1 element in the current list (i.e front != NULL)
	else if(L->length == 1)
	{
		L->front = newNode();
		L->front->data = data;
		L->front->next = L->back;
		L->back->prev = L->front;
	}

	// Only 2 or more elements in the current list (i.e front != NULL && back != NULL)
	else 
	{
		Node new = newNode();
		new->data = data;
		new->next = L->front;
		L->front->prev = new;
		L->front = new;
	}

	// Increment length of List
	L->length++;

	// Check to see if the index is defined; if so, increment
	if(L->index!= -1)
	{
		// printf("(4)\n");
		L->index++;
	}
}

// Insert new element into L. If L is non-empty,
// insertion takes place after back element.
void append(List L, long data)
{	// Passing precondtions-----

	// Empty List 
	if(L->length == 0)
	{
		L->front = L->back = newNode();
		L->front->data = L->back->data = data;
	}

	// Only 1 element in the current list (i.e front != NULL)
	else if(L->length == 1)
	{
		L->back = newNode();
		L->back->data = data;
		L->back->prev = L->front;
		L->front->next = L->back;
	}

	// Only 2 or more elements in the current list (i.e front != NULL && back != NULL)
	else 
	{
		Node new = newNode();
		new->data = data;
		new->prev = L->back;
		L->back->next = new;
		L->back = new;
	}

	// Increment length of List
	L->length++;
}

// Insert new element before cursor.
// Pre: length()>0, index()>=0
void insertBefore(List L, long data)
{
	// Checking precondition
	if(L == NULL)
	{
		fprintf(stderr, "Manipulation procedure: calling insertBefore() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}

	// Checking precondition
	if(L->length <= 0)
	{
		fprintf(stderr, "Manipulation procedure: calling insertBefore() on an empty List reference\n");
		exit(EXIT_FAILURE);
	}

	// Checking precondition
	if(L->index < 0)
	{
		fprintf(stderr, "Manipulation procedure: calling insertBefore() on an invalid index() reference\n");
		exit(EXIT_FAILURE);
	}

	// Passing preconditions-----

	// Condition if the cursor is at the "front"
	if(L->cursor == L->front)
	{
		prepend(L,data);
	}

	// Condition if the cursor is at the "back" or somewhere in the middle
	else
	{
		// Link node in between 'cursor->prev' and 'cursor' && increment index
		Node new = newNode();
		new->data = data;
		new->next = L->cursor;
		new->prev = L->cursor->prev;
		L->cursor->prev->next = new;
		L->cursor->prev = new;
		L->index++;
		L->length++;	
	}
}

// Insert new element after cursor.
// Pre: length()>0, index()>=0
void insertAfter(List L, long data)
{
	// Checking precondition
	if(L == NULL)
	{
		fprintf(stderr, "Manipulation procedure: calling insertAfter() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}

	// Checking precondition
	if(L->length <= 0)
	{
		fprintf(stderr, "Manipulation procedure: calling insertAfter() on an empty List reference\n");
		exit(EXIT_FAILURE);
	}

	// Checking precondition
	if(L->index < 0)
	{
		fprintf(stderr, "Manipulation procedure: calling insertAfter() on an invalid index() reference\n");
		exit(EXIT_FAILURE);
	}

	// Passing preconditions-----

	// Condition if the cursor is at the "back"
	if(L->cursor == L->back)
	{
		append(L,data);
	}

	// Condition if the cursor at the "front" or somewhere in the middle
	else
	{
		// Link node in between 'cursor' and 'cursor->next'
		Node new = newNode();
		new->data = data;
		new->next = L->cursor->next;
		new->prev = L->cursor;
		L->cursor->next->prev = new;
		L->cursor->next = new;
		L->length++;
	}
}

// Delete the front element. Pre: length()>0
void deleteFront(List L)
{
	// Checking validity
	if(L == NULL)
	{
		fprintf(stderr, "Manipulation procedure: calling deleteFront() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}

	// Checking precondition
	if(L->length <= 0)
	{
		fprintf(stderr, "Manipulation procedure: calling deleteFront() on empty List reference\n");
		exit(EXIT_FAILURE);		
	}

	// Passing preconditions-----

	// Special Condition such that 'cursor' > 'front'
	if(L->cursor == L->front)
	{
		// printf("(df_1)\n");
		L->cursor = NULL;
		L->index = -1;
	}

	if(L->length == 1)
	{
		// printf("(df_2)\n");
		// Deleting the single Node
		freeNode(&L->front);
		L->front = L->back = NULL;
	}
	else
	{
		// printf("(df_3)\n");
		// delete 'front' node && update 'front->next->prev'
		L->front->next->prev = NULL;
		Node temp = L->front;
		L->front = L->front->next;
		freeNode(&temp);
		temp = NULL;
	}

	// If 'index' is defined, update index
	if(L->index != -1)
	{
		L->index--;
	}

	// Decrementing the length of the List
	// printf("Decrementing Length!\n");
	L->length--;
}

// Delete the back element. Pre: length()>0
void deleteBack(List L)
{
	// Checking validity
	if(L == NULL)
	{
		fprintf(stderr, "Manipulation procedure: calling deleteBack() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	
	// Checking precondition
	if(L->length <= 0)
	{
		fprintf(stderr, "Manipulation procedure: calling deleteBack() on empty List reference\n");
		exit(EXIT_FAILURE);		
	}	

	// Passing preconditions-----

	// Special Condition such that 'cursor' > 'back'
	if(L->cursor == L->back)
	{
		// printf("(db_1)\n");
		L->cursor = NULL;
		L->index = -1;
	}

	if(L->length == 1)
	{
		// printf("(db_2)\n");
		// Deleting the single Node
		freeNode(&L->front);
		L->front = L->back = NULL;
	}
	else
	{
		// printf("(db_3)\n");
		// delete 'back' node && update 'back->prev-next'
		L->back->prev->next = NULL;
		Node temp = L->back;
		L->back = L->back->prev;
		freeNode(&temp);
		temp = NULL;
	}

	// Decrementing the length of the List
	// printf("Decrementing Length!\n");
	L->length--;
}

// Delete highlighted element by the cursor, making cursor undefined.
// Pre: length()>0, index()>=0
void delete(List L)
{
	// Checking validity
	if(L == NULL)
	{
		fprintf(stderr, "Manipulation procedure: calling delete() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}

	// Checking precondition
	if(L->length <= 0)
	{
		fprintf(stderr, "Manipulation procedure: calling delete() on empty List reference\n");
		exit(EXIT_FAILURE);		
	}

	// Checking precondition
	if(index(L) < 0)
	{
		fprintf(stderr, "Manipulation procedure: calling delete() on invalid index() reference\n");
		exit(EXIT_FAILURE);			
	}

	// Passing preconditions-----

	// Condition if the cursor is pointing at the front of the list
	if (L->cursor == L->front)
	{
		// printf("(d_1)\n");	
		deleteFront(L);
	}
	else if(L->cursor == L->back)
	{
		// printf("(d_2)\n");
		deleteBack(L);
	}

	// L->cursor == 'middle'
	else
	{
		// printf("(d_3)\n");
		L->cursor->prev->next = L->cursor->next;
		L->cursor->next->prev = L->cursor->prev;
		freeNode(&L->cursor);
		// printf("Decrementing Length!\n");
		L->length--;
	}
	L->cursor = NULL;
	L->index = -1;
}

// Other operations -----------------------------------------------------------

// Prints to the file pointed to by out, a
// string representation of L consisting
// of a space separated sequence of integers,
// with front on left.
void printList(FILE* out, List L)
{
	// Checking validity
	if(L == NULL)
	{
		fprintf(stderr, "Other operation: calling printList() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}

	// Make sure that the List is not empty
	if(L->length >= 1)
	{
		// Start with the "front" of the List
		Node temp = L->front;

		// Loop through the List and create the string
		while(temp != NULL)
		{
			// write to the file: including the 'idx' value and 'space'
			fprintf(out, "%ld ",temp->data);

		   	// move to the next Node
		   	temp = temp->next;
		}		
	}
} 

// Returns a new List representing the same integer
// sequence as L. The cursor in the new list is undefined,
// regardless of the state of the cursor in L. The state
// of L is unchanged.
List copyList(List L)
{
	// Checking validity
	if(L == NULL)
	{
		fprintf(stderr, "Other operation: calling copyList() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}

	// Allocate memory for the new list
	List nL = newList();

	// Set pre-determined variables
	nL->cursor = NULL;
	nL->index = -1;

	// create a temp node pointing to the "front" at the provided at the list
	Node temp = L->front;

	while(temp != NULL)
	{
		// create a newNode
		Node new = newNode();

		// insert 'idx' value from "temp" (method is to insert AFTER the "back" and update the "back")
		new->data = temp->data;

		// Condition such that "copied list length" is 0
		if(nL->length == 0)
		{
			// set "front" and "back" to point at the new node
			nL->front = nL->back = new;
		}

		// Condition such that "copied list length" is 1
		else if (nL->length == 1)
		{
			// linking the "front" to the back "back"
			nL->front->next = new;
			new->prev = nL->front;

			// set "back" to point at the new node
			nL->back = new;
		}
		else 
		{
			// link the "new" to the "back"
			nL->back->next = new;
			new->prev = nL->back;

			// set "back" to point at the new node
			nL->back = new;		
		}

		// move onward to the next node in the given List
		temp = temp->next;

		// increment the length of new list
		nL->length++;
	}

	// return the copied list
	return nL;
}

// Returns a new List which is the concatenation of
// A and B. The cursor in the new List is undefined,
// regardless of the states of the cursors in A and B.
// The states of A and B are unchanged.
List concatList(List A, List B)
{
	// Checking validity
	if(A == NULL || B == NULL)
	{
		fprintf(stderr, "Other operation: calling concatList() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}

	// Create a new list
	List concatnated = newList();
	concatnated->index = -1;
	concatnated->cursor = NULL;

	// Loop through A and copy it's values into 'new'
	moveFront(A);
	while(index(A) != -1)
	{
		append(concatnated,get(A));
		moveNext(A);
	}

	// Loop through B and copy it's values into 'new'
	moveFront(B);
	while(index(B) != -1)
	{
		append(concatnated, get(B));
		moveNext(B);
	}

	// Return the concatnated list
	return concatnated;
}