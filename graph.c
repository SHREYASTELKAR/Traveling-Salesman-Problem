#include "graph.h"

#include "vertices.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

//Credit Eugene for providing psuedocode for main graph functions used. Also used lab doc
//psuedocode on graph functions.

struct Graph {
    uint32_t vertices; //number of vertices
    bool undirected; //Checks if undirected
    uint32_t visited[VERTICES]; //Checks if vertex is visited
    uint32_t matrix[VERTICES][VERTICES]; //matrix containing weights
};

Graph *graph_create(uint32_t vertices, bool undirected) {
    Graph *G = (Graph *) malloc(sizeof(Graph)); //constructor
    if (G) {
        G->vertices = vertices; //num of vertecies read from top of the input file.
        G->undirected = undirected;
        for (uint32_t i = 0; i < VERTICES; i += 1) { //initializes all vertecies as not visited
            G->visited[i] = false;
        }

        for (uint64_t rows = 0; rows < VERTICES;
             rows += 1) { //Credit to Eugene for providing sudocode for this.
            for (uint64_t columns = 0; columns < VERTICES;
                 columns += 1) { //initializes matrix values all 0
                G->matrix[rows][columns] = 0;
            }
        }
    }
    return G;
}

void graph_delete(Graph **G) {
    if (*G) {
        free(*G);
        *G = NULL;
    }
    return;
}

uint32_t graph_vertices(Graph *G) {
    return (G->vertices); //Read from first line in graph input
}

bool graph_add_edge(Graph *G, uint32_t i, uint32_t j, uint32_t k) {
    G->matrix[i][j] = k; //Set specified edge weight on matrix, from input file.

    if (G->undirected == true) { //If graph is undirected, specified in opt
        G->matrix[j][i] = k; //set the diagonal as same edge weight
    }

    //if i and j are in bounds and edge successfully addded, return true
    if (i <= G->vertices && i >= START_VERTEX && j <= G->vertices && j >= START_VERTEX
        && (G->matrix[i][j] == k)) {
        if (G->undirected == true) {
            if (G->matrix[j][i] == k) {
                return true;
            } else {
                return false;
            }
        } else {
            return true;
        }
    } else {
        return false;
    }
}

bool graph_has_edge(
    Graph *G, uint32_t i, uint32_t j) { //if there is a positive edge at the vertices.
    return (i <= G->vertices && i >= START_VERTEX && j <= G->vertices && j >= START_VERTEX
            && G->matrix[i][j] > 0);
}

uint32_t graph_edge_weight(Graph *G, uint32_t i, uint32_t j) {
    if (graph_has_edge(G, i, j) == false) {
        return 0;
    } else {
        return (G->matrix[i][j]); //get the edge weight at matrix
    }
}

bool graph_visited(Graph *G, uint32_t v) { //check visited array.
    return (G->visited[v]);
}

void graph_mark_visited(Graph *G, uint32_t v) { //In visited array, mark vertex as visited
    if (v >= START_VERTEX && v <= G->vertices) {
        G->visited[v] = true;
    }
    return;
}

void graph_mark_unvisited(Graph *G, uint32_t v) { //In visited array, mark vertex as unvisited
    if (v >= START_VERTEX && v <= G->vertices) {
        G->visited[v] = false;
    }
    return;
}

void graph_print(Graph *G) { //prints out the graph in nested rows and cloumns loop
    printf("[");
    for (uint64_t row = 0; row < VERTICES; row += 1) {
        for (uint64_t column = 0; column < VERTICES; column += 1) {
            printf("%d, ", G->matrix[row][column]);
        }
        printf("\n");
    }
    printf("]\n");
}
