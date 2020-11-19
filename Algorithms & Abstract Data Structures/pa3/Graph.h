/*********************************************************************************
* Name: 			Jimmy Franknedy
* CruzID:			jfrankne
* Course: 			CSE 101 Spring 2020
* File name: 		Graph.h
* File Description: Function prototypes for Graph.c
*********************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include "List.h"
#define INF -1
#define NIL 0 

// Graph reference type
typedef struct GraphObj* Graph;

/*** Constructors-Destructors ***/

// Returns a Graph pointing to a newly created GraphObj representing a graph having and 'n' vertices and no edges
Graph newGraph(int n);

// frees all dynamic memory associated with the Graph *pG, then sets the handle *pG to NULL
void freeGraph(Graph* pG);

/*** Access functions ***/

// Return order of graph G
int getOrder(Graph G);

// Return size of graph G
int getSize(Graph G);

// Returns the source vertex most recently used in function BFS(), or NIL if BFS() has not yet been called.
int getSource(Graph G);

// Returns the parent of vertex u in the BreadthFirst tree created by BFS(), or NIL if BFS() has not yet been called.
int getParent(Graph G, int u);

// Returns the distance from the most recent BFS source to vertex u, or INF if BFS() has not yet been called.
int getDist(Graph G, int u);

// appends to the List L the vertices of a shortest path in G from source to u, or appends to L the value NIL if no such path exists.
void getPath(List L, Graph G, int u);

/*** Manipulation procedures ***/

// Deletes all edges of G, restoring it to its original (no edge) state
void makeNull(Graph G);

// Pre: the two int arguments must lie in the range 1 to getOrder(G)
// Inserts a new edge joining u to v, i.e. u is added to the adjacency List of v, and v to the adjacency List of u
void addEdge(Graph G, int u, int v);

// Pre: the two int arguments must lie in the range 1 to getOrder(G)
// Inserts a new directed edge from u to v, i.e. v is added to the adjacency List of u (but not u to the adjacency List of v)
void addArc(Graph G, int u, int v);

// runs the BFS algorithm on the Graph G with source s, setting the color, distance, parent, and source fields of G accordingly. 
void BFS(Graph G, int s);

/*** Other operations ***/
// prints the adjacency list representation of G to the file pointed to by out
void printGraph(FILE* out, Graph G);

