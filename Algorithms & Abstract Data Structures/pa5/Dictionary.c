/*********************************************************************************
* Name: 			Jimmy Franknedy
* CruzID:			jfrankne
* Course: 			CSE 101 Spring 2020
* File name: 		Dictionary.c
* File Description: Dictionary Function Code
*********************************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "Dictionary.h"

// Exported type --------------------------------------------------------------
typedef struct NodeObj* Node;

typedef struct NodeObj
{
	KEY_TYPE key;
	VAL_TYPE value;
	struct NodeObj* right;
	struct NodeObj* left;
	struct NodeObj* parent;
}NodeObj;

void freeNode(Node* pN);
void freeNode(Node* pN)
{
	if( pN!=NULL && *pN!=NULL )
	{
		free(*pN);
		*pN = NULL;
   	}
}


Node newNode(KEY_TYPE k, VAL_TYPE v)
{
	Node N = malloc(sizeof(NodeObj));
	assert(N!=NULL);
	N->key = k;
	N->value = v;
	N->right = N->left = N->parent = NULL;
	return N;
}

typedef struct DictionaryObj
{
	Node root;
	Node max;
	Node min;
	Node cursor;
	int size;
	int uniqueKeys;
}DictionaryObj;

// Helper Function ------------------------------------------------------------

void printKeysInOrderHelper (FILE* out, Node N);
void printKeysInOrderHelper (FILE* out, Node N)
{
	if(N != NULL )
	{
		printKeysInOrderHelper(out,N->left);
		fprintf(stdout,KEY_FORMAT,N->key);
		fprintf(out,KEY_FORMAT,N->key);
		printKeysInOrderHelper(out,N->right);
	}
}

void printKeysInOrder (FILE* out, Dictionary D)
{
	if(D == NULL)
	{
		fprintf(stderr, "Helper function: calling printKeysInOrder() on NULL List reference\n");
		exit(EXIT_FAILURE);			
	}
	printKeysInOrderHelper(out,D->root);
}



void inOrderTreeWalk (Node N);
void inOrderTreeWalk (Node N)
{
	if(N != NULL)
	{
		inOrderTreeWalk(N->left);
		fprintf(stdout,KEY_FORMAT,N->key);
		fprintf(stdout," ");
		fprintf(stdout,VAL_FORMAT,N->value);
		fprintf(stdout,"\n");
		inOrderTreeWalk(N->right);
	}
}

Node search (Dictionary D, KEY_TYPE k);
Node search (Dictionary D, KEY_TYPE k)
{
	if(lookup(D,k) != VAL_UNDEF)
	{
		Node x = D->root;
		int match = 0;
		while(match == 0)
		{
			if(KEY_CMP(k,x->key) == 0) match = 1;
			else if(KEY_CMP(k,x->key) < 1) x = x->left;
			else x = x->right;
		}
		return x;
	}
	return NULL;
}

Node TreeMinimum (Node N);
Node TreeMinimum (Node N)
{
	if(N == NULL)
	{
		fprintf(stderr, "Helper function: calling TreeMinimum() on NULL List reference\n");
		exit(EXIT_FAILURE);			
	}
	while(N->left != NULL) N = N->left;
	return N;
}

Node TreeMaximum (Node N);
Node TreeMaximum (Node N)
{
	if(N == NULL)
	{
		fprintf(stderr, "Helper function: calling TreeMaximum() on NULL List reference\n");
		exit(EXIT_FAILURE);			
	}
	while(N->right != NULL) N = N->right;
	return N;
}

Node TreeSuccessor (Node N);
Node TreeSuccessor (Node N)
{
	if(N == NULL)
	{
		fprintf(stderr, "Helper function: calling TreeSuccessor() on NULL List reference\n");
		exit(EXIT_FAILURE);			
	}
	if(N->right != NULL) return (TreeMinimum(N->right));
	Node Y = N->parent;
	while(Y != NULL && Y->right != NULL && (KEY_CMP(N->key,Y->right->key) == 0))
	{
		N = Y;
		Y = Y->parent;
	}
	return Y;
}

Node TreePredecessor (Node N);
Node TreePredecessor (Node N)
{
	if(N == NULL)
	{
		fprintf(stderr, "Helper function: calling TreePredecessor() on NULL List reference\n");
		exit(EXIT_FAILURE);			
	}
	if(N->left != NULL) return (TreeMaximum(N->left));
	Node Y = N->parent;
	while(Y != NULL && Y->left != NULL && (KEY_CMP(N->key,Y->left->key) == 0))
	{
		N = Y;
		Y = Y->parent;
	}
	return Y;
}

void checkKey (Node N);
void checkKey (Node N)
{
	if(N == NULL)
	{
		fprintf(stderr, "Helper function: calling checkKey() on NULL List reference\n");
		exit(EXIT_FAILURE);			
	}
	fprintf(stdout,"key: %s\n",N->key);
}

void checkVal (Node N);
void checkVal (Node N)
{
	if(N == NULL)
	{
		fprintf(stderr, "Helper function: calling checkVal() on NULL List reference\n");
		exit(EXIT_FAILURE);			
	}
	fprintf(stdout,"val: %d\n",N->value);
}

void Transplant (Dictionary D, Node U, Node V);
void Transplant (Dictionary D, Node U, Node V)
{
	if(D == NULL)
	{
		fprintf(stderr, "Helper function: calling Transplant() on NULL List reference\n");
		exit(EXIT_FAILURE);			
	}
	if(U == NULL)
	{
		fprintf(stderr, "Helper function: calling Transplant() on NULL U reference\n");
		exit(EXIT_FAILURE);			
	}
	if(U->parent == NULL) D->root = V;
	else if (U == U->parent->left) U->parent->left = V;
	else U->parent->right = V;
	if(V != NULL) V->parent = U->parent;
}


// Constructors-Destructors ---------------------------------------------------

// newDictionary()
// Creates a new empty Dictionary. If unique==false (0), then the Dictionary 
// will accept duplicate keys, i.e. distinct pairs with identical keys. If 
// unique==true (1 or any non-zero value), then duplicate keys will not be 
// accepted. In this case, the operation insert(D, k) will enforce the 
// precondition: lookup(D, k)==VAL_UNDEF
Dictionary newDictionary(int unique)
{
	Dictionary D = malloc(sizeof(DictionaryObj));
	assert(D != NULL);
	D->root = D->min = D->max = D->cursor = NULL;
	D->size = 0;
	D->uniqueKeys = unique;
	return D;
}

// freeDictionary()
// Frees heap memory associated with *pD, sets *pD to NULL.
void freeDictionary(Dictionary* pD)
{
	if(pD != NULL && *pD != NULL)
	{
		makeEmpty(*pD);
		free(*pD);
		*pD = NULL;
	}
}


// Access functions -----------------------------------------------------------

// size()
// Returns the number of (key, value) pairs in Dictionary D.
int size(Dictionary D)
{
	if(D == NULL)
	{
		fprintf(stderr, "Access function: calling size() on NULL List reference\n");
		exit(EXIT_FAILURE);			
	}
	return D->size;
}

// getUnique()
// Returns true (1) if D requires that all pairs have unique keys. Returns
// false (0) if D accepts distinct pairs with identical keys.
int getUnique(Dictionary D)
{
	if(D == NULL)
	{
		fprintf(stderr, "Access function: calling getUnique() on NULL List reference\n");
		exit(EXIT_FAILURE);			
	}
	return D->uniqueKeys;
}

// lookup()
// If Dictionary D contains a (key, value) pair whose key matches k (i.e. if
// KEY_CMP(key, k)==0), then returns value. If D contains no such pair, then
// returns VAL_UNDEF.
VAL_TYPE lookup(Dictionary D, KEY_TYPE k)
{
	if(D == NULL)
	{
		fprintf(stderr, "Access function: calling getUnique() on NULL List reference\n");
		exit(EXIT_FAILURE);			
	}
	Node x = D->root;
	int match = 0;
	if(D->size > 0)
	{
		while(x != NULL && match == 0)
		{
			if(KEY_CMP(k,x->key) == 0) match = 1;
			else if(KEY_CMP(k,x->key) < 0) x = x->left;
			else x = x->right;
		}
		if(match && (x != NULL)) return x->value;
	}
	return VAL_UNDEF;
}


// Manipulation procedures ----------------------------------------------------

// insert()
// Insert the pair (k,v) into Dictionary D. 
// If getUnique(D) is false (0), then there are no preconditions.
// If getUnique(D) is true (1), then the precondition lookup(D, k)==VAL_UNDEF
// is enforced. 
void insert(Dictionary D, KEY_TYPE k, VAL_TYPE v)
{
	if(D == NULL)
	{
		fprintf(stderr, "Manipulation Function: calling insert() on NULL List reference\n");
		exit(EXIT_FAILURE);			
	}
	if(getUnique(D))
	{
		if(lookup(D,k) != VAL_UNDEF)
		{
			fprintf(stderr, "Manipulation Function: calling insert() on duplicate key reference\n");
			exit(EXIT_FAILURE);			
		}
	}
	Node new = newNode(k,v);
	Node y = NULL;
	Node x = D->root;
	int level = -1;
	while(x != NULL)
	{
		y = x;
		if(KEY_CMP(k,x->key) < 0) x = x->left;
		else x = x->right;
		level++;
	}
	new->parent = y;
	if(D->size == 0 || y == NULL) D->root = new;
	else if (KEY_CMP(k,y->key) < 0) y->left = new;
	else y->right = new;
	D->size++;
}

// delete()
// Remove the pair whose key is k from Dictionary D.
// Pre: lookup(D,k)!=VAL_UNDEF (i.e. D contains a pair whose key is k.)
void delete(Dictionary D, KEY_TYPE k)
{
	if(D == NULL)
	{
		fprintf(stderr, "Manipulation Function: calling delete() on NULL List reference\n");
		exit(EXIT_FAILURE);			
	}
	if(lookup(D,k) != VAL_UNDEF)
	{
		if(D->cursor != NULL)
		{
			if(KEY_CMP(D->cursor->key,k)==0) D->cursor = NULL;
		}
		Node target = D->root;
		int match = 0;
		while(match == 0)
		{
			if(KEY_CMP(k,target->key) == 0) match = 1;
			else if(KEY_CMP(k,target->key) < 0) target = target->left;
			else target = target->right;
		}

		/////////////////////////////////////////////////////////////////

		if(target->left == NULL) Transplant(D,target,target->right);
		else if(target->right == NULL) Transplant(D,target,target->left);
		else
		{
			Node Y = TreeMinimum(target->right);
			if(Y->parent != target)
			{
				Transplant(D,Y,Y->right);
				Y->right = target->right;
				Y->right->parent = Y;
			}
			Transplant(D,target,Y);
			Y->left = target->left;
			Y->left->parent = Y;
		}
		freeNode(&target);
		D->size--;
	}
}

// makeEmpty()
// Reset Dictionary D to the empty state, containing no pairs.
void makeEmpty(Dictionary D)
{
	if(D == NULL)
	{
		fprintf(stderr, "Manipulation Function: calling makeEmpty() on NULL List reference\n");
		exit(EXIT_FAILURE);			
	}
	D->cursor = D->max = D->min = NULL;
	if(D->size > 0)
	{
		while(D->root != NULL && size > 0) delete(D,D->root->key);
	}
}

// beginForward()
// If D is non-empty, starts a forward iteration over D at the first key 
// (as defined by the order operator KEY_CMP()), then returns the first
// value. If D is empty, returns VAL_UNDEF. 
VAL_TYPE beginForward(Dictionary D)
{
	if(D == NULL)
	{
		fprintf(stderr, "Manipulation Function: calling beginForward() on NULL List reference\n");
		exit(EXIT_FAILURE);			
	}
	if(size(D) != 0)
	{
		D->cursor = TreeMinimum(D->root);
		return D->cursor->value;
	}
	return VAL_UNDEF;
}

// beginReverse()
// If D is non-empty, starts a reverse iteration over D at the last key 
// (as defined by the order operator KEY_CMP()), then returns the last
// value. If D is empty, returns VAL_UNDEF.
VAL_TYPE beginReverse(Dictionary D)
{
	if(D == NULL)
	{
		fprintf(stderr, "Manipulation Function: calling beginReverse() on NULL List reference\n");
		exit(EXIT_FAILURE);			
	}
	if(size(D) != 0)
	{
		D->cursor = TreeMaximum(D->root);
		return D->cursor->value;
	}
	return VAL_UNDEF;
}

// currentKey()
// If an iteration (forward or reverse) over D has started, returns the 
// the current key. If no iteration is underway, returns KEY_UNDEF.
KEY_TYPE currentKey(Dictionary D)
{
	if(D == NULL)
	{
		fprintf(stderr, "Manipulation Function: calling currentKey() on NULL List reference\n");
		exit(EXIT_FAILURE);			
	}
	if(D->cursor != NULL) return D->cursor->key;
	return KEY_UNDEF;
}

// currentVal()
// If an iteration (forward or reverse) over D has started, returns the 
// value corresponding to the current key. If no iteration is underway, 
// returns VAL_UNDEF.
VAL_TYPE currentVal(Dictionary D)
{
	if(D == NULL)
	{
		fprintf(stderr, "Manipulation Function: calling currentVal() on NULL List reference\n");
		exit(EXIT_FAILURE);			
	}
	if(D->cursor != NULL) return D->cursor->value;
	return VAL_UNDEF;
}

// next()
// If an iteration (forward or reverse) over D has started, and has not
// reached the last pair, moves to the next key in D (as defined by the 
// order operator KEY_CMP()), and returns the value corresponding to the 
// new key. If an iteration has started, and has reached the last pair,
// ends the iteration and returns VAL_UNDEF. If no iteration is underway, 
// returns VAL_UNDEF.
VAL_TYPE next(Dictionary D)
{
	if(D == NULL)
	{
		fprintf(stderr, "Manipulation Function: calling next() on NULL List reference\n");
		exit(EXIT_FAILURE);			
	}
	if(D->cursor != NULL && D->size > 0)
	{
		D->cursor = TreeSuccessor(D->cursor);
		if(D->cursor != NULL) return D->cursor->value;
		else return VAL_UNDEF;
	}
	return VAL_UNDEF;
}


// prev()
// If an iteration (forward or reverse) over D has started, and has not
// reached the first pair, moves to the previous key in D (as defined by the 
// order operator KEY_CMP()), and returns the value corresponding to the 
// new key. If an iteration has started, and has reached the first pair,
// ends the iteration and returns VAL_UNDEF. If no iteration is underway, 
// returns VAL_UNDEF. 
VAL_TYPE prev(Dictionary D)
{
	if(D == NULL)
	{
		fprintf(stderr, "Manipulation Function: calling prev() on NULL List reference\n");
		exit(EXIT_FAILURE);			
	}
	if(D->cursor != NULL && D->size > 0)
	{
		D->cursor = TreePredecessor(D->cursor);
		if(D->cursor != NULL) return D->cursor->value;
		else return VAL_UNDEF;
	}
	return VAL_UNDEF;
}


// Other operations -----------------------------------------------------------

// printDictionary()
// Prints a text representation of D to the file pointed to by out. Each key-
// value pair is printed on a single line, with the two items separated by a
// single space.  The pairs are printed in the order defined by the operator
// KEY_CMP().
void printDictionary(FILE* out, Dictionary D)
{
	if(D == NULL)
	{
		fprintf(stderr, "Manipulation Function: calling printDictionary() on NULL List reference\n");
		exit(EXIT_FAILURE);			
	}
	inOrderTreeWalk(D->root);
}
