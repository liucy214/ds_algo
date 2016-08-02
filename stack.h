#ifndef STACK_H
#define STACK_H

typedef struct _Stack {
    void** data;
    unsigned int capacity;
    unsigned int top;
    void (*push)(struct _Stack* self, void* data);
    void* (*pop)(struct _Stack* self);
    void* (*peek)(struct _Stack* self);
    unsigned int (*size)(struct _Stack* self);
    int (*isEmpty)(struct _Stack* self);
    int (*isFull)(struct _Stack* self);
    void (*delete)(struct _Stack* self);
} Stack;

Stack* newStack(unsigned int capacity);
int unitTestStack(void);
#endif
