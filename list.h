#ifndef LIST_H
#define LIST_H

typedef struct _ListNode {
    void* data;
    struct _ListNode* next;
    void (*delete) (struct _ListNode* self);
} ListNode;

ListNode* newListNode(void* data);

typedef struct _ListIterator {
    ListNode* current;
    void (*advance) (struct _ListIterator* self);
    void (*delete) (struct _ListIterator* self);
} ListIterator;

ListIterator* newListIterator(ListNode* node);

typedef struct _List {
    ListNode* head;

    ListIterator* (*begin)(struct _List* self);
    ListIterator* (*find)(struct _List* self, void* data);
    ListIterator* (*insert)(struct _List* self, ListIterator* pos, void* data);
    ListIterator* (*erase)(struct _List* self, ListIterator* pos);
    void (*delete)(struct _List* self);
} List;

List* newList(void);

int unitTestList(void);
#endif
