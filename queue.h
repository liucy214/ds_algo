#ifndef QUEUE_H
#define QUEUE_H

typedef struct _Queue {
    void** data;
    unsigned int capacity;
    unsigned int head;
    unsigned int tail;
    unsigned int size;
    void (*enqueue)(struct _Queue* self, void*);
    void* (*dequeue)(struct _Queue* self);
    int (*isEmpty)(struct _Queue* self);
    int (*isFull)(struct _Queue* self);
    void (*delete)(struct _Queue* self);
} Queue;

Queue* newQueue(unsigned int capacity);
int unitTestQueue(void);
#endif
