#include "stack.h"

void initStack(StringStack *stack) {
    stack->top = NULL;
    stack->size = 0;
}

int isEmpty(StringStack *stack) {
    return stack->size == 0;
}

void pushStack(StringStack *stack, const char *str) {
    StackNode *newNode = (StackNode *)malloc(sizeof(StackNode));
    if (!newNode) {
        exit(EXIT_FAILURE);
    }
    newNode->data = strdup(str);
    if (!newNode->data) {
        free(newNode);
        exit(EXIT_FAILURE);
    }
    newNode->next = stack->top;
    stack->top = newNode;
    stack->size++;
}

char *popStack(StringStack *stack) {
    if (isEmpty(stack)) {
        return NULL;
    }
    StackNode *temp = stack->top;
    char *data = temp->data;
    stack->top = temp->next;
    free(temp);
    stack->size--;
    return data;
}

char *peekStack(StringStack *stack) {
    if (isEmpty(stack)) {
        return NULL;
    }
    return stack->top->data;
}

void freeStack(StringStack *stack) {
    while (!isEmpty(stack)) {
        char *data = popStack(stack);
        free(data);
    }
}