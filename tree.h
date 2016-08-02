#ifndef TREE_H
#define TREE_H

typedef struct _BinaryTreeNode {
    void* data;
    struct _BinaryTreeNode* left;
    struct _BinaryTreeNode* right;
    void (*delete)(struct _BinaryTreeNode* self);
} BinaryTreeNode;

BinaryTreeNode* newBinaryTreeNode(void* data);

typedef struct _BinarySearchTree {
    BinaryTreeNode* root;
    int AVL;

    // operations
    BinaryTreeNode* (*find)(struct _BinarySearchTree* self, void* data);
    BinaryTreeNode* (*findMin)(struct _BinarySearchTree* self);
    BinaryTreeNode* (*findMax)(struct _BinarySearchTree* self);
    void (*insert)(struct _BinarySearchTree* self, void* data);
    void (*remove)(struct _BinarySearchTree* self, void* data);
    void (*delete)(struct _BinarySearchTree* self);
    void (*printPreOrder)(struct _BinarySearchTree* self);
    void (*printInOrder)(struct _BinarySearchTree* self);
    void (*printPostOrder)(struct _BinarySearchTree* self);
    void (*printBFS)(struct _BinarySearchTree* self);
    void (*printPreOrderByStack)(struct _BinarySearchTree* self);
    void (*printInOrderByStack)(struct _BinarySearchTree* self);
    void (*printPostOrderByStack)(struct _BinarySearchTree* self);
    int (*getHeight)(struct _BinarySearchTree* self);

    // private
    BinaryTreeNode* (*findSubTree)(BinaryTreeNode* root, void* data);
    BinaryTreeNode* (*findMinSubTree)(BinaryTreeNode* root);
    BinaryTreeNode* (*findMaxSubTree)(BinaryTreeNode* root);
    BinaryTreeNode* (*insertSubTree)(BinaryTreeNode* root, void* data);
    BinaryTreeNode* (*insertSubTreeAVL)(BinaryTreeNode* root, void* data);
    BinaryTreeNode* (*removeSubTree)(BinaryTreeNode* root, void* data);
    BinaryTreeNode* (*removeSubTreeAVL)(BinaryTreeNode* root, void* data);
    BinaryTreeNode* (*singleRotateLeftChildSubTree)(BinaryTreeNode* root);
    BinaryTreeNode* (*singleRotateRightChildSubTree)(BinaryTreeNode* root);
    BinaryTreeNode* (*doubleRotateLeftChildSubTree)(BinaryTreeNode* root);
    BinaryTreeNode* (*doubleRotateRightChildSubTree)(BinaryTreeNode* root);
    void (*deleteSubTree)(BinaryTreeNode* root);
    void (*printPreOrderSubTree)(BinaryTreeNode* root);
    void (*printInOrderSubTree)(BinaryTreeNode* root);
    void (*printPostOrderSubTree)(BinaryTreeNode* root);
    int (*getHeightSubTree)(BinaryTreeNode* root);
} BinarySearchTree;

BinarySearchTree* newBinarySearchTree(void);

int unitTestTree(void);
#endif
