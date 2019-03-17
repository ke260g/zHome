#include<stdlib.h>
#include<string.h>

#include"graph.h"
#include"slist/slist.h"
#include"set/set.h"

void graph_init(Graph *graph,
        int (*match)(const void *key1, const void *key2),
        void (*destroy)(void *data)) {
    /* initialize the graph */
    graph->vcount = 0;
    graph->ecount = 0;
    graph->match = match;
    graph->destroy = destroy;

    /* initialize the list of adjacency-list */
    slist_init(&graph->adjlists, NULL);
}

void graph_destroy(Graph *graph) {
    AdjList *adj_list;

    /* Remove each adjacency-list and destroy its adjacency list */
    while((graph->adjlists).size > 0) {
        if(slist_rem_next(&graph->adjlists, NULL, (void **)&adj_list) == 0) {

            set_destroy(&adj_list->adjacent);

            if(graph->destroy != NULL)
                graph->destroy(adj_list->vertex);

            free(adj_list);

        }
    }

    /* Destroy the list of adjacency-list, which is now empty */
    slist_destroy(&graph->adjlists);

    /* No operation is allowed now, but clear the structure as a precaution */
    memset(graph, 0, sizeof(Graph));
}

int graph_ins_vertex(Graph *graph,
        const void *data) {
    SListElmt *element;
    AdjList *adjlist;
    int ret;

    /* do not allow the insertion of duplicate vertices */
    for(element = (graph->adjlists).head ; element != NULL ; element = element->next) {
        if(graph -> match(data, ((AdjList *)(element->data))->vertex))
            return 1; /* the input data is a duplicate */
    }

    /* when the input data is not a duplicate */
    adjlist->vertex = (void *)data;
    set_init(&adjlist->adjacent, graph->match, NULL);

    if((ret = slist_ins_next(&graph->adjlists, (graph->adjlists).tail, adjlist)) != 0)
        return ret; /* fail to insert the new vertex */

    /* when succeed to insert the new vertex,
     * adjust the vertex count. */
    graph->vcount++;
    return 0;

}

int graph_ins_edge(Graph *graph,
        const void *vertex_from, const void *vertex_to){
    /* do not allow insertion of an edge without both its vertices in the graph */
    SListElmt *element;
    int ret;

    for(element = (graph->adjlists).head; element != NULL; element = element->next)
        if(graph->match(vertex_from, ((AdjList *)(element->data))->vertex))
            break;
    /* can not find the 'vertex' defined by 'vertex_from' */
    if(element == NULL)
        return -1;

    for(element = (graph->adjlists).head; element != NULL; element = element->next)
        if(graph->match(vertex_to, ((AdjList *)(element->data))->vertex))
            break;
    /* can not find the 'vertex' defined by 'vertex_to' */
    if(element == NULL)
        return -1;

    /* Insert the second vertex into the adjacency-list of the vertex_from */
    if(set_insert(&((AdjList *)(element->data))->adjacent, vertex_to))
        /* failed to insert the adjacent to first_vertex */
        return ret;

    graph->ecount++;
    return 0;
}

int graph_rem_vertex(Graph *graph, void **data) {
    SListElmt *element,
              *temp,
              *prev;
    AdjList *adj_list;  /* store the removed vertex */
    int found; /* whether found or not */

    /* Traverse each adjacency list and the vertices it contains */
    prev = NULL;
    found = 0;

    for(element = (graph->adjlists).head; element != NULL; element = element->next) {
        /* do not allow removal of the vertex when it is in a adjacency list */
        if(set_is_member(&((AdjList *)(element->data))->adjacent, *data))
            return -1;

        /* keep a pointer to the vertex to be removed */
        if(graph->match(*data, ((AdjList *)(element->data))->vertex)) {
            temp = element;
            found = 1;
        }

        /* keep a pointer to the vertex before the vertex to be removed */
        if(!found)
            prev = element;
    }

    /* return if the vertex was not found */
    if(!found)
        return -1;

    /* do not allow removal of the vertex if its adjacency list is not empty */
    if((&((AdjList *)(temp->data))->adjacent)->size > 0)
        return -1;

    /* remove the vertex */
    if(slist_rem_next(&graph->adjlists, prev, (void **)&adj_list))
        return -1;  /* faild to remove */

    *data = adj_list->vertex;
    free(adj_list);

    /* adjust the vertex count to account for the removed vertex */
    graph->vcount--;
    return 0;
}

int graph_rem_edge(Graph *graph,
        void *vertex_from, void **vertex_to) {
    SListElmt *element;

    /* Locate the adjacency list for the first vertex */
    for(element = (graph->adjlists).head; element != NULL; element = element->next)
        if(graph->match(vertex_from, ((AdjList *)(element->data))->vertex))
                break;

    if(element == NULL)
        return -1; /* the input vertex is not in the graph */

    /* remove the vertex_to from the adjacency list of the vertex_from */
    if(set_remove(&((AdjList *)(element->data))->adjacent, vertex_to))
        return -1; /* for some reason, failed to remove */

    graph->ecount--;
    return 0;
}

/* graph_adjlist */
int graph_adjlist(const Graph *graph,
        const void *vertex,
        AdjList **adjlist){
    /* input a 'vertex', output its adjacency in the specific graph */
    SListElmt *element, *prev;

    /* Locate the adjacency list for the vertex */
    prev = NULL;
    for(element = (graph->adjlists).head; element != NULL; element = element->next) {
        if(graph->match(vertex, ((AdjList *)(element->data))->vertex))
                break;

        prev = element;
    }

    /* return if the vertex was not found */
    if(element == NULL)
        return -1;

    /* Pass back the adjacency list for the vertex */
    *adjlist = element->data;
    return 0;
}

int grap_is_adjacent(const Graph *graph, const void *vertex_from,
        const void *vertex_to) {
    SListElmt *element, *prev;

    /* locate the adjacency list of the vertex_from */
    for(element = (graph->adjlists).head; element != NULL; element = element->next) {
        if(graph->match(vertex_from, ((AdjList *)(element->data))->vertex))
            break;

        prev = element;
    }

    /* Return if the first vertex was not found */
    if(element == NULL)
        return 0;

    /* return whether the 'vertex_to' is in the adjacency-list of the 'vertex_from' */
    return set_is_member(&((AdjList *)(element->data))->adjacent, vertex_to);
}
