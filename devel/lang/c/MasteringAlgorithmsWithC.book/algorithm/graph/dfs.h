#ifndef DFS_H
#define DFS_H

/* Deep-First-Search */

#include"graph.h"
#include"slist/slist.h"

typedef struct DfsVertex_ {
    void *data;
    VertexColor color;
} DfsVertex;

/* public interface */
int dfs(Graph *graph,
        SList *ordered /* output-parameter */);

#endif
