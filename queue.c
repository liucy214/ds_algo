#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

static void Queue_enqueue(Queue* self, void* data) {
    if (!self) return;
    if (self->isFull(self)) {
        printf("Queue: %p is full while enqueue\n", self);
        return;
    }
    self->data[self->tail] = data;
    self->tail++;
    if (self->tail == self->capacity) {
        self->tail = 0;
    }
    self->size++;
    return;
}

static void* Queue_dequeue(Queue* self) {
    void* data = NULL;

    if (!self) return NULL;
    if (self->isEmpty(self)) {
        printf("Queue %p: is empty while dequeue\n", self);
        return NULL;
    }
    data = self->data[self->head];
    self->head++;
    if (self->head == self->capacity) {
        self->head = 0;
    }
    self->size--;
    return data;
}

static int Queue_isEmpty(Queue* self) {
    if (!self) return 0;
    return (self->size == 0);
}

static int Queue_isFull(Queue* self) {
    if (!self) return 0;
    return (self->size == self->capacity);
}

static void Queue_delete(Queue* self) {
    if (!self) return;
    free(self->data);
    free(self);
    return;
}

Queue* newQueue(unsigned int capacity) {
    Queue* p = NULL;

    if (capacity == 0) return NULL;
    p = (Queue*)malloc(sizeof(Queue));
    p->data = (void**)malloc(sizeof(void*) * capacity);
    p->capacity = capacity;
    p->head = 0;
    p->tail = 0;
    p->size = 0;
    p->enqueue = Queue_enqueue;
    p->dequeue = Queue_dequeue;
    p->isEmpty = Queue_isEmpty;
    p->isFull = Queue_isFull;
    p->delete = Queue_delete;
    return p;
}

int unitTestQueue(void) {
    Queue* q = NULL;
    int data = 0;

    q = newQueue(10);
    while(!q->isFull(q)) {
        printf("enqueue data:%d\n", data);
        q->enqueue(q, (void*)data++);
    }
    while(!q->isEmpty(q)) {
        printf("dequeue data:%d\n", q->dequeue(q));
    }
    q->delete(q);
    q = NULL;
    return 0;
}
