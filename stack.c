#include "stack.h" //include header file

#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

//Credit Sahiti and Eugene for providing Stack struct code in section.
//Also used psuedocode for stack peek, print, and copy in lab doc.

struct Stack {
    uint32_t top;
    uint32_t capacity;
    int64_t *items;
};

Stack *stack_create(uint32_t capacity) {
    Stack *s = (Stack *) malloc(sizeof(Stack)); //constructor
    if (s) {
        s->top = 0;
        s->capacity = capacity;
        s->items = (int64_t *) calloc(capacity, sizeof(int64_t)); //typecasts memory for items.
        if (!s->items) {
            free(s);
            s = NULL;
        }
    }
    return s;
}

void stack_delete(Stack **s) {
    if (*s && (*s)->items) {
        free((*s)->items);
        free(*s);
        *s = NULL;
    }
    return;
}

bool stack_empty(Stack *s) { //top is the index of the next element to be pushed
    return (s->top == 0);
}

bool stack_full(Stack *s) {
    return (s->top == s->capacity); // capcity is the max size, specified as n for the array
}

uint32_t stack_size(Stack *s) {
    return (s->top);
}

bool stack_push(Stack *s, uint32_t x) {
    if (s->top == s->capacity) { //if stack is full
        return false;
    }
    s->items[s->top] = x; //push x into top location
    s->top += 1; // increment it for next push
    return true;
}

bool stack_peek(Stack *s, uint32_t *x) {
    if (s->top == 0) { //if stack is empty
        return false;
    }
    s->top -= 1; //make top point to the top of the stack
    *x = s->items[s->top]; //get the value from the top
    s->top += 1; //not popping so increment for next value
    return true;
}

bool stack_pop(Stack *s, uint32_t *x) {
    if (s->top == 0) { // if stack is empty
        return false;
    }
    s->top -= 1; // decrease top to point to last pushed
    *x = s->items[s->top]; // store it to x
    return true;
}

void stack_copy(Stack *dst, Stack *src) {
    for (uint32_t i = 0; i < src->top; i += 1) {
        dst->items[i] = src->items[i]; //copy all values in stack
    }

    dst->top = src->top;
}

void stack_print(Stack *s, FILE *outfile,
    char *cities[]) { //print the stack, used by path, print given in lab doc.
    for (uint32_t i = 0; i < s->top; i += 1) {
        fprintf(outfile, "%s", cities[s->items[i]]);
        if (i + 1 != s->top) {
            fprintf(outfile, " -> ");
        }
    }
    fprintf(outfile, "\n");
}
