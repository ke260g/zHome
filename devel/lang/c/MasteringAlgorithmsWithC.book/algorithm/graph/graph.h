#ifndef GRAPH_H
#define GRAPH_H

#include<stdio.h>
#include"set/set.h"
#include"slist/slist.h"

typedef struct AdjList_ {  /* adjacency lists */
    void *vertex;
    Set adjacent;
} AdjList;

typedef struct Graph_ { /* graph */
    int vcount; /* vertex count */
    int ecount; /* edge count */

    int (*match)(const void *key1, const void *key2);
    /* when it matches, return non-zero, else return 0 */

    void (*destroy)(void *data);

    SList adjlists;
    /*
        the element in the singly-list,
        its member, 'data'
        is pointing to a AdjList-Structure
    */
} Graph;

/* colors for vertices */
typedef enum VertexColor_ {
    VertexColorWhite,   /* has not been visited */
    VertexColorGray,    /* is being visited */
    VertexColorBlack    /* has been visited */
} VertexColor;

/* public interface */
void graph_init(Grap *graph,
        int (*match)(const void *key1, const void *key2),
        void (*destroy)(void *data));
void graph_destroy(Graph *graph);

int graph_ins_vertex(Graph *graph, const void *data);
int graph_ins_edge(Graph *graph,
        const void *vertex_from,
        const void *vertex_to);

int graph_rem_vertex(Graph *graph, void **data);
int graph_rem_edge(Graph *graph, void *data1, void **data2);

int graph_adjlist(const Graph *graph,
        const void *data,
        AdjList **adjlist); /* 'adjlist' is an output-parameter */
int graph_is_adjacent(const Graph *graph, const void *data1, const void *data2);
