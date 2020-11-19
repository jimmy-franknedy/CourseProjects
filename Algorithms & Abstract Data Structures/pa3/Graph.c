/*********************************************************************************
* Name: 			Jimmy Franknedy
* CruzID:			jfrankne
* Course: 			CSE 101 Spring 2020
* File name: 		Graph.c
* File Description: Function code for Graph.h
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


/*** Constructors-Destructors ***/

// Graph reference type
typedef struct GraphObj
{
	List *N; 		// Array of lists representing the ith index's neighbors
	int *color;		// Array of ints representing the color of the 'node'
	int *parent; 	// Array of ints, where the ith element is the parent of the ith vertex
	int *distance; 	// Array of ints, where the ith element is the distance from the ith vertex to the source
	int order;			// number of 'vertices' in the graph (i.e end points)
	int size;  			// number of 'edges' in the graph (i.e line segments)
	int source;			// variable holding the most recently vertex as it's source

}GraphObj;


// Returns a Graph pointing to a newly created GraphObj representing a graph having and 'n' vertices and no edges
Graph newGraph(int n)
{
	Graph G = malloc(sizeof(GraphObj));
	assert(G!=NULL);
	G->color = calloc(n+1,sizeof(int));
	G->parent = calloc(n+1,sizeof(int));
	G->distance = calloc(n+1,sizeof(int));
	G->N= calloc(n+1,sizeof(List));
	for(int i = 1; i<n+1; i++)
	{
		G->N[i] = newList();
		G->color[i] = 1;
		G->parent[i] = NIL;
		G->distance[i] = INF;
	}
	G->order = n;
	G->size = 0;
	G->source = NIL;
	return G;
}

// frees all dynamic memory associated with the Graph *pG, then sets the handle *pG to NULL
void freeGraph(Graph* pG)
{
	if(pG != NULL && *pG != NULL)
	{
		makeNull(*pG);
		free((*pG)->color);
		free((*pG)->parent);
		free((*pG)->distance);
		for(int i = 1; i <= getOrder((*pG)); i++)
		{
			freeList(&((*pG)->N[i]));
		}
		free((*pG)->N);
		(*pG)->N = NULL;
		free(*pG);
		*pG = NULL;
	}
}

/*** Access functions ***/

// Return order of graph G -or- number of 'vertices' in Graph G (i.e endpoints)
int getOrder(Graph G)
{
	// Checking validity
	if(G == NULL)
	{
		fprintf(stderr, "Access function: calling getOrder() on NULL Graph reference\n");
		exit(EXIT_FAILURE);			
	}
	return G->order;
}

// Return size of graph G -or- number of 'edges' in Graph G (i.e line segments)
int getSize(Graph G)
{
	// Checking validity
	if(G == NULL)
	{
		fprintf(stderr, "Access function: calling getSize() on NULL Graph reference\n");
		exit(EXIT_FAILURE);			
	}
	return G->size;
}

// Returns the source vertex most recently used in function BFS(), or NIL if BFS() has not yet been called.
int getSource(Graph G)
{
	// Checking validity
	if(G == NULL)
	{
		fprintf(stderr, "Access function: calling getSource() on NULL Graph reference\n");
		exit(EXIT_FAILURE);			
	}
	return G->source;
}

// Returns the parent of vertex u in the BreadthFirst tree created by BFS(), or NIL if BFS() has not yet been called.
int getParent(Graph G, int u)
{
	// Checking validity
	if(G == NULL)
	{
		fprintf(stderr, "Access function: calling getParent() on NULL Graph reference\n");
		exit(EXIT_FAILURE);			
	}
	return G->parent[u];
}

// Returns the distance from the most recent BFS source to vertex u, or INF if BFS() has not yet been called.
int getDist(Graph G, int u)
{
	// Checking validity
	if(G == NULL)
	{
		fprintf(stderr, "Access function: calling getDist() on NULL Graph reference\n");
		exit(EXIT_FAILURE);			
	}
	return G->distance[u];
}

// appends to the List L the vertices of a shortest path in G from source to u, or appends to L the value NIL if no such path exists.
void getPath(List L, Graph G, int u)
{
	// Checking validity
	if(G == NULL)
	{
		fprintf(stderr, "Access function: calling getPath() on NULL Graph reference\n");
		exit(EXIT_FAILURE);			
	}
	if(u == NIL)
	{
		// printf("check\n");
		append(L,NIL);
	}
	else
	{
		// printf("parent[u]: %d\n",getParent(G,u));
		if(u == G->source)
		{
			// printf("check 1\n");
			append(L,u);
		}
		else if (getParent(G,u) == NIL)
		{
			// printf("check 2\n");
			append(L,NIL);
		}
		else if (getParent(G,u) == G->source)
		{
			// printf("check 3\n");
			append(L,getParent(G,u));
			append(L,u);
		}
		else
		{
			// printf("check 4\n");
			getPath(L,G,G->parent[u]);
			append(L,u);
		}
		// printf("preOut!\n");
	}
	// printf("out!\n");
}

/*** Manipulation procedures ***/

// Deletes all edges of G, restoring it to its original (no edge) state
void makeNull(Graph G)
{
	// Checking validity
	if(G == NULL)
	{
		fprintf(stderr, "Manipulation procedures: calling makeNull() on NULL Graph reference\n");
		exit(EXIT_FAILURE);			
	}
	for(int i = 1; i <= G->order; i++)
	{
		clear(G->N[i]);
		G->color[i] = 0;
		G->distance[i] = 0;
		G->parent[i] = 0;

	}
	G->size = 0;
	G->source = NIL;
}

// Pre: the two int arguments must lie in the range 1 to getOrder(G)
// Inserts a new edge joining u to v, i.e. u is added to the adjacency List of v, and v to the adjacency List of u
void addEdge(Graph G, int u, int v)
{
	// Checking validity
	if(G == NULL)
	{
		fprintf(stderr, "Manipulation procedures: calling addEdge() on NULL Graph reference\n");
		exit(EXIT_FAILURE);			
	}
	if(u >= 1 && u <= getOrder(G))
	{
		if(v >= 1 && v <= getOrder(G))
		{
			// Add 'v' to the adjacency list of 'u'
			addArc(G,u,v);
			G->size--;
			// Add 'u' to the adjacency list of 'v'
			addArc(G,v,u);	
		}
	}
}
// Pre: the two int arguments must lie in the range 1 to getOrder(G)
// Inserts a new directed edge from u to v, i.e. v is added to the adjacency List of u (but not u to the adjacency List of v)
void addArc(Graph G, int u, int v)
{
	// Checking validity
	if(G == NULL)
	{
		fprintf(stderr, "Manipulation procedures: calling addArc() on NULL Graph reference\n");
		exit(EXIT_FAILURE);			
	}
	if((u >= 1) && (u <= getOrder(G)))
	{
		if((v >= 1) && (v <= getOrder(G)))
		{
			// Add 'v' to the adjacency list of 'u'
			if(length(G->N[u]) > 0)
			{
				if(v >= back(G->N[u]))
				{
					if(v != back(G->N[u]))
					{
						append(G->N[u],v);					
					}
				}
				else if(v <= front(G->N[u]))
				{
					if(v != front(G->N[u]))
					{
						prepend(G->N[u],v);
					}
				}
				else
				{
					moveFront(G->N[u]);
					while(index(G->N[u]) >= 0 && get(G->N[u]) <= v)
					{
						moveNext(G->N[u]);
					}
					movePrev(G->N[u]);
					if(get(G->N[u]) != v)
					{
						insertAfter(G->N[u],v);
					}
				}
			}
			else
			{
				append(G->N[u],v);
			}
			G->size++;
		}
	}
}

// runs the BFS algorithm on the Graph G with source s, setting the color, distance, parent, and source fields of G accordingly. 
void BFS(Graph G, int s)
{
	// Checking validity
	if(G == NULL)
	{
		fprintf(stderr, "Manipulation procedures: calling BFS() on NULL Graph reference\n");
		exit(EXIT_FAILURE);			
	}
	// Reset Arrays
	for(int i = 1; i <= getOrder(G); i++)
	{
		if(i != s)
		{
			G->parent[i] = NIL;
			G->distance[i] = INF;
			G->color[i] = 1;
		}
	}
 	G->color[s] = 2;
 	G->parent[s] = NIL;
	G->distance[s] = 0;
	G->source = s;
	List Q = newList();	
 	append(Q,s);
	while(length(Q) > 0)
	{
		int val = front(Q);
		deleteFront(Q);
		moveFront(G->N[val]);
		while(index(G->N[val]) != -1)
		{
			if(G->color[get(G->N[val])] == 1)
			{
				G->color[get(G->N[val])] = 2;
				G->distance[get(G->N[val])] = G->distance[val] + 1;
				G->parent[get(G->N[val])] = val;
				append(Q,get(G->N[val]));
			}
			moveNext(G->N[val]);
		}
		G->color[val] = 3;
	}
	freeList(&Q);
}

/*** Other operations ***/
// prints the adjacency list representation of G to the file pointed to by out
void printGraph(FILE* out, Graph G)
{
	// Checking validity
	if(G == NULL)
	{
		fprintf(stderr, "Other operations: calling printGraph() on NULL Graph reference\n");
		exit(EXIT_FAILURE);			
	}
	for(int i = 1; i <= getOrder(G); i++)
	{
		fprintf(out,"%d: ",i);
		fprintf(stdout,"%d: ",i);
		moveFront(G->N[i]);
		while(index(G->N[i]) != -1)
		{
			fprintf(out,"%d ",get(G->N[i]));
			fprintf(stdout,"%d ",get(G->N[i]));
			moveNext(G->N[i]);
		}
		fprintf(out,"\n\n");
		fprintf(stdout,"\n\n");
	}
}