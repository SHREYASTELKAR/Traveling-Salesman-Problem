#Credit to Eugene for Makefile in section
CC = clang
CFLAGS = -Wall -Werror -Wpedantic -Wextra

all: tsp

tsp: tsp.o stack.o graph.o path.o dfs.o
	$(CC) -o tsp $^

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f tsp *.o

format:
	clang-format -i -style=file *.c *.h
