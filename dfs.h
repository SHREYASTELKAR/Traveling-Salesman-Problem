#include "graph.h"
#include "path.h"
#include "stack.h"
#include "vertices.h"

#include <stdint.h>
#include <stdio.h>

extern uint64_t num_recursive;

void dfs(
    Graph *G, uint32_t v, Path *curr, Path *shortest, char *cities[], FILE *outfile, bool verbose);
