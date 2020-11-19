//-----------------------------------------------------------------------------
// Dictionary.h
// Header file for the Dictionary ADT
//-----------------------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>

#ifndef _DICTIONARY_H_INCLUDE_
#define _DICTIONARY_H_INCLUDE_


// Exported type --------------------------------------------------------------

// Dictionary
typedef struct DictionaryObj* Dictionary;

// Constructors-Destructors ---------------------------------------------------

// newDictionary()
// Constructor for the Dictionary ADT.
Dictionary newDictionary();

// freeDictionary()
// Destructor for the Dictionary ADT.
void freeDictionary(Dictionary* pD);


// ADT operations -------------------------------------------------------------

// size()
// Return the number of (key, value) pairs in Dictionary D.
int size(Dictionary D);

// lookup()
// If D contains a pair whose key matches argument k, then return the 
// corresponding value, otherwise return NULL.
char* lookup(Dictionary D, char* k);

// insert()
// Insert the pair (k,v) into D.
// Pre: lookup(D, k)==NULL (D does not contain a pair whose first member is k.)
void insert(Dictionary D, char* k, char* v);

// delete()
// Remove pair whose first member is the argument k from D.
// Pre: lookup(D,k)!=NULL (D contains a pair whose first member is k.)
void delete(Dictionary D, char* k);

// makeEmpty()
// Reset D to the empty state, the empty set of pairs.
void makeEmpty(Dictionary D);


// Other Operations -----------------------------------------------------------

// DictionaryToString()
// Determines a text representation of the current state of Dictionary D. Each 
// (key, value) pair is represented as the chars in key, followed by a space,
// followed by the chars in value, followed by a newline '\n' char. The pairs 
// occur in alphabetical order by key. The function returns a pointer to a char 
// array, allocated from heap memory, containing the text representation 
// described above, followed by a terminating null '\0' char. It is the 
// responsibility of the calling function to free this memory.
char* DictionaryToString(Dictionary D);


#endif











