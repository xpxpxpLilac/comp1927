// Graph.c ... implementation of Graph ADT
// Written by John Shepherd, May 2013

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "Graph.h"
#include "Queue.h"

// graph representation (adjacency matrix)
typedef struct GraphRep {
	int    nV;    // #vertices
	int    nE;    // #edges
	int  **edges; // matrix of weights (0 == no edge)
} GraphRep;

// check validity of Vertex
int validV(Graph g, Vertex v)
{
	return (g != NULL && v >= 0 && v < g->nV);
}

// make an edge
Edge mkEdge(Graph g, Vertex v, Vertex w)
{
	assert(g != NULL && validV(g,v) && validV(g,w));
	Edge new = {v,w}; // struct assignment
	return new;
}

// insert an Edge
// - sets (v,w) and (w,v)
void insertEdge(Graph g, Vertex v, Vertex w, int wt)
{
	assert(g != NULL && validV(g,v) && validV(g,w));
	if (g->edges[v][w] == 0) {
		g->edges[v][w] = wt;
		g->edges[w][v] = wt;
		g->nE++;
	}
}

// remove an Edge
// - unsets (v,w) and (w,v)
void removeEdge(Graph g, Vertex v, Vertex w)
{
	assert(g != NULL && validV(g,v) && validV(g,w));
	if (g->edges[v][w] != 0) {
		g->edges[v][w] = 0;
		g->edges[w][v] = 0;
		g->nE--;
	}
}

// create an empty graph
Graph newGraph(int nV)
{
	assert(nV > 0);
	int v, w;
	Graph new = malloc(sizeof(GraphRep));
	assert(new != 0);
	new->nV = nV; new->nE = 0;
	new->edges = malloc(nV*sizeof(int *));
	assert(new->edges != 0);
	for (v = 0; v < nV; v++) {
		new->edges[v] = malloc(nV*sizeof(int));
		assert(new->edges[v] != 0);
		for (w = 0; w < nV; w++)
			new->edges[v][w] = 0;
	}
	return new;
}

// free memory associated with graph
void dropGraph(Graph g)
{
	assert(g != NULL);
	// not needed for this lab
}

// display graph, using names for vertices
void showGraph(Graph g, char **names)
{
	assert(g != NULL);
	printf("#vertices=%d, #edges=%d\n\n",g->nV,g->nE);
	int v, w;
	for (v = 0; v < g->nV; v++) {
		printf("%d %s\n",v,names[v]);
		for (w = 0; w < g->nV; w++) {
			if (g->edges[v][w]) {
				printf("\t%s (%d)\n",names[w],g->edges[v][w]);
			}
		}
		printf("\n");
	}
}

// find a path between two vertices using breadth-first traversal
// only allow edges whose weight is less than "max"
int findPath(Graph g, Vertex src, Vertex dest, int max, int *path)
{
	assert(g != NULL);
        int *visited; // array [0..V-1] of boolean

        int i;
   	visited = malloc(g->nV * sizeof(int));
   	for (i = 0; i < g->nV; i++) visited[i] = 0;
   	Vertex *prev = malloc(g->nV * sizeof(Vertex));   //where the current city fly from 
   	Queue q = newQueue();
   	QueueJoin(q, src); visited[src] = 1;
   	int isFound = 0;
	int count = 1;

   	while (!QueueIsEmpty(q) && !isFound) {
//        showQueue(q);
//        printf("start city is %d and destination is %d\n",src,dest);
      	Vertex y, x = QueueLeave(q);
      		for (y = 0; y < g->nV; y++) {   //visited[y] is to ensure it is the first time 
         		if (!g->edges[x][y] || g->edges[x][y] >= max || visited[y]) continue;        //jump from this condition,that is,if y=o is the codition,then jump directly to y=1
			if(g->edges[x][y] < max) {
         			prev[y] = x;
  //                              printf("x is %d\n",x);
  //				printf("y is %d\n",y);
  //				printf("distance is %d\n",g->edges[x][y]);
         			if (!visited[y]) {
            				QueueJoin(q, y);
            				visited[y] = 1;
         			}
//				printf("======================== First for loop\n");
                                if (y == dest) { isFound = 1; break; } 
      			}
//                        printf("======================Second fpr loop\n");
		}
// 		printf("========================= while loop\n");
   	}
       
      Vertex v = dest;
      if(!QueueIsEmpty(q)) {
          while(v != src){
               v = prev[v];
//               printf("v now is %d\n",v);      
               count++;
	  }
      } else if(src == dest) {
         count = 1;
      } else {
         count = 0;
      }
//      printf("count is %d\n",count);
       int n = count-1;
       int m = dest;
       path[n] = dest;
       while(n >= 0) {
	  path[n-1] = prev[m];
	  n--;
	  m = prev[m]; 
      }
 
      return count;
}
