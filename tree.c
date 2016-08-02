#include <stdio.h>
#include <stdlib.h>

#include "comparable_object.h"
#include "tree.h"
#include "stack.h"
#include "queue.h"

static void BinaryTreeNode_delete(BinaryTreeNode* self) {
    if (!self) return;
    free(self);
}

BinaryTreeNode* newBinaryTreeNode(void* data) {
    BinaryTreeNode* node = NULL;

    node = (BinaryTreeNode*) malloc (sizeof(BinaryTreeNode));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    node->delete = BinaryTreeNode_delete;
    return node;
}

static BinaryTreeNode* BinarySearchTree_find(BinarySearchTree* self, void* data) {
    BinaryTreeNode* node = NULL;
    ComparableObject* obj = NULL;

    if (!self) return NULL;
    node = self->findSubTree(self->root, data);
    obj = (ComparableObject*) data;
    if (node) {
        printf("BinarySearchTree %p: found node %p by data: %s\n", self, node, obj->toString(obj));
    } else {
        printf("BinarySearchTree %p: not found node by data: %s\n", self, obj->toString(obj));
    }
    return node;
}

static BinaryTreeNode* BinarySearchTree_findMin(BinarySearchTree* self) {
    if (!self) return NULL;
    return self->findMinSubTree(self->root);
}

static BinaryTreeNode* BinarySearchTree_findMax(BinarySearchTree* self) {
    if (!self) return NULL;
    return self->findMaxSubTree(self->root);
}

static void BinarySearchTree_insert(BinarySearchTree* self, void* data) {
    ComparableObject* obj = NULL;

    if (!self) return;
    obj = (ComparableObject*) data;
    printf("BinarySearchTree %p: insert data: %s\n", self, obj->toString(obj));
    if (self->AVL) {
        self->root = self->insertSubTreeAVL(self->root, data);
    } else {
        self->root = self->insertSubTree(self->root, data);
    }
}

static void BinarySearchTree_remove(BinarySearchTree* self, void* data) {
    ComparableObject* obj = NULL;

    if (!self) return;
    obj = (ComparableObject*) data;
    printf("BinarySearchTree %p: remove data: %s\n", self, obj->toString(obj));
    if (self->AVL) {
        self->root = self->removeSubTreeAVL(self->root, data);
    } else {
        self->root = self->removeSubTree(self->root, data);
    }
}

static void BinarySearchTree_delete(BinarySearchTree* self) {
    if (!self) return;
    self->deleteSubTree(self->root);
    free(self);
}

static void BinarySearchTree_printPreOrder(BinarySearchTree* self) {
    if (!self) return;
    printf("BinarySearchTree %p: preorder traversal\n", self);
    self->printPreOrderSubTree(self->root);
}

static void BinarySearchTree_printInOrder(BinarySearchTree* self) {
    if (!self) return;
    printf("BinarySearchTree %p: inorder traversal\n", self);
    self->printInOrderSubTree(self->root);
}

static void BinarySearchTree_printPostOrder(BinarySearchTree* self) {
    if (!self) return;
    printf("BinarySearchTree %p: postorder traversal\n", self);
    self->printPostOrderSubTree(self->root);
}

static void BinarySearchTree_printBFS(BinarySearchTree* self) {
    Queue* queue = NULL;
    BinaryTreeNode* node = NULL;

    if (!self) return;
    printf("BinarySearchTree %p: BFS traversal\n", self);
    queue = newQueue(512);
    queue->enqueue(queue, (void*)self->root);
    while(!queue->isEmpty(queue)) {
        node = (BinaryTreeNode*)queue->dequeue(queue);
        if (node) {
            ComparableObject* obj = (ComparableObject*)node->data;
            printf("BinaryTreeNode %p with data: %s\n", node, obj->toString(obj));
            queue->enqueue(queue, (void*)node->left);
            queue->enqueue(queue, (void*)node->right);
        }
    }
    queue->delete(queue);
}

static void BinarySearchTree_printPreOrderByStack(BinarySearchTree* self) {
    Stack* stack = NULL;
    BinaryTreeNode* node = NULL;

    if (!self) return;
    printf("BinarySearchTree %p: preorder traversal by stack\n", self);
    stack = newStack(512);
    stack->push(stack, (void*)self->root);
    while(!stack->isEmpty(stack)) {
        node = (BinaryTreeNode*) stack->pop(stack);
        if (node) {
            ComparableObject* obj = (ComparableObject*)node->data;
            printf("BinaryTreeNode %p: with data: %s\n", node, obj->toString(obj));
            stack->push(stack, (void*)node->right);
            stack->push(stack, (void*)node->left);
        }
    }
    stack->delete(stack);
}

static void BinarySearchTree_printInOrderByStack(BinarySearchTree* self) {
    Stack* stack = NULL;
    BinaryTreeNode* node = NULL;
    ComparableObject* obj = NULL;

    if (!self) return;
    printf("BinarySearchTree %p: inorder traversal by stack\n", self);
    stack = newStack(512);
    node = self->root;
    if (node) {
        stack->push(stack, (void*)node);
    }
    while (!stack->isEmpty(stack)) {
        while (node != NULL) {
            node = node->left;
            if (node) {
                stack->push(stack, (void*)node);
            }
        }
        node = (BinaryTreeNode*)stack->pop(stack);
        obj = (ComparableObject*)node->data;
        printf("BinaryTreeNode %p: with data: %s\n", node, obj->toString(obj));
        node = node->right;
        if (node) {
            stack->push(stack, (void*)node);
        }
    }
    stack->delete(stack);
}

static void BinarySearchTree_printPostOrderByStack(BinarySearchTree* self) {
    Stack* stack1 = NULL;
    Stack* stack2 = NULL;
    BinaryTreeNode* node = NULL;

    if (!self) return;
    printf("BinarySearchTree %p: postorder traversal by stack\n", self);
    stack1 = newStack(512);
    stack2 = newStack(512);
    stack1->push(stack1, (void*)self->root);
    while(!stack1->isEmpty(stack1)) {
        node = (BinaryTreeNode*) stack1->pop(stack1);
        if (node) {
            stack2->push(stack2, (void*)node);
            stack1->push(stack1, (void*)node->left);
            stack1->push(stack1, (void*)node->right);
        }
    }
    while(!stack2->isEmpty(stack2)) {
        ComparableObject* obj = NULL;
        node = (BinaryTreeNode*) stack2->pop(stack2);
        obj = (ComparableObject*)node->data;
        printf("BinaryTreeNode %p: with data: %s\n", node, obj->toString(obj));
    }
    stack1->delete(stack1);
    stack2->delete(stack2);
}

static int BinarySearchTree_getHeight(BinarySearchTree* self) {
    int height = 0;

    if (!self) return 0;
    height = self->getHeightSubTree(self->root);
    printf("BinarySearchTree %p: height: %d\n", self, height);
    return height;
}

static BinaryTreeNode* BinarySearchTree_findSubTree(BinaryTreeNode* root, void* data) {
    ComparableObject* obj = NULL;
    ComparableObject* rootObj = NULL;

    if (!root) return NULL;
    obj = (ComparableObject*)data;
    rootObj = (ComparableObject*)root->data;
    if (rootObj->compareTo(rootObj, obj) > 0) {
        return BinarySearchTree_findSubTree(root->left, data);
    } else if (rootObj->compareTo(rootObj, obj) < 0) {
        return BinarySearchTree_findSubTree(root->right, data);
    } else {
        return root;
    }
}

static BinaryTreeNode* BinarySearchTree_findMinSubTree(BinaryTreeNode* root) {
    BinaryTreeNode* minNode = NULL;

    if (!root) return NULL;
    minNode = root;
    while(minNode->left) {
        minNode = minNode->left;
    }
    return minNode;
}

static BinaryTreeNode* BinarySearchTree_findMaxSubTree(BinaryTreeNode* root) {
    BinaryTreeNode* maxNode = NULL;

    if (!root) return NULL;
    maxNode = root;
    while(maxNode->right) {
        maxNode = maxNode->right;
    }
    return maxNode;
}

static int BinarySearchTree_getHeightSubTree(BinaryTreeNode* root) {
    int leftHeight = 0;
    int rightHeight = 0;

    if (!root) return -1;
    leftHeight = BinarySearchTree_getHeightSubTree(root->left) + 1;
    rightHeight = BinarySearchTree_getHeightSubTree(root->right) + 1;
    return leftHeight >= rightHeight ? leftHeight : rightHeight;
}

static BinaryTreeNode* BinarySearchTree_singleRotateLeftChildSubTree(BinaryTreeNode* root) {
    // left-left rotation
    BinaryTreeNode* left = NULL;

    printf("BinarySearchTree %p: AVL left-left single rotation\n", root);
    left = root->left;
    root->left = left->right;
    left->right = root;
    return left;
}

static BinaryTreeNode* BinarySearchTree_singleRotateRightChildSubTree(BinaryTreeNode* root) {
    // right-right rotation
    BinaryTreeNode* right = NULL;

    printf("BinarySearchTree %p: AVL right-right single rotation\n", root);
    right = root->right;
    root->right = right->left;
    right->left = root;
    return right;
}

static BinaryTreeNode* BinarySearchTree_doubleRotateLeftChildSubTree(BinaryTreeNode* root) {
    // right-left rotation
    BinaryTreeNode* right = NULL;
    BinaryTreeNode* right_left = NULL;

    printf("BinarySearchTree %p: AVL right-left double rotation\n", root);
    right = root->right;
    right_left = right->left;
    root->right = right_left->left;
    right->left = right_left->right;
    right_left->left = root;
    right_left->right = right;
    return right_left;
}

static BinaryTreeNode* BinarySearchTree_doubleRotateRightChildSubTree(BinaryTreeNode* root) {
    // left-right rotation
    BinaryTreeNode* left = NULL;
    BinaryTreeNode* left_right = NULL;

    printf("BinarySearchTree %p: AVL left-right double rotation\n", root);
    left = root->left;
    left_right = left->right;
    root->left = left_right->right;
    left->right = left_right->left;
    left_right->left = left;
    left_right->right = root;
    return left_right;
}


static BinaryTreeNode* BinarySearchTree_insertSubTree(BinaryTreeNode* root, void* data) {
    if (!root) {
        root = newBinaryTreeNode(data);
        printf("BinaryTreeNode %p inserted\n", root);
    } else {
        ComparableObject* obj = (ComparableObject*)data;
        ComparableObject* rootObj = (ComparableObject*)root->data;
        if (rootObj->compareTo(rootObj, obj) > 0) {
            root->left = BinarySearchTree_insertSubTree(root->left, data);
        } else if (rootObj->compareTo(rootObj, obj) < 0) {
            root->right = BinarySearchTree_insertSubTree(root->right, data);
        }
    }
    return root;
}

static BinaryTreeNode* BinarySearchTree_insertSubTreeAVL(BinaryTreeNode* root, void* data) {
    if (!root) {
        root = newBinaryTreeNode(data);
        printf("BinaryTreeNode %p inserted\n", root);
    } else {
        ComparableObject* obj = (ComparableObject*)data;
        ComparableObject* rootObj = (ComparableObject*)root->data;
        if (rootObj->compareTo(rootObj, obj) > 0) {
            root->left = BinarySearchTree_insertSubTreeAVL(root->left, data);
            if (BinarySearchTree_getHeightSubTree(root->left) - BinarySearchTree_getHeightSubTree(root->right) == 2) {
                ComparableObject* leftObj = (ComparableObject*)root->left->data;
                if (leftObj->compareTo(leftObj, obj) > 0) { // left-left
                    root = BinarySearchTree_singleRotateLeftChildSubTree(root);
                } else { // left-right
                    root = BinarySearchTree_doubleRotateRightChildSubTree(root);
                }
            }
        } else if (rootObj->compareTo(rootObj, obj) < 0) {
            root->right = BinarySearchTree_insertSubTreeAVL(root->right, data);
            if (BinarySearchTree_getHeightSubTree(root->right) - BinarySearchTree_getHeightSubTree(root->left) == 2) {
                ComparableObject* rightObj = (ComparableObject*)root->right->data;
                if (rightObj->compareTo(rightObj, obj) < 0) { // right-right
                    root = BinarySearchTree_singleRotateRightChildSubTree(root);
                } else { // right-left
                    root = BinarySearchTree_doubleRotateLeftChildSubTree(root);
                }
            }
        }
    }
    return root;
}

static BinaryTreeNode* BinarySearchTree_removeSubTree(BinaryTreeNode* root, void* data) {
    ComparableObject* obj = NULL;
    ComparableObject* rootObj = NULL;

    if (!root) return NULL;
    obj = (ComparableObject*)data;
    rootObj = (ComparableObject*)root->data;
    if (rootObj->compareTo(rootObj, obj) > 0) {
        root->left = BinarySearchTree_removeSubTree(root->left, data);
    } else if (rootObj->compareTo(rootObj, obj) < 0) {
        root->right = BinarySearchTree_removeSubTree(root->right, data);
    } else {
        if (root->left && !root->right) {
            BinaryTreeNode* tmp = root->left;
            root->delete(root);
            root = tmp;
        } else if (!root->left && root->right) {
            BinaryTreeNode* tmp = root->right;
            root->delete(root);
            root = tmp;
        } else if (!root->left && !root->right) {
            root->delete(root);
            root = NULL;
        } else {
            void* tmp = NULL;
            BinaryTreeNode* minInRight = NULL;

            // find min node in right subtree and swap it with root
            minInRight = BinarySearchTree_findMinSubTree(root->right);
            tmp = root->data;
            root->data = minInRight->data;
            minInRight->data = tmp;

            // remove the leaf node
            root->right = BinarySearchTree_removeSubTree(root->right, minInRight->data);
        }
    }
    return root;
}

static BinaryTreeNode* BinarySearchTree_removeSubTreeAVL(BinaryTreeNode* root, void* data) {
    ComparableObject* obj = NULL;
    ComparableObject* rootObj = NULL;

    if (!root) return NULL;
    obj = (ComparableObject*)data;
    rootObj = (ComparableObject*)root->data;
    if (rootObj->compareTo(rootObj, obj) > 0) {
        root->left = BinarySearchTree_removeSubTreeAVL(root->left, data);
        if (BinarySearchTree_getHeightSubTree(root->right) - BinarySearchTree_getHeightSubTree(root->left) == 2) {
            if (BinarySearchTree_getHeightSubTree(root->right->right) >= BinarySearchTree_getHeightSubTree(root->right->left)) {
                // right-right
                root = BinarySearchTree_singleRotateRightChildSubTree(root);
            } else {
                // right-left
                root = BinarySearchTree_doubleRotateLeftChildSubTree(root);
            }
        }
    } else if (rootObj->compareTo(rootObj, obj) < 0) {
        root->right = BinarySearchTree_removeSubTreeAVL(root->right, data);
        if (BinarySearchTree_getHeightSubTree(root->left) - BinarySearchTree_getHeightSubTree(root->right) == 2) {
            if (BinarySearchTree_getHeightSubTree(root->left->left) >= BinarySearchTree_getHeightSubTree(root->left->right)) {
                // left-left
                root = BinarySearchTree_singleRotateLeftChildSubTree(root);
            } else {
                // left-right
                root = BinarySearchTree_doubleRotateRightChildSubTree(root);
            }
        }
    } else {
        if (root->left && !root->right) {
            BinaryTreeNode* tmp = root->left;
            root->delete(root);
            root = tmp;
        } else if (!root->left && root->right) {
            BinaryTreeNode* tmp = root->right;
            root->delete(root);
            root = tmp;
        } else if (!root->left && !root->right) {
            root->delete(root);
            root = NULL;
        } else {
            void* tmp = NULL;
            BinaryTreeNode* minInRight = NULL;

            // find min node in right subtree and swap it with root
            minInRight = BinarySearchTree_findMinSubTree(root->right);
            tmp = root->data;
            root->data = minInRight->data;
            minInRight->data = tmp;

            // remove the leaf node
            root->right = BinarySearchTree_removeSubTree(root->right, minInRight->data);
        }
    }
    return root;
}

static void BinarySearchTree_deleteSubTree(BinaryTreeNode* root) {
    if (!root) return;
    // postorder traversal
    BinarySearchTree_deleteSubTree(root->left);
    BinarySearchTree_deleteSubTree(root->right);
    root->delete(root);
}

static void BinarySearchTree_printPreOrderSubTree(BinaryTreeNode* root) {
    ComparableObject* obj = NULL;
    if (!root) return;
    obj = (ComparableObject*)root->data;
    printf("BinaryTreeNode %p: data: %s\n", root, obj->toString(obj));
    BinarySearchTree_printPreOrderSubTree(root->left);
    BinarySearchTree_printPreOrderSubTree(root->right);
}

static void BinarySearchTree_printInOrderSubTree(BinaryTreeNode* root) {
    ComparableObject* obj = NULL;
    if (!root) return;
    BinarySearchTree_printInOrderSubTree(root->left);
    obj = (ComparableObject*)root->data;
    printf("BinaryTreeNode %p: data: %s\n", root, obj->toString(obj));
    BinarySearchTree_printInOrderSubTree(root->right);
}

static void BinarySearchTree_printPostOrderSubTree(BinaryTreeNode* root) {
    ComparableObject* obj = NULL;
    if (!root) return;
    BinarySearchTree_printPostOrderSubTree(root->left);
    BinarySearchTree_printPostOrderSubTree(root->right);
    obj = (ComparableObject*)root->data;
    printf("BinaryTreeNode %p: data: %s\n", root, obj->toString(obj));
}

BinarySearchTree* newBinarySearchTree(void) {
    BinarySearchTree* tree = NULL;

    tree = (BinarySearchTree*) malloc (sizeof(BinarySearchTree));
    tree->root = NULL;
    tree->AVL = 0;

    tree->find = BinarySearchTree_find;
    tree->findMin = BinarySearchTree_findMin;
    tree->findMax = BinarySearchTree_findMax;
    tree->insert = BinarySearchTree_insert;
    tree->remove = BinarySearchTree_remove;
    tree->delete = BinarySearchTree_delete;
    tree->printPreOrder = BinarySearchTree_printPreOrder;
    tree->printInOrder = BinarySearchTree_printInOrder;
    tree->printPostOrder = BinarySearchTree_printPostOrder;
    tree->printBFS = BinarySearchTree_printBFS;
    tree->printPreOrderByStack = BinarySearchTree_printPreOrderByStack;
    tree->printInOrderByStack = BinarySearchTree_printInOrderByStack;
    tree->printPostOrderByStack = BinarySearchTree_printPostOrderByStack;
    tree->getHeight = BinarySearchTree_getHeight;

    tree->findSubTree = BinarySearchTree_findSubTree;
    tree->findMinSubTree = BinarySearchTree_findMinSubTree;
    tree->findMaxSubTree = BinarySearchTree_findMaxSubTree;
    tree->insertSubTree = BinarySearchTree_insertSubTree;
    tree->insertSubTreeAVL = BinarySearchTree_insertSubTreeAVL;
    tree->removeSubTree = BinarySearchTree_removeSubTree;
    tree->removeSubTreeAVL = BinarySearchTree_removeSubTreeAVL;
    tree->singleRotateLeftChildSubTree = BinarySearchTree_singleRotateLeftChildSubTree;
    tree->singleRotateRightChildSubTree = BinarySearchTree_singleRotateRightChildSubTree;
    tree->doubleRotateLeftChildSubTree = BinarySearchTree_doubleRotateLeftChildSubTree;
    tree->doubleRotateRightChildSubTree = BinarySearchTree_doubleRotateRightChildSubTree;
    tree->deleteSubTree = BinarySearchTree_deleteSubTree;
    tree->printPreOrderSubTree = BinarySearchTree_printPreOrderSubTree;
    tree->printInOrderSubTree = BinarySearchTree_printInOrderSubTree;
    tree->printPostOrderSubTree = BinarySearchTree_printPostOrderSubTree;
    tree->getHeightSubTree = BinarySearchTree_getHeightSubTree;
    return tree;
}

int unitTestTree_BST_AVL(void) {
    BinarySearchTree* bst = NULL;
    BinaryTreeNode* node = NULL;
    IntObject* data = NULL;
    ComparableObject* compObj = NULL;
    int num;

    bst = newBinarySearchTree();
    bst->AVL = 1;

    for(int i = 0; i < 16; ++ i) {
        num = rand()%16;
        data = newIntObject(num);
        if (!bst->find(bst, (void*)data)) {
            bst->insert(bst, (void*)data);
        } else {
            data->delete(data);
        }
    }
    bst->getHeight(bst);
    bst->printBFS(bst);
    bst->printPreOrder(bst);
    bst->printPreOrderByStack(bst);
    bst->printInOrder(bst);
    bst->printInOrderByStack(bst);
    bst->printPostOrder(bst);
    bst->printPostOrderByStack(bst);

    // remove 3 min nodes
    for(int i = 0; i < 3; ++ i) {
        node = bst->findMin(bst);
        data = (IntObject*)node->data;
        printf("remove node: %p with data: %s\n", node, data->base.toString((ComparableObject*)data));
        bst->remove(bst, node->data);
        data->delete(data);
    }
    bst->getHeight(bst);
    bst->printBFS(bst);

    // remove 4 max nodes
    for(int i = 0; i < 4; ++ i) {
        node = bst->findMax(bst);
        data = (IntObject*)node->data;
        printf("remove node: %p with data: %s\n", node, data->base.toString((ComparableObject*)data));
        bst->remove(bst, node->data);
        data->delete(data);
    }
    bst->getHeight(bst);
    bst->printBFS(bst);
    bst->printPreOrder(bst);

    // remove 1 min nodes
    for(int i = 0; i < 1; ++ i) {
        node = bst->findMin(bst);
        data = (IntObject*)node->data;
        printf("remove node: %p with data: %s\n", node, data->base.toString((ComparableObject*)data));
        bst->remove(bst, node->data);
        data->delete(data);
    }
    bst->getHeight(bst);
    bst->printBFS(bst);

    // remove all nodes
    node = bst->findMin(bst);
    while (node) {
        data = (IntObject*)node->data;
        printf("remove node: %p with data: %s\n", node, data->base.toString((ComparableObject*)data));
        bst->remove(bst, node->data);
        data->delete(data);

        node = bst->findMin(bst);
    }
    bst->delete(bst);
    return 0;
}

int unitTestTree_BST(void) {
    BinarySearchTree* bst = NULL;
    BinaryTreeNode* node = NULL;
    IntObject* data = NULL;
    ComparableObject* compObj = NULL;
    int num;

    bst = newBinarySearchTree();

    for(int i = 0; i < 16; ++ i) {
        num = rand()%16;
        data = newIntObject(num);
        if (!bst->find(bst, (void*)data)) {
            bst->insert(bst, (void*)data);
        } else {
            data->delete(data);
        }
    }
    bst->getHeight(bst);
    bst->printBFS(bst);
    bst->printPreOrder(bst);
    bst->printPreOrderByStack(bst);
    bst->printInOrder(bst);
    bst->printInOrderByStack(bst);
    bst->printPostOrder(bst);
    bst->printPostOrderByStack(bst);

    // find last node inserted
    data = newIntObject(num);
    node = bst->find(bst, (void*)data);
    data->delete(data);

    // find min node
    node = bst->findMin(bst);
    compObj = (ComparableObject*)node->data;
    printf("min node: %p, data: %s\n", node, compObj->toString(compObj));

    // find max node
    node = bst->findMax(bst);
    compObj = (ComparableObject*)node->data;
    printf("max node: %p, data: %s\n", node, compObj->toString(compObj));

    // remove root node
    data = (IntObject*)bst->root->data;
    bst->remove(bst, (void*)data);
    data->delete(data);
    bst->printInOrder(bst);

    // remove all nodes
    node = bst->findMin(bst);
    while (node) {
        data = (IntObject*)node->data;
        printf("remove node: %p with data: %s\n", node, data->base.toString((ComparableObject*)data));
        bst->remove(bst, node->data);
        data->delete(data);

        node = bst->findMin(bst);
    }
    bst->delete(bst);
    return 0;
}

int unitTestTree(void) {
    unitTestTree_BST_AVL();
    return 0;
}
