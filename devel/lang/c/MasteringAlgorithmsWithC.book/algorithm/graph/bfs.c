#include<stdlib.h>

/* Breadth-First-Search */

#include"bfs.h"
#include"slist/slist.h"
#include"graph.h"
#include"queue/queue.h"

/* graph_algorithm, breadth-first-search */
int bfs(Graph *graph, BfsVertex *start, SList *hops) {
    Queue queue;
    AdjList *adjlist, *clr_adjlist;
    BfsVertex *clr_vertex, *adj_vertex;
    SListElmt *element, *member;

    /* initialize all of the vertices in the graph */
    for(element = (graph->adjlists).head; element != NULL; element = element->next) {
        clr_vertex = ((AdjList *)(element->data))->vertex;
        if(graph->match(clr_vertex, start)) {
            /* Initialize the start vertex */
            clr_vertex->color = VertexColorGray;
            clr_vertex->hops = 0;
        } else {
            /* Initialize vertices other than the start vertex */
            clr_vertex->color = VertexColorWhite;
            clr_vertex->hops = -1;
        }
    }

    /* initialize the queue with the adjacency-list of the start vertex */
    queue_init(&queue, NULL);
    if(graph_adjlist(graph, start, &clr_adjlist)) {
        queue_destroy(&queue);
        return -1;
    }

    if(queue_enqueue(&queue, clr_adjlist)) {
        queue_destroy(&queue);
        return -1;
    }

    /* perform breadth-first search */
    while(queue.size > 0) {
        adjlist = (AdjList *)queue_peek(&queue); /* get the head of queue */

        /* traverse each vertex in the current adjacency list */
        for(member = (adjlist->adjacent).head; member != NULL; member = member->next) {
            /* (Set *)adjacent */
            adj_vertex = (BfsVertex *)member->data;

            /* determine the color of the next adjacent vertex */
            if(graph_adjlist(graph, adj_vertex, &clr_adjlist)) {
                queue_destroy(&queue); /* process error */
                return -1;
            }
            clr_vertex = (BfsVertex *)clr_adjlist->vertex;

            /* turn each white-vertex gray and enqueue its adjacency-list */
            if(clr_vertex->color == VertexColorWhite) {
                clr_vertex->color = VertexColorGray;
                clr_vertex->hops = ((BfsVertex *)adjlist->vertex)->hops + 1;

                if(queue_enqueue(&queue, clr_adjlist)) {
                    queue_destroy(&queue);
                    return -1; /* process error */
                }
            }
        }

        /* dequeue the current adjacency-list and color its vertex black */
        if(queue_dequeue(&queue, (void **)&adjlist) == 0)
            ((BfsVertex *)adjlist->vertex)->color = VertexColorBlack;
        else { /* failed to dequeue, process error */
            queue_destroy(&queue);
            return -1;
        }
    }

    queue_destroy(&queue);

    /* Pass back the hop count for each vertex in a list */
    slist_init(hops, NULL);

    for(element = (graph->adjlists).head; element != NULL; element = element->next) {
        /*
         * skip vertices that were not visited
         * (those with 'hop' counts of -1)
         */
        clr_vertex = ((AdjList *)(element->data))->vertex;
        if(clr_vertex->hops != -1) {
            if(slist_ins_next(hops, hops->tail, clr_vertex)) {
                slist_destroy(hops);
                return -1;
                /* failed to insert into the output-parameter
                 * process error */
            }
        }
    }

    return 0;
}
