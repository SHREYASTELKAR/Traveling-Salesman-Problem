#include "dfs.h"
#include "graph.h"
#include "path.h"
#include "stack.h" //header files
#include "vertices.h"

#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h> //for reading input
#include <unistd.h> //for getopt

//Credit Eugene for psuedocode for how to read the file for values and city names.

#define BLOCK   1024 //Block used by buffer for fgets
#define OPTIONS "hvui:o:" //command line options for getopt

int main(int argc, char **argv) {
    int opt;
    uint32_t i, j, k; // vertices and weight
    int c; // for fscan
    int ci; // for fscan
    uint32_t vertices = 1; //intial value for num of vert
    uint32_t vert; //temp value for vertices
    bool verbose = false; //Initializes verbose option as false
    bool undirected = false; //Initialize undirected option as false
    char buffer[BLOCK]; //Used for fgets for city names

    FILE *input_file = stdin; //default input file option
    FILE *output_file = stdout; //default output file option
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'h': //print help message
            printf("SYNOPSIS\n");
            printf("  Traveling Salesman Problem using DFS.\n");
            printf("\n");
            printf("USAGE\n");
            printf("  ./tsp [-u] [-v] [-h] [-i infile] [-o outfile]\n");
            printf("\n");
            printf("OPTIONS\n");
            printf("  -u             Use undirected graph.\n");
            printf("  -v             Enable verbose printing.\n");
            printf("  -h             Program usage and help.\n");
            printf("  -i infile      Input containing graph (default: stdin)\n");
            printf("  -o outfile     Output of computed path (default: stdout)\n");
            return 1;
            break;
        case 'v':
            //print all, print shortest one twice, should be normal print
            verbose = true;
            break;
        case 'u':
            //undirected sets the graph diagonals as the same edge
            undirected = true;
            break;
        case 'i':
            //open file
            input_file = fopen(optarg, "r");
            break;
        case 'o':
            //open file
            output_file = fopen(optarg, "w");
            break;
        }
    }
    //Errors for invalid file
    if (input_file == NULL) {
        fprintf(stderr, "failed to open file");
        return 1;
    }

    if (output_file == NULL) {
        fprintf(stderr, "failed to open file");
        return 1;
    }

    //Scans for the vertex in the first line, psuedocode from Eugene
    while ((ci = fscanf(input_file, "%d", &vert)) != EOF) {
        if (ci != 1) {
            break;
        } else {
            vertices = vert; //Sets the value to vertices
        }
    }

    char *citi[vertices]; //array of cities
    for (uint32_t ind = 0; ind < vertices; ind += 1) { //code from Eugene's section.
        fgets(buffer, BLOCK, input_file); //gets value into buffer
        citi[ind] = strdup(buffer); //makes a copy of it with strdup into the array
        citi[ind][strlen(citi[ind]) - 1] = '\0'; //gets rid of the newline
    }

    Graph *Gr = graph_create(vertices, undirected); //num of vertices from first line
    Path *current = path_create(); //creates a current path for dfs
    Path *shorte = path_create(); // shortest path

    //*For getting graph add values:, code from Eugene's section.
    while ((c = fscanf(input_file, "%d %d %d\n", &i, &j, &k)) != EOF) {
        if (c != 3) {
            fprintf(output_file, "Error: malformed number of vertices.\n");
            fclose(output_file);
            return 1;
            break;
        } else {
            graph_add_edge(Gr, i, j, k); //adds to the matrix after reading
        }
    }

    dfs(Gr, START_VERTEX, current, shorte, citi, output_file,
        verbose); //calls dfs with set parameters

    //For printing full shortest path
    if (path_length(shorte) != 0) {
        fprintf(output_file, "Path length: %d\n", path_length(shorte));
        fprintf(output_file, "Path: %s -> ", citi[START_VERTEX]);
        path_print(shorte, output_file, citi);
        fprintf(output_file, "Total recursive calls: %lu\n",
            num_recursive); //prints out num of recursions.
    } else {
        fprintf(output_file, "There's nowhere to go\n"); //if the path length == 0, Error
    }

    //free used space
    fclose(input_file);

    for (uint32_t in = 0; in < vertices; in += 1) { //free array, given in Eugene's section
        free(citi[in]);
    }
    path_delete(&current);
    path_delete(&shorte);
    graph_delete(&Gr);

    return 0;
}
