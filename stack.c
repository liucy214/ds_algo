#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

static void push(Stack* self, void* data) {
    if (!self) return;
    if (self->isFull(self)) {
        printf("Stack %p: is full while push\n", self);
        return;
    }
    self->data[self->top] = data;
    self->top++;
    return;
}

static void* pop(Stack* self) {
    void* data = NULL;

    if (!self) return NULL;
    if (self->isEmpty(self)) {
        printf("Stack %p: is empty while pop\n", self);
        return NULL;
    }
    data = self->data[self->top-1];
    self->top--;
    return data;
}

static void* peek(Stack* self) {
    if (!self) return NULL;
    if (self->isEmpty(self)) {
        return NULL;
    }
    return self->data[self->top-1];
}

static unsigned int size(Stack* self) {
    if (!self) return 0;
    return self->top;
}

static int isEmpty(Stack* self) {
    if (!self) return 0;
    return (self->top == 0);
}

static int isFull(Stack* self) {
    if (!self) return 0;
    return (self->top == self->capacity);
}

static void delete(Stack* self) {
    if (!self) return;
    free(self->data);
    free(self);
    return;
}

Stack* newStack(unsigned int capacity) {
    Stack* s = NULL;

    if (capacity == 0) return NULL;
    s = (Stack*)malloc(sizeof(Stack));
    s->data = (void**)malloc(sizeof(void*)*capacity);
    s->capacity = capacity;
    s->top = 0;
    s->push = push;
    s->pop = pop;
    s->peek = peek;
    s->size = size;
    s->isEmpty = isEmpty;
    s->isFull = isFull;
    s->delete = delete;
    return s;
}

int unitTestStack(void) {
    Stack* s = NULL;
    int data = 0;

    s = newStack(10);
    while(!s->isFull(s)) {
        printf("push %d\n", data);
        s->push(s, (void*)data++);
    }
    while(!s->isEmpty(s)) {
        printf("pop %d\n", (int)s->pop(s));
    }
    s->delete(s);
    s = NULL;
    return 0;
}

