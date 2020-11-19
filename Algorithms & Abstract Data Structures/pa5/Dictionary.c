// Name:		 Jimmy Franknedy
// CruzID:    	 jfrankne
// Class: 		 CSE-015
// Date:		 12/5/2019
// Project Name: Dictionary.c
// Project Desc: The goal of this project is to recreate the Dictionary ADT 
//				 from pa3, but now based on a hash table instead of a linked list.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "Dictionary.h"

// Exported type --------------------------------------------------------------

// the hash value
const int tableSize = 101;

// Additional Helper Functions (Prototypes)------------------------------------
unsigned int rotate_left(unsigned int value, int shift);
unsigned int pre_hash(char* input);
int hash(char* key);
void makeErase(Dictionary D);

// Additional Helper Functions (Definition)------------------------------------
// rotate_left()
// rotate the bits in an unsigned int
unsigned int rotate_left(unsigned int value, int shift) 
{
	int sizeInBits = 8*sizeof(unsigned int);
	shift = shift & (sizeInBits - 1);
	if (shift == 0) return value;
 	return (value << shift) | (value >> (sizeInBits - shift));
}

// pre_hash()
// turn a string into an unsigned int
unsigned int pre_hash(char* input) 
{
	unsigned int result = 0xBAE86554;
	while (*input) 
	{
		result ^= *input++;
 		result = rotate_left(result, 5);
 	}
 	return result;
}
// hash()
// turns a string into an int in the range 0 to tableSize-1
int hash(char* key) return pre_hash(key)%tableSize;

//---------------------------------------------------------------------
// NodeObj 
typedef struct NodeObj
{
	// pointer to the pair value of "key"    - UNIQUE
	char* key;

	// pointer to the pair value of "value"  - COMMON
	char* value;

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
Node newNode(char* k, char* v)
{
	// allocate space on the heap for the size of NodeObj
	Node N = malloc(sizeof(NodeObj));

	// check to see if allocation was valid
	assert(N!=NULL);

	// set the custom "key" value to the "key" value in the Node
	N->key = k;

	// set the custom "value" value to the "value" value in the Node
	N->value = v;

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
// NodeObj 
//---------------------------------------------------------------------

//---------------------------------------------------------------------
// PageObj
typedef struct PageObj
{
	// pointer to the first Node in list
	Node head;

	// pointer to the last Node in list
	Node tail;

	// counter for number of items in the Dictionary 	// not sure if you're gonna need	
	int numPairs;										// the "number of pages"

} PageObj;

// create an instance of Page
typedef struct PageObj* Page;

// newPage()
// Constructor for the Page ADT (i.e LL).
Page newPage()
{
	// allocate memory on the heap for the size of a NodeObj
	Page P = malloc(sizeof(PageObj));

	// check to see if the memory allocated correctly
	assert(P != NULL);

	// initialize the head Node to point to nothing (i.e NULL)
	P->head = NULL;

	// initialize the tail Node to point to nothing (ie. NULL)
	P->tail = NULL;

	// set the number of elements (or pages) (i.e numPairs = 0)
	P->numPairs = 0;

	// return the Dictionary 'D'
	return P;
}

// deleteAllPages()
// deletes all Nodes in the Page P
void deleteAllPages(Node N);

// Pre: make sure you are starting at the head!
void deleteAllPages(Node N)
{
	// if you haven't reach the tail yet
	if(N != NULL)
	{
		// recurse until you find the tail
		deleteAllPages(N->next);

		// recurse back and free the memory on the heap
		freeNode(&N);
	}
}

// makePagesEmpty()
// Reset P to the empty state, the empty set of pairs.
void makePagesEmpty(Page P)
{
	// check to see if the Dictionary is not NULL
	if(P == NULL)
	{
		fprintf(stderr, "Dictionary Error: calling makeEmpty() on NULL Dictionary reference\n");
		exit(EXIT_FAILURE);
	}

	// make sure you are passing in the HEAD of the linked list!
	deleteAllPages(P->head);

	// set the head & tail Node to point to nothing (i.e NULL)
	P->head = NULL;
	P->tail = NULL;

	// reset the number of pairs in the Dictionary
	P->numPairs = 0;
}

// freePages()
// Destructor for the Page ADT.
void freePages(Page pP)
{
	// check if the value of pD and *pD are not NULL
	if(pP != NULL)
	{
		// clear the Dictionary
		makePagesEmpty(pP);

		// free the memory pointed to by pD
		free(pP);

		// set that pointer to point to NULL
		pP = NULL;
	}
}


// PageObj
//----------------------------------------------------------------------

//---------------------------------------------------------------------
// DictionaryObj
typedef struct DictionaryObj
{
	// create a "page" variable that points to a "page" array
	Page* P;

	// hold the number of elements in the Dictionary Array
	int usedPages;

	// hold the max pages:
	int maxPages;

} DictionaryObj;

// create an instance of Dictionary
typedef struct DictionaryObj* Dictionary;

// newDictionary()
// Constructor for the Dictionary ADT.
Dictionary newDictionary()
{
	// create the "page" array of pages
	Dictionary D = malloc(sizeof(DictionaryObj));

	// check if they are null
	assert(D != NULL);

	// set the number of pages in the Dictionary to 0
	D->usedPages = 0;

	// hold the max pages?
	D->maxPages = tableSize;

	// create the set the "page" pointer to an array of "page(s)"
	D->P = calloc(tableSize,sizeof(PageObj));

	for(int i = 0; i<tableSize; i++) D->P[i] = newPage();
	return D;
}

// freeDictionary()
// Destructor for the Dictionary ADT.
void freeDictionary(Dictionary* pD)
{
	if(pD != NULL && *pD != NULL)
	{
		makeErase(*pD);
		free(*pD);
		*pD = NULL;
	}
}

// Node findKey 
// Returns the Node containing the desired "key" in Dictionary D or NULL if Node does not exist.

// recall the return values of strcmp(string1,string2), which gets its difference by subtracting 
// the ASCII values of string1 by string2 (i.e string1 - string2)
//
// >0: if string1 > string2
//  0: if they are the same
// <0: if string1 < string2

Node findKey(Dictionary D, char* key);

Node findKey(Dictionary D, char* key)
{
	// check to see if the Dictionary is not NULL
	if(D == NULL)
	{
		fprintf(stderr, "Node findKey: calling findKey() on NULL Dictionary reference\n");
		exit(EXIT_FAILURE);
	}

	//for(int i = 0; i < D->maxPages; i++)
	//{
		if(D->P[hash(key)]->head != NULL)
		{
			// create a temp Node!
			Node temp = D->P[hash(key)]->head;
			
			// continue through the linked list until you hit the end
			// for(int i = 0; i < D->P[i]->numPairs; i++)
			while(temp != NULL)
			{
				// variable holding string compare result of the temp's key and the inputted key
				// int StringCompareResult = strcmp(temp->key,key);

				// if the strings match
				if(!(strcmp(temp->key,key)))
				{
					// return the node
					return temp;
				}
				// if the strings don't match, continue to through the linked list and increment to the next Node
				temp = temp->next;
			}
			// freeNode(&temp);
		}
	//}
	// return the Node
	return NULL;	
}

// int countChars
int countChars(Dictionary D);
int countChars(Dictionary D)
{
	int count = 0;
	for(int i = 0; i<D->maxPages; i++)
	{
		if(D->P[i]->head != NULL)
		{
			Node temp = D->P[i]->head;
			while(temp != NULL)
			{
				count += strlen(temp->key)+strlen(temp->value)+2;
				temp = temp->next;
			}
			freeNode(&temp);
		}
	}
	return count;
}
// DictionaryObj
//---------------------------------------------------------------------

// size()
// Return the number of (key, value) pairs in Dictionary D.
int size(Dictionary D)
{
	// check to see if the Dictionary is not NULL
	if(D == NULL)
	{
		fprintf(stderr, "Dictionary Error: calling size() on NULL Dictionary reference\n");
		exit(EXIT_FAILURE);
	}
	return D->usedPages;
}

// lookup()
// If D contains a pair whose key matches argument k, then return the 
// corresponding value, otherwise return NULL.
char* lookup(Dictionary D, char* k)
{
	// check to see if the Dictionary is not NULL
	if(D == NULL)
	{
		fprintf(stderr, "Dictionary Error: calling lookup() on NULL Dictionary reference\n");
		exit(EXIT_FAILURE);
	}

	// generate the key's hash value!
	int hashed = hash(k);

	// check if Dicationary[hashed] is not NULL (i.e there is a page with the key's value!)
	if(D->P[hashed]->head != NULL)
	{
		// create an instance of a "temp" node
		Node temp = D->P[hashed]->head;

		// loop through the "page's" size
		for(int i = 0; i < D->P[hashed]->numPairs; i++)
		{
			// if the page's key matches the given key
			if(!(strcmp(temp->key,k))) return temp-> value;
			else temp = temp->next;
		}
	}
	return NULL;
}	


// insert()
// Insert the pair (k,v) into D.
// Pre: lookup(D, k)==NULL (D does not contain a pair whose first member is k.)
void insert(Dictionary D, char* k, char* v)
{
	// check to see if the Dictionary is not NULL
	if(D == NULL)
	{
		fprintf(stderr, "Dictionary Error: calling insert() on NULL Dictionary reference\n");
		exit(EXIT_FAILURE);
	}

	int hashed = hash(k);
	if(D->P[hashed]-> head == NULL && D->P[hashed]->tail == NULL && D->P[hashed]->numPairs == 0)
	{
		D->P[hashed]->head = newNode(k,v);
	}
	else if( D->P[hashed]-> head != NULL && D->P[hashed]->tail == NULL && D->P[hashed]->numPairs == 1)
	{
		D->P[hashed]->tail = D->P[hashed]->head;
		D->P[hashed]->head = newNode(k,v);
		D->P[hashed]->head->next = D->P[hashed]->tail;
		D->P[hashed]->tail->prev = D->P[hashed]->head;
	}
	else if(D->P[hashed]->head != NULL && D->P[hashed]->tail != NULL && D->P[hashed]->numPairs > 1)
	{
		Node new = newNode(k,v);
		D->P[hashed]->head->prev = new;
		new->next = D->P[hashed]->head;
		D->P[hashed]->head = new;
	}
	D->P[hashed]->numPairs++;
	D->usedPages++;
	
}

// delete()
// Remove pair whose first member is the argument k from D.
// Pre: lookup(D,k)!=NULL (D contains a pair whose first member is k.)
void delete(Dictionary D, char* k)
{
	// check to see if the Dictionary is not NULL
	if(D == NULL)
	{
		fprintf(stderr, "Dictionary Error: calling delete() on NULL Dictionary reference\n");
		exit(EXIT_FAILURE);
	}

	if(findKey(D,k) != NULL)
	{
		Node temp = findKey(D,k);

		// if temp->next == NULL && temp->prev == NULL (i.e empty D or only head)
		if(temp->next == NULL && temp->prev == NULL && D->P[hash(k)]->numPairs == 1)
		{
			makePagesEmpty(D->P[hash(k)]);
			D->P[hash(k)]->numPairs++;
		}
		// if temp->next == NULL (i.e removing the tail)
		else if(temp->next == NULL && temp->prev != NULL)
		{
			D->P[hash(k)]->tail = temp->prev;
			freeNode(&temp->next);
			temp->next = NULL;
			D->P[hash(k)]->tail->next = NULL;

			if(D->P[hash(k)]->numPairs == 2) D->P[hash(k)]->tail = NULL;
			freeNode(&temp);
		}
		// if temp->prev == NULL (i.e removing the head)
		else if(temp->prev == NULL && temp->next != NULL)
		{
			D->P[hash(k)]->head = temp->next;
			freeNode(&temp->prev);
			temp->prev = NULL;
			D->P[hash(k)]->head->prev = NULL;
			if(D->P[hash(k)]->numPairs == 2)
			{
				D->P[hash(k)]->tail = NULL;
				D->P[hash(k)]->head->next = NULL;
			}
			freeNode(&temp);
		}
		// if temp->prev != NULL && temp->next != NULL (i.e removing middle node)
		else if(temp->next != NULL && temp->prev != NULL)
		{
			temp->next->prev = temp->prev;
			temp->prev->next = temp->next;
			freeNode(&temp);
		}
		D->P[hash(k)]->numPairs--;
		D->usedPages--;
	}
}

// makeEmpty()
// Reset D to the empty state, the empty set of pairs.
void makeEmpty(Dictionary D)
{
	// check to see if the Dictionary is not NULL
	if(D == NULL)
	{
		fprintf(stderr, "Dictionary Error: calling makeEmpty() on NULL Dictionary reference\n");
		exit(EXIT_FAILURE);
	}
	for(int i = 0; i < D->maxPages; i++)
	{
		freePages(D->P[i]);
	}
	free(D->P);
	D->P = calloc(tableSize,sizeof(PageObj));
	for(int i = 0; i<tableSize; i++)
	{
		D->P[i] = newPage();
	}
	D->usedPages = 0;
}

// makeEmpty()
// Reset D to the empty state, the empty set of pairs.
void makeErase(Dictionary D)
{
	// check to see if the Dictionary is not NULL
	if(D == NULL)
	{
		fprintf(stderr, "Dictionary Error: calling makeEmpty() on NULL Dictionary reference\n");
		exit(EXIT_FAILURE);
	}
	for(int i = 0; i < D->maxPages; i++)
	{
		freePages(D->P[i]);
	}
	free(D->P);
	D->usedPages = 0;
}


// Other Operations -----------------------------------------------------------

// DictionaryToString()
// Determines a text representation of the current state of Dictionary D. Each 
// (key, value) pair is represented as the chars in key, followed by a space,
// followed by the chars in value, followed by a newline '\n' char. The pairs 
// occur in alphabetical order by key. The function returns a pointer to a char 
// array, allocated from heap memory, containing the text representation 
// described above, followed by a terminating null '\0' char. It is the 
// responsibility of the calling function to free this memory.
char* DictionaryToString(Dictionary D)
{
	// check to see if the Dictionary is not NULL
	if(D == NULL)
	{
		fprintf(stderr, "Dictionary Error: calling DictionaryToString() on NULL Dictionary reference\n");
		exit(EXIT_FAILURE);
	}
	char* string;
   	int length = countChars(D);
   	string = calloc(length+1, sizeof(char));
   	for(int i = 0; i< D->maxPages; i++)
   	{
   		if(D->P[i]->head != NULL)
   		{
   			Node temp = D->P[i]->head;
   			char space[] = " ";
		   	char* sp = space;
		   	char newLine[] = "\n";
		   	char* nL = newLine;
   			while(temp != NULL)
   			{
		   		strcat(string,temp->key);
		   		strcat(string,sp);
		   		strcat(string,temp->value);
		   		strcat(string,nL);
		   		temp = temp->next;
   			}
   			freeNode(&temp);
   		}
   	}
   	string[length] = '\0';
    return string;
}