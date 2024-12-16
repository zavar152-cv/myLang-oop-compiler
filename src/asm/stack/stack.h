#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct StackNode {
    char *data;
    struct StackNode *next;
} StackNode;

typedef struct {
    StackNode *top;
    size_t size;
} StringStack;

void initStack(StringStack *stack);

int isEmpty(StringStack *stack);

void pushStack(StringStack *stack, const char *str);

char *popStack(StringStack *stack);

char *peekStack(StringStack *stack);

void freeStack(StringStack *stack);