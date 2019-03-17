#ifndef AVLTREE_H
#define AVLTREE_H

#include"btree.h"

#define AVL_LEFT_HEAVY 1
#define AVL_RIGHT_HEAVY -1
#define AVL_BALANCED 0

typedef struct AvlTreeNode {
    void *data;
    int hidden;
    int factor; /* balanced factor */
} AvlTreeNode;

typedef BTree AvlTree;

void avltree_init(AvlTree *tree,
        int (*compare)(const void *key1, const void *key2),
        int (*destroy)(void *data));
void avltree_destroy(AvlTree *tree, const void *data);

int avltree_ins(AvlTree *tree, const void *data);
int avltree_rem(AvlTree *tree, const void *data);

int avltree_lookup(AvlTree *tree, void **data);
#endif
