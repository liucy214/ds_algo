#ifndef COMPARABLE_OBJECT_H
#define COMPARABLE_OBJECT_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _ComparableObject {
    int (*compareTo)(struct _ComparableObject* self, struct _ComparableObject* to);
    const char* (*toString)(struct _ComparableObject* self);
} ComparableObject;

typedef struct _IntObject {
    ComparableObject base;
    int data;
    char buffer[33];
    void (*delete)(struct _IntObject* self);
} IntObject;

static int IntObject_compareTo(ComparableObject* self, ComparableObject* to) {
    IntObject* _self = (IntObject*)self;
    IntObject* _to = (IntObject*)to;
    if (_self->data > _to->data) return 1;
    else if (_self->data < _to->data) return -1;
    else return 0;
}

static const char* IntObject_toString(ComparableObject* self) {
    IntObject* _self = (IntObject*)self;
    sprintf(_self->buffer, "%d", _self->data);
    return (const char*)_self->buffer;
}

static void IntObject_delete(IntObject* self) {
    if (!self) return;
    free(self);
}

IntObject* newIntObject(int data) {
    IntObject* obj = (IntObject*) malloc(sizeof(IntObject));
    obj->base.compareTo = IntObject_compareTo;
    obj->base.toString = IntObject_toString;
    obj->data = data;
    obj->delete = IntObject_delete;
    return obj;
}
#endif

