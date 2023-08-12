Shreyas Telkar
stelkar
Lab 4: Traveling Salesman Problem, Hamiltonian Path

# DESCRIPTION
This lab finds the shortest hamiltonian path using the graph and path methods built. The path uses the stack and graph to push vertices on the the path or pop them if they are connected. It accumulates the total distance of the path whenever it pushes the vertex onto the path. It prints the hamiltonian path based on the vertex connections specified in the graph. Vertecies are represented as city names. Build the program then use option -h to understand how the program is run.
# BUILD
The program can be built using make all and scan build. ** scan build generates a warning bug for possible memory leak but that is taken care of and valgrind returns no leaks.

# OUTPUT
The output prints the shortes hamiltonian path found in the dfs for the graph. It matches the output provided in the binary. It also prints the number of recursions it took to find the path. The number of recursions are also inaccurate for large vertices because it continue to search when the current path is greater than the shortest from before. This is explained in the DESIGN.pdf
# FILES
Unspecified files are both .c/.h files:
stack
path
graph
dfs

tsp.c
vertices.h

Makefile
Diagram.pdf
Writeup.pdf
