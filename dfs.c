#include "dfs.h" //include header file with extern var

#include "graph.h"
#include "path.h"
#include "stack.h"
#include "vertices.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

//Dfs psuedocode given in lab doc, credit Eugene for help to check if hamiltonian path.

//extern var for recursive counts
uint64_t num_recursive = 0;
//bool larger = false;

void dfs(
    Graph *G, uint32_t v, Path *curr, Path *shortest, char *cities[], FILE *outfile, bool verbose) {
    num_recursive += 1;
    uint32_t pop_zero = 0; //origin used to pop/push for hamiltonian paths

    graph_mark_visited(G, v); //mark current vertex

    for (uint32_t w = 0; w < graph_vertices(G);
         w += 1) { //breaks out of loop when cant find vertex to dfs to
        if (graph_has_edge(G, v, w) == true) {
            if (graph_visited(G, w) == false) {
                path_push_vertex(curr, w, G); //push current vertex onto path
                dfs(G, w, curr, shortest, cities, outfile, verbose); //call dfs for next path
                path_pop_vertex(curr, &w, G);
            }
        }
    }

    graph_mark_unvisited(G, v); //marked unvisited for other possible paths after no paths found.

    if (path_vertices(curr) == (graph_vertices(G)) - 1) { //is hamiltonian
        if (graph_has_edge(G, v, START_VERTEX)) {
            path_push_vertex(curr, START_VERTEX, G); //path to origin

            //print
            if (path_vertices(shortest) == 0) { //if there is no shortest saved yet.
                path_copy(shortest, curr);
                if (verbose == true) { //only print if verbose option presented
                    fprintf(outfile, "Path length: %d\n", path_length(curr));
                    fprintf(outfile, "Path: %s -> ", cities[START_VERTEX]);
                    path_print(shortest, outfile, cities);
                }

            }

            else if (path_length(curr) < path_length(shortest)) { //if shorter path found
                path_copy(shortest, curr);
                if (verbose == true) {
                    fprintf(outfile, "Path length: %d\n", path_length(curr));
                    fprintf(outfile, "Path: %s -> ", cities[START_VERTEX]);
                    path_print(shortest, outfile, cities);
                }
            }
            //else if (path_length(curr) >= path_length(shortest)) {
            //larger = true;
            //}

            path_pop_vertex(curr, &pop_zero, G);

            //Remove path to origin after copying, return to dfs
        }
    }
}
