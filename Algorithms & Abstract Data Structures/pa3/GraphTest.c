/*********************************************************************************
* Name: 			Jimmy Franknedy
* CruzID:			jfrankne
* Course: 			CSE 101 Spring 2020
* File name: 		GraphTest.c
* File Description: Testing functions for Graph.c
*********************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include "List.h"
#include "Graph.h"
#define INF -1
#define NIL 0 

int main()
{
	Graph A = newGraph(100);
	Graph B = newGraph(100);

	// Printing welcome message
	printf("Welcome to Jimmy's BigIntegerTest.c\n");
	printf("Programs will only prompt 'error' if there exists and error. Else the function works!\n");
	printf("\n ==================== Testing Access Fucntions ==================== \n");
	printf("Testing getOrder():\n");
	if(getOrder(A) != 100)
	{
		printf("error(1)\n");
	}
	if(getOrder(B) != 100)
	{
		printf("error(2)\n");
	}
	printf("Testing getSize():\n");
	if(getSize(A) != 0)
	{
		printf("error(3)\n");
	}
	printf("Testing getSource():\n");
	if(getSource(A) != NIL)
	{
		printf("error (4)\n");
	}
	printf("Testing getParent():\n");
	if(getParent(A,5) != NIL)
	{
		printf("error (9)\n");
	}

	printf("Testing getDist():\n");
	addArc(A, 64, 4);
    addArc(A, 64, 3);
    addArc(A, 42, 2);
    addArc(A, 2, 64);
    addArc(A, 4, 2);
    addArc(A, 3, 42);
    BFS(A, 64);
    BFS(A,4);
    if(getDist(A,42) != 4)
    {
    	printf("error (5)\n");
    }

	printf("Testing getPath():\n");
	BFS(A,3);
	List C = newList();
	List G = newList();
	getPath(G,A,64);
	append(C,3);
	append(C,42);
	append(C,2);
	append(C,64);
	if(equals(G,C) != 1)
	{
		printf("error (6)\n");
		printf("C: ");
		moveFront(C);
		while(index(C)!= -1)
		{
			printf("%d ",get(C));
			moveNext(C);
		}
		printf("\n");
		printf("G: ");
		moveFront(G);
		while(index(G) != -1)
		{
			printf("%d ",get(G));
			moveNext(G);
		}
		printf("\n");
	}
	clear(C);
	clear(G);
	append(C,NIL);
	BFS(A,99);
	getPath(G,A,2);
	if(equals(C,G) != 1)
	{
		printf("error (7)\n");
		printf("C: ");
		moveFront(C);
		while(index(C)!= -1)
		{
			printf("%d ",get(C));
			moveNext(C);
		}
		printf("\n");
		printf("G: ");
		moveFront(G);
		while(index(G) != -1)
		{
			printf("%d ",get(G));
			moveNext(G);
		}
		printf("\n");		
	}
	freeList(&C);
	freeList(&G);
	printf("\n ================= Testing Manipulation Procedures ================ \n");
	printf("Testing makeNull():\n");
	// Test in freeGraph():
	printf("Testing addEdge():\n");
	printf("Testing addArc():\n");
	// Tested above():
	printf("Testing BFS():\n");	
	// Tested above
	printf("\n ==================== Testing Other Operations ==================== \n");
	printf("Testing printGraph():\n");

	freeGraph(&A);
	freeGraph(&B);
}