#ifndef BTREE_H
#define BTREE_H

#include<stdio.h>

typedef struct BTreeNode {
    void  *data;
    struct BTreeNode *left;
    struct BTreeNode *right;
} BTreeNode;

typedef struct BTree {
    int size ;
    int (*compare)(const void *key1, const void *key2);
    void (*destroy)(void *data);
    BTreeNode *root;
} BTree;

void btree_init(BTree *tree, void (*destroy)(void *data));
void btree_destroy(BTree *tree);
int btree_ins_left(BTree *tree, BTreeNode *node, const void *data);
int btree_ins_right(BTree *tree, BTreeNode *node, const void *data);

void btree_rem_left(BTree *tree, BTreeNode *node);
void btree_rem_right(BTree *tree, BTreeNode *node);

int btree_merge(BTree *merge, BTree *left, BTree *right, const void *data);

#define btree_is_eob(node) ((node) == NULL) /* an empty node */
#define btree_is_leaf(node) ((node)->left == NULL \
        && (node)->right == NULL)

#endif /* BTREE_H */
