#include"btree.h"

#include<stdlib.h>
#include<stdio.h>
#include<string.h>


void btree_init(BTree *tree, void (*destroy)(void *data)) {
    tree->size = 0;
    tree->root = NULL;
    tree->destroy = destroy

    memset(tree, 0, sizeof(BTree));
}

int btree_ins_left(BTree *tree, BTreeNode *node, const void *data) {
    BTreeNode *new_node, **position;

    if(node == NULL) {
        if(tree->size > 0)
            return -1; /* the btree is not empty */

        else /* tree->size == 0, first node is the root */
            position = &(tree->root);
    } else { /* node != NULL */
        if(node->left != NULL)
            return -1; /* the insertion is not the end of a branch */
        else /* node->left is allowable to insert a new node */
            position = &(node->left);
    }

    /* allowable to allocate storage for the node */
    if((new_node = (BTreeNode *)malloc(sizeof(BTreeNode))) == NULL)
        return -1; /* can't allocate memory space for new_node */

    /* insert the node into the tree */
    new_node->data = (void *)data;
    new_node->left = NULL;
    new_node->right = NULL;
    *position = new_node;

    tree->size++;
    return 0;
}

int btree_ins_right(BTree *tree, BTreeNode *node, const void *data) {
    BTreeNode *new_node, **position;

    if(node == NULL) {
        if(tree->size > 0)
            return -1; /* the btree is already empty */

        else /* tree->size == 0, insert the root */
            position = &(tree->root);
    } else { /* node != NULL */
        if(node->right != NULL)
            return -1; /* the insertion is not the end of a branch */
        else /* node->right is allowable to insert a new node */
            position = &(node->right);
    }

    /* allowable to allocate storage for the node */
    if((new_node = (BTreeNode *)malloc(sizeof(BTreeNode))) == NULL)
        return -1; /* can't allocate memory space for new_node */

    /* insert the node into the tree */
    new_node->data = (void *)data;
    new_node->left = NULL;
    new_node->right = NULL;
    *position = new_node;

    tree->size++;
    return 0;
}

void btree_rem_left(BTree *tree, BTreeNode *node) {
    BTreeNode **position;
    if(tree->size == 0)
        return;

    /* determine where to remove nodes */
    if(node == NULL)
        position = &(tree->root);
    else
        position = &(node->left);

    if(*position != NULL) {
        btree_rem_left(tree, *position);
        btree_rem_right(tree, *position);

        if(tree->destroy != NULL)
            tree->destroy((*position)->data);

        free(*position);
        *position = NULL;
        tree->size--;
    }
}

void btree_rem_right(BTree *tree, BTreeNode *node) {
    BTreeNode **position;
    if(tree->size == 0)
        return;

    /* determine where to remove nodes */
    if(node == NULL)
        position = &(tree->root);
    else
        position = &(node->right);

    if(*position != NULL) {
        btree_rem_right(tree, *position);
        btree_rem_right(tree, *position);

        if(tree->destroy != NULL)
            tree->destroy((*position)->data);

        free(*position);
        *position = NULL;
        tree->size--;
    }
}

int btree_merge(BTree *merge, BTree *left, BTree *right, const void *data) {
    /* how can I distinguish two tree is the same type */
    btree_init(merge, left->destroy);
    if(btree_ins_left(merge, NULL, data) != 0) {
        /* failed to insert the root_node */
        btree_destroy(merge);
        return -1;
    }

    merge->root->left = left->root;
    merge->root->right = right->root;

    merge->size += (left->size + right->size);

    left->root = NULL;
    left->size = 0;
    right->root = NULL;
    right->size = 0;

    return 0;
}
