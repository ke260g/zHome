#ifndef BFS_H
#define BFS_H

/* Breadth-First-Search */

#include"graph.h"
#include"slist/slist.h"

/* define a structure for vertices in a breadth-first search */
typedef struct BfsVertex_ {
    void *data;
    VertexColor color;
    int hops;
} BfsVertex;

/* public interface */
int bfs(Graph *graph,
        BfsVertex *start,
        SList *hops /* output-parameter */);

#endif
