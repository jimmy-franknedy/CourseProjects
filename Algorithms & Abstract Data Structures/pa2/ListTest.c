/*********************************************************************************
* Name: 			Jimmy Franknedy
* CruzID:			jfrankne
* Course: 			CSE 101 Spring 2020
* File name: 		ListTest.c
* File Description: Program code for testing List ADT functions!
*********************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "List.h"

int main()
{
	// Printing welcome message
	printf("Welcome to Jimmy's ListTest.c\n");
	printf("Programs will only prompt 'error' if there exists and error. Else the function works!\n");

	// Generating newLists
	List A = newList();
	List B = newList();
	List C = newList();
	List D = newList();
	List E = newList();
	List F = NULL;
	List G = newList();
	List H = newList();
	List M = newList();
	List N = newList();
	List O = newList();
	List X = newList();
	List Y = newList();
	List Z = newList();
	List V = newList();

	// List M = 0 -> 10
	for(int i = 0; i < 10; i++)
	{
		append(M,i);
	}


	// List N = 10-> 20
	for(int i = 10; i < 20; i++)
	{
		append(N,i);
	}

	// List A  = 10 elements
	for(int i = 0; i< 10 ; i++)
	{
		append(A,i);
	}

	// List B = 20 elements
	for(int i = 0; i< 20; i++)
	{
		prepend(B, i);
		append(O, i);
	}

	// List C = 10 elements
	for(int i = 0; i< 10; i++)
	{
		append(C,i);
		append(G,i);
	}

	// List D = 20 elements
	for(int i = 0; i< 20; i++)
	{
		append(D,i);
		append(H,i);
	}

	// List X, Y, Z = 3 elements
	for(int i = 0; i< 3; i++)
	{
		append(X,i);
		append(Y,i);
		append(Z,i);
		append(V,i);
	}
	// Checkpoint: Testing Access Functions
	printf("====================     Testing Access Functions    ====================\n");
	printf("Testing length(): \n");
	if(length(A) != 10)
	{
		printf("Error(1)\n");
	}
	printf("Testing index(): \n");
	moveFront(A);
	if(index(A) != 0)
	{
		printf("Error(2)\n");
	}
	moveBack(A);
	if(index(A) != 9)
	{
		printf("Error(3)\n");
		printf("index(A): %d\n",index(A));

	}
	moveFront(B);
	if(index(B) != 0)
	{
		printf("Error(4)\n");
		printf("index(B) = %d\n",index(B));
	}
	moveBack(B);
	if(index(B) != 19)
	{
		printf("Error(5)\n");
		printf("index(B) = %d\n",index(B));
	}
	printf("Testing front(): \n");
	if(front(A) != 0)
	{
		printf("Error(6)\n");
	}
	if(front(B) != 19)
	{
		printf("Error(8)\n");
	}
	printf("Testing back(): \n");
	if(back(A) != 9)
	{
		printf("Error(7)\n");
	}
	if(back(B) != 0)
	{
		printf("Error(9)\n");
	}
	printf("Testing get(): \n");
	if(get(A) != 9)
	{
		printf("Error(10)\n");
	}
	if(get(B) != 0)
	{
		printf("Error(11)\n");
	}
	printf("Testing equalz(): \n");
	if(equalz(A,C) != 1)
	{
		printf("Error(12)\n");
	}
	printf("Testing set():\n");
	moveFront(G);
	set(G,100);
	if(get(G) != 100)
	{
		printf("Error (12.1)\n");
	}
	moveBack(G);
	set(G,-100);
	if(get(G) != -100)
	{
		printf("Error (12.2\n");
	}

	// Checkpoint: Testing Manipulation Procedures
	printf("==================== Testing Manipulation Procedures ====================\n");
	printf("Testing clear(): \n");
	// Tested below inside freeList()

	printf("Testing moveFront(): \n");
	// Tested above inside index()

	printf("Testing moveBack(): \n");
	// Tested above inside index()

	printf("Testing movePrev(): \n");

	// Normal Case > movePrev() >> some node
	moveFront(C);
	movePrev(C);
	if(index(C) != -1)
	{
		printf("Error(13)\n");
	}

	// Special Case > movePrev() >> NULL
	moveBack(D);
	movePrev(D);
	if(index(D) == -1)
	{
		printf("Error(14)\n");
	}
	printf("Testing moveNext(): \n");

	// Normal Case > moveNext() >> some node
	moveBack(C);
	moveNext(C);
	if(index(C) != -1)
	{
		printf("Error(15)\n");
	}

	// Special Case > moveNext() >> NULL
	moveFront(D);
	moveNext(D);
	if(index(D) == -1)
	{
		printf("Error(16)\n");
	}
	printf("Testing prepend(): \n");
	// Tested above in 'Generating List'

	printf("Testing append(): \n");
	// Tested above in 'Generating List'

	printf("Testing insertBefore(): \n");

	// Normal Case > insertBefore() >> cursor == some node
	moveBack(A);
	insertBefore(A,20);
	movePrev(A);
	if(get(A) != 20)
	{
		printf("Error(17)\n");
		printf("get(A) = %ld\n",get(A));
	}

	// Special Case > insertBefore() >> cursor == "front"
	moveFront(A);
	insertBefore(A,21);
	if(front(A) != 21)
	{
		printf("Error(18)\n");
	}

	printf("Testing insertAfter(): \n");

	// Normal Case > insertAfter() >> cursor == some node
	moveFront(A);
	insertAfter(A,22);
	moveNext(A);
	if(get(A) != 22)
	{
		printf("Error(19)\n");
	}

	// Special Case > insertAfter() >> cursor == "back"
	moveBack(A);
	insertAfter(A,23);
	moveNext(A);
	if(get(A) != 23)
	{
		printf("Error(20)\n");
	}

	printf("Testing deleteFront(): \n");

	// Normal Case > deleteFront() >> length > 3
	moveFront(X);
	deleteFront(X);
	moveFront(X);
	if(index(X) != 0)
	{
		printf("Error(21)\n");
		printf("index(X) = %d\n",index(X));
	}

	// Special Case > deleteFront() >> length == 2
	moveBack(X);
	deleteFront(X);
	moveBack(X);
	if(index(X) != 0)
	{
		printf("Error(22)\n");
		printf("index(X) = %d\n",index(X));
	}	

	// Special Case > deleteFront() >> length == 1
	deleteFront(X);
	moveFront(X);
	if(index(X) != -1)
	{
		printf("Error(23)\n");
		printf("index(X) = %d\n",index(X));
	}

	printf("Testing deleteBack(): \n");

	// Normal Case > deleteBack() >> length > 3
	moveBack(Y);
	deleteBack(Y);
	moveBack(Y);
	if(index(Y) != 1)
	{
		printf("Error(24)\n");
	}

	// Special Case > deleteBack() >> length == 2
	moveFront(Y);
	deleteBack(Y);
	moveBack(Y);
	if(index(Y) != 0)
	{
		printf("Error(25)\n");
	}

	// Special Case > deleteBack >> length == 1
	deleteBack(Y);
	moveBack(Y);
	if(index(Y) != -1)
	{
		printf("Error(26)\n");
		printf("index(Y) = %d\n",index(Y));
	}

	// printf("Testing delete(): \n");

	// Normal case > delete() >> length == 3

	// printf("init_Length(Z): %d\n",length(Z));
	// printf("init_Length(V): %d\n",length(V));

	moveFront(Z);
	moveNext(Z);
	delete(Z);

	moveFront(V);
	moveNext(V);
	delete(V);

	// Special Case > delete() >> length == 2 >> cursor == L->front
	// printf("case 1\n");
	moveFront(Z);
	delete(Z);

	// Special Case > delete() >> length == 2 >> cursor == L->back
	// printf("case 2\n");
	moveBack(V);
	delete(V);

	// Speical case > delete() >> length == 1 >> cursor == L->back
	// printf("case 3 \n");
	moveFront(Z);
	delete(Z);

	// Special case > delete() >> length == 1 >> cursor == L->front
	// printf("case 4\n");
	moveBack(V);
	delete(V);


	// Checkpoint: Testing Other Functions
	printf("====================     Testing Other Functions     ====================\n");
	printf("Testing printList(): \n");

	// // ======================================================== //
	// moveFront(Z);
	// moveFront(V);
	// printf("Length(Z): %d\n",length(Z));
	// printf("Length(V): %d\n",length(V));
	// for(int i = 0; i < length(Z); i++)
	// {
	// 	printf("[Z] %d: %d {%ld}\n",i,index(Z),get(Z));
	// 	moveNext(Z);
	// }
	// printf("--------------------------------------------\n");
	// for(int i = 0; i < length(V); i++)
	// {
	// 	printf("[V] %d: %d {%ld}\n",i,index(V),get(V));
	// 	moveNext(V);
	// }
	// // ======================================================== //

	printf("Testing copyList(): \n");
	List duplicate = copyList(H);
	if(equalz(duplicate,H) != 1)
	{
		printf("Error 27\n");
	}

	printf("Testing concatList(): \n");
	List concatnate = concatList(M,N);
	if(equalz(O,concatnate) != 1)
	{
		printf("Error 28\n");
	}


	// Freeing generated newLists
	printf("\n");
	freeList(&A);
	freeList(&B);
	freeList(&C);
	freeList(&D);
	freeList(&E);
	freeList(&F);
	freeList(&G);
	freeList(&H);
	freeList(&M);
	freeList(&N);
	freeList(&O);
	freeList(&X);
	freeList(&Y);
	freeList(&Z);
	freeList(&V);
	freeList(&duplicate);
	freeList(&concatnate);

	// Return the program with a success!
	return EXIT_SUCCESS;
}