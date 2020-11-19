/*********************************************************************************
* Name: 			Jimmy Franknedy
* CruzID:			jfrankne
* Course: 			CSE 101 Spring 2020
* File name: 		FindPath.c
* File Description: Main algorithm for implementing BFS on input file
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
#define MAX 10
int main(int argc, char* argv[])
{
	if(argc != 3)
    {
        fprintf(stderr, "Inproper Usage: Invalid findPath input\n");
        exit(EXIT_FAILURE); 
    }
    // File Access 
    FILE* in;   // input file to read from
    FILE* out;  // output file to write to

    // Check to see if input file can be read
    in = fopen(argv[1], "r");
    if(in == NULL)
    {
    	fprintf(stderr, "Inproper Usage: Invalid input file\n");
        exit(EXIT_FAILURE);    
    }

    // Check to see if putput file can be written into
    out = fopen(argv[2], "wr+");
    if(out == NULL)
    {
        fprintf(stderr, "Inproper Usage: Invalid output file\n");
        exit(EXIT_FAILURE);          
    }
    char n[1];
    fscanf(in,"%s",n);
    int graph_input = atoi(n);
    int u = 1;
    int v = 1;
    Graph G = newGraph(graph_input);
    while((u != 0) && (v!= 0))
    {
    	char U[MAX];
    	char V[MAX];
    	fscanf(in,"%s",U);
    	fscanf(in,"%s",V);
    	u = atoi(U);
    	v = atoi(V);
    	if((u != 0) && (v!= 0))
    	{
	    	addEdge(G,u,v);
	   	}
    }
    u = 1;
    v = 1;
    List P = newList();
    while((u != 0) && (v!= 0))
    {
    	char U[MAX];
    	char V[MAX];
    	fscanf(in,"%s",U);
    	fscanf(in,"%s",V);
    	u = atoi(U);
    	v = atoi(V);
    	if((u != 0) && (v!= 0))
    	{
	        append(P,u);
    		append(P,v);
    	}
    }
    printGraph(out,G);
    int loop = (length(P))/2;
    for(int i = 0; i < loop; i++)
    {
    	int value_1 = front(P);
    	deleteFront(P);
    	int value_2 = front(P);
    	deleteFront(P);
    	BFS(G,value_1);
    	List Path = newList();
    	// printf("value_1: %d\n",value_1);
    	// printf("value_2: %d\n",value_2);
    	// printf("getSource: %d\n",getSource(G));
    	// printf("-START-\n");
    	getPath(Path,G,value_2);
    	// printf("-END-\n");
    	fprintf(out,"The distance from %d to %d is ",value_1,value_2);
    	fprintf(stdout,"The distance from %d to %d is ",value_1,value_2);
    	if(getDist(G,value_2) != INF)
    	{
    		fprintf(out,"%d\n",getDist(G,value_2));
    		fprintf(stdout,"%d\n",getDist(G,value_2));
    	}
    	else
    	{
    		fprintf(out,"infinity\n");	
    		fprintf(stdout,"infinity\n");
    	}
    	moveFront(Path);
    	if(get(Path) != NIL)
    	{
    		fprintf(out,"A shortest %d-%d path is: ",value_1,value_2);
    		fprintf(stdout,"A shortest %d-%d path is: ",value_1,value_2);
	    	while(index(Path) != -1)
	    	{
	    		fprintf(out,"%d ",get(Path));
	    		fprintf(stdout,"%d ",get(Path));
	    		moveNext(Path);
	    	}
    	}
    	else
    	{
    		fprintf(out,"No %d-%d path exists",value_1,value_2);
    		fprintf(stdout,"No %d-%d path exists",value_1,value_2);

    	}
    	freeList(&Path);
    	fprintf(out,"\n\n");
    	fprintf(stdout,"\n\n");
    }
    freeList(&P);
    freeGraph(&G);
    fclose(in);
    fclose(out);
}