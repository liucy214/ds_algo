#include <stdio.h>
#include <stdlib.h>
#include "list.h"

static void ListNode_delete(ListNode* self) {
    if (!self) return;
    free(self);
    return;
}

ListNode* newListNode(void* data) {
    ListNode* n = NULL;

    n = (ListNode*) malloc (sizeof(ListNode));
    n->data = data;
    n->next = NULL;
    n->delete = ListNode_delete;
    return n;
}

static void ListIterator_advance(ListIterator* self) {
    if (!self) return;
    if (self->current == NULL) return;
    self->current = self->current->next;
    return;
}

static void ListIterator_delete(ListIterator* self) {
    if (!self) return;
    free(self);
    return;
}

ListIterator* newListIterator(ListNode* node) {
    ListIterator* it = NULL;

    it = (ListIterator*) malloc(sizeof(ListIterator));
    it->current = node;
    it->advance = ListIterator_advance;
    it->delete = ListIterator_delete;
}

static ListIterator* List_begin(List* self) {
    ListIterator* it = NULL;

    if (!self) return NULL;
    it = newListIterator(self->head);
    return it;
}

static ListIterator* List_find(List* self, void* data) {
    ListIterator* it = NULL;
    ListNode* node = NULL;

    if (!self) return NULL;
    node = self->head;
    while (node != NULL && node->data != data) {
        node = node->next;
    }
    if (node) {
        it = newListIterator(node);
    }
    return it;
}

static ListIterator* List_insert(List* self, ListIterator* pos, void* data) {
    ListNode* node = NULL;

    if (!self || !pos) return NULL;

    // insert at empty list
    if (self->head == NULL) {
        self->head = newListNode(data);
        pos->current = self->head;
        return pos;
    }

    // insert at head
    if (self->head == pos->current) {
        node = newListNode(data);
        node->next = self->head;
        self->head = node;
        pos->current = node;
        return pos;
    }

    // find a node before inserted node
    node = self->head;
    while (node != NULL && node->next != pos->current) {
        node = node->next;
    }
    if (node == NULL) {
        printf("List %p: insert at non-existed position\n", self);
        return NULL;
    } else {
        ListNode* newNode = NULL;
        newNode = newListNode(data);
        node->next = newNode;
        newNode->next = pos->current;
        pos->current = newNode;
        return pos;
    }
}

static ListIterator* List_erase(List* self, ListIterator* pos) {
    ListNode* node = NULL;

    if (!self) return NULL;

    // list is empty
    if (self->head == NULL) {
        printf("List %p: erase at empty list\n", self);
        return NULL;
    }

    // erase at out of list
    if (pos->current == NULL) {
        printf("List %p: erase at non-existed position\n", self);
        return NULL;
    }

    // erase at head of list
    if (pos->current == self->head) {
        self->head = self->head->next;
        pos->current->delete(pos->current);
        pos->current = self->head;
    }

    // find a node before erased node
    node = self->head;
    while (node != NULL && node->next != pos->current) {
        node = node->next;
    }
    if (node == NULL) {
        printf("List %p: erase at non-existed position\n", self);
        return NULL;
    } else {
        node->next = pos->current->next;
        pos->current->delete(pos->current);
        pos->current = node->next;
        return pos;
    }
}

static void List_delete(List* self) {
    ListIterator* it = NULL;

    if (!self) return;
    it = self->begin(self);
    while (it->current != NULL) {
        it = self->erase(self, it);
    }
    it->delete(it);
    free(self);
}

List* newList(void) {
    List* list = NULL;
    list = (List*) malloc(sizeof(List));
    list->head = NULL;
    list->begin = List_begin;
    list->find = List_find;
    list->insert = List_insert;
    list->erase = List_erase;
    list->delete = List_delete;
    return list;
}

static void printList(List* list) {
    ListIterator* it = NULL;
    if (!list) return;
    it = list->begin(list);
    printf("Print List %p\n", list);
    while(it->current != NULL) {
        printf("\tList %p: data: %d\n", list, (int)it->current->data);
    it->advance(it);
    }
    it->delete(it);
    return;
}

static void findData(List* list, int data) {
    ListIterator* it = NULL;

    it = list->find(list, (void*)data);
    if (it) {
        printf("found Node: %p with data: %d\n", it->current, (int)it->current->data);
        it->delete(it);
        it = NULL;
    } else {
        printf("not found node with data: %d\n", data);
    }
    return;
}

static void eraseData(List* list, int data) {
    ListIterator* it = NULL;

    it = list->find(list, (void*)data);
    if (it) {
        printf("found node and erased: %p with data: %d\n", it->current, (int)it->current->data);
        list->erase(list, it);
        it->delete(it);
        it = NULL;
    } else {
        printf("not found node with data: %d\n", data);
    }
    return;
}

int unitTestList(void) {
    List* list = NULL;
    ListIterator* it = NULL;
    int data = 0;

    list = newList();

    // erase empty list
    printf("erase empty list\n");
    it = list->begin(list);
    list->erase(list, it);
    it->delete(it);

    // insert
    printf("insert 0~9 into list\n");
    it = list->begin(list);
    for(int i = 0; i < 10; ++ i) {
        it = list->insert(list, it, (void*)data++);
    }
    it->delete(it);
    printList(list);

    // erase 3rd and 4th nodes
    printf("erase 3rd and 4th nodes\n");
    it = list->begin(list);
    it->advance(it);
    it->advance(it);
    it->advance(it);
    it = list->erase(list, it);
    it = list->erase(list, it);
    it->delete(it);
    printList(list);

    // find nodes by data
    printf("find nodes by data\n");
    for(int i = 0; i < 10; ++ i) {
        findData(list, i);
    }

    // find nodes and erase
    printf("find nodes and erase\n");
    for(int i = 3; i < 8; ++ i) {
        eraseData(list, i);
    }

    return 0;
}

