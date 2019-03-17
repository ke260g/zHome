#include<stdlib.h>

#include"dfs.h"
#include"graph.h"
#include"slist/slist.h"

/* dfs_main, piravate-interface */
static int dfs_main(Graph *graph,
        AdjList *adjlist,
        SList *ordered) {
    AdjList *clr_adjlist;
    DfsVertex *clr_vertex, *adj_vertex;
    SListElmt *member;

    /* turn the vertex to gray and traverse its adjacency-list */
    ((DfsVertex *)adjlist->vertex)->color = VertexColorGray;

    for(member = (adjlist->adjacent).head; member != NULL; member = member->next) {
        /* Determine the color of the next adjacent vertex */
        adj_vertex = (DfsVertex *)member->data;

        if(graph_adjlist(graph, adj_vertex, &clr_adjlist))
            return -1;

        clr_vertex = (DfsVertex *)clr_adjlist->vertex;

        /* move one vertex deeper when the next adjacent vertex is white */
        if(clr_vertex->color == VertexColorWhite)
            if(dfs_main(graph, clr_adjlist, ordered))
                return -1; /* process error */
    }

    /* turn the current-vertex to black and make it first in the list */
    ((DfsVertex *)adjlist->vertex)->color = VertexColorBlack;

    if(slist_ins_next(ordered, NULL, (DfsVertex *)adjlist->vertex))
        return -1; /* process error */

    return 0;
}

/* dfs */
int dfs(Graph *graph, SList *ordered) {
    DfsVertex *vertex;
    SListElmt *element;

    /* Initialize all of the vertices in the graph */
    for(element = (graph->adjlists).head; element != NULL; element = element->next)
        ((DfsVertex *)((AdjList *)element->data)->vertex)->color = VertexColorWhite;

    /* Perform depth-first search */
    slist_init(ordered, NULL);
    for(element = (graph->adjlists).head; element != NULL; element = element->next) {
        /* Ensure that every component of unconnected graphs is searched */
        vertex = (DfsVertex *)((AdjList *)element->data)->vertex;

        if(vertex->color == VertexColorWhite)
            if(dfs_main(graph, (AdjList *)(element->data), ordered)) {
                slist_destroy(ordered); /* process error */
                return -1;
            }
    }
    return 0;
}
