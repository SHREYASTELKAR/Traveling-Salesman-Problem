#include "path.h"

#include "graph.h"
#include "stack.h"
#include "vertices.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

//Credit Eugene and lab doc for psuedocode for path add edge and pop.

struct Path {
    Stack *vertices; //this is the stack for keeping tack of the current path
    uint32_t length; //keeps track of path length when popped or appended to stack
};

Path *path_create(void) {
    Path *p = (Path *) malloc(sizeof(Path)); //constructor
    Stack *vertices = stack_create(VERTICES); //vertices stack created with size 26
    if (p) {
        p->vertices = vertices;
        p->length = 0;
    }
    return p;
}

void path_delete(Path **p) {
    if (*p) {
        stack_delete(&(*p)->vertices); //TA miles provided code for deleting stack
        free(*p); //in path del.
        *p = NULL;
    }
    return;
}

bool path_push_vertex(Path *p, uint32_t v, Graph *G) {
    //stack: [v, vertex], matrix[v][vertex], v is current vertex, p->vertices is the stack.
    uint32_t prev_vert;
    if (stack_size(p->vertices) > 0) { //Psuedocode provided by Eugene
        stack_peek(p->vertices, &prev_vert); //gets the top of path to use for length
        p->length += graph_edge_weight(
            G, prev_vert, v); //increments lenght with curr vertex and next vertex v

        stack_push(p->vertices, v); // pushes next vertex v
        return true;
    }

    else { //if the stack size is empty
        p->length += graph_edge_weight(G, START_VERTEX, v); //do the same with the start_vertex
        stack_push(p->vertices, v);
        return true;
    }
    return false;
}

bool path_pop_vertex(Path *p, uint32_t *v, Graph *G) { //Credit Eugene for pusedocode
    uint32_t prev_vertex;
    if (stack_size(p->vertices) == 0) { //if stack is empty
        return false;
    } else if (stack_size(p->vertices)
               == 1) { //Uses start vertex if there is only 1 element in stack.
        stack_pop(p->vertices, v);
        p->length -= graph_edge_weight(G, START_VERTEX, *v); //decreases length
        return true;
    } else {
        stack_pop(p->vertices, v);
        stack_peek(p->vertices, &prev_vertex); //gets value of value with edge pair
        p->length -= graph_edge_weight(G, prev_vertex, *v);
        return true;
    }
    return false;
}

uint32_t path_vertices(Path *p) {
    return stack_size(p->vertices); //returns size of path stack
}

uint32_t path_length(Path *p) {
    return (p->length); //returns cumulative length
}

void path_copy(Path *dst, Path *src) { //Psuedocode from lab doc
    stack_copy(dst->vertices, src->vertices); //copies stack contents
    dst->length = src->length; //copies path length
}

void path_print(
    Path *p, FILE *outfile, char *cities[]) { //Uses stack print, pusedocode from lab doc
    stack_print(p->vertices, outfile, cities);
}
