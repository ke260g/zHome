#include"avltree.h"
#include<stdlib.h>
#include<string.h>

static void avltree_rotate_left(BTreeNode **node);
static void avltree_rotate_right(BTreeNode **node);
static void avltree_destroy_left(BTree *tree, BTreeNode *node);
static void avltree_destroy_right(BTree *tree, BTreeNode *node);

#define AVL_LEFT_HEAVY 1
#define AVL_RIGHT_HEAVY -1
#define AVL_BALANCED 0

/* Private interface */

static void avltree_rotate_left(BTreeNode **node) {
    BTreeNode *src_left, *grandchild;

    src_left = (*node)->left;

    if(((AvlTreeNode *)(src_left->data))->factor == AVL_LEFT_HEAVY) {
        /* perform LL rotation */
        (*node)->left = src_left->right;
        src_left->right = *node;

        ((AvlTreeNode *)((*node)->data))->factor = AVL_BALANCED;
        ((AvlTreeNode *)((src_left)->data))->factor = AVL_BALANCED;

        *node = src_left;

    }
    else if(((AvlTreeNode *)(src_left->data))->factor == AVL_RIGHT_HEAVY) {
        /* perform LR rotation */
        grandchild = src_left->right;

        src_left->right = grandchild->left;
        (*node)->left = grandchild->right;

        grandchild->left = src_left;
        grandchild->right = *node;

        switch(((AvlTreeNode *)(grandchild->data))->factor) {
            case AVL_LEFT_HEAVY:
                ((AvlTreeNode *)((*node)->data))->factor = AVL_RIGHT_HEAVY;
                ((AvlTreeNode *)((src_left)->data))->factor = AVL_BALANCED;
                break;

            case AVL_RIGHT_HEAVY:
                ((AvlTreeNode *)((*node)->data))->factor = AVL_BALANCED;
                ((AvlTreeNode *)((src_left)->data))->factor = AVL_LEFT_HEAVY;
                break;

            case AVL_BALANCED:
                ((AvlTreeNode *)((*node)->data))->factor = AVL_BALANCED;
                ((AvlTreeNode *)((src_left)->data))->factor = AVL_BALANCED;
                break;
        }

        ((AvlTreeNode *)(grandchild->data))->factor = AVL_BALANCED;
        *node = grandchild;
    }
    return;
}

static void avltree_rotate_right(BTreeNode **node) {
    BTreeNode *src_right, *grandchild;

    src_right = (*node)->right;

    if(((AvlTreeNode *)(src_right->data))->factor == AVL_RIGHT_HEAVY) {
        /* perform RR rotation */
        (*node)->right = src_right->left;
        src_right->left = *node;

        ((AvlTreeNode *)((*node)->data))->factor = AVL_BALANCED;
        ((AvlTreeNode *)((src_right)->data))->factor = AVL_BALANCED;

        *node = src_right;
    }
    else if(((AvlTreeNode *)(src_right->data))->factor == AVL_LEFT_HEAVY) {
        /* perform RL rotation */
        grandchild = src_right->left;

        (*node)->right = grandchild->left;
        src_right->left = grandchild->right;

        grandchild->left = *node;
        grandchild->right = src_right;

        switch(((AvlTreeNode *)(grandchild->data))->factor) {
            case AVL_LEFT_HEAVY:
                ((AvlTreeNode *)((*node)->data))->factor = AVL_BALANCED;
                ((AvlTreeNode *)((src_right)->data))->factor = AVL_RIGHT_HEAVY;
                break;

            case AVL_RIGHT_HEAVY:
                ((AvlTreeNode *)((*node)->data))->factor = AVL_LEFT_HEAVY;
                ((AvlTreeNode *)((src_right)->data))->factor = AVL_BALANCED;
                break;

            case AVL_BALANCED:
                ((AvlTreeNode *)((*node)->data))->factor = AVL_BALANCED;
                ((AvlTreeNode *)((src_right)->data))->factor = AVL_BALANCED;
                break;
        }

        ((AvlTreeNode *)(grandchild->data))->factor = AVL_BALANCED;
        *node = grandchild;
    }
    return;
}

static void avltree_destroy_left(BTree *tree, BTreeNode *node) {
    BTreeNode **position;
    if(tree->size == 0)
        return; /* empty tree */

    if(node == NULL)
        position = &(tree->root);
    else
        position = &(node->left);

    if(*position != NULL) {
        avltree_destroy_left(tree, *position);
        avltree_destroy_right(tree, *position);

        if(tree->destroy != NULL) {
            tree->destroy(((AvlTreeNode *)(*position)->data)->data);
        }

        /* free the AVL data in the node, then free the node itself */
        free((*position)->data);
        free(*position);
        *position = NULL;
        tree->size--;
    }
}

static void avltree_destroy_right(BTree *tree, BTreeNode *node) {
    BTreeNode **position;
    if(tree->size == 0)
        return; /* empty tree */

    if(node == NULL)
        position = &(tree->root);
    else
        position = &(node->right);

    if(*position != NULL) {
        avltree_destroy_left(tree, *position);
        avltree_destroy_right(tree, *position);

        if(tree->destroy != NULL) {
            tree->destroy(((AvlTreeNode *)(*position)->data)->data);
        }

        /* free the AVL data in the node, then free the node itself */
        free((*position)->data);
        free(*position);
        *position = NULL;

        tree->size--;
    }
}

static int avltree_insert(BTree *tree, BTreeNode **node,
        const void *data, int *is_balanced) {
    AvlTreeNode *avl_data;
    int cmpval, retval;

    if((avl_data = (AvlTreeNode *)malloc(sizeof(AvlTreeNode))) == NULL)
        return -1;  /* can't allocate memory space */

    /* initialize the  avltree_node */

    avl_data->factor = AVL_BALANCED;
    avl_data->hidden = 0;       /* Mark as not be hiddened */
    avl_data->data = (void *)data;

    /* Insert the data into the tree */

    if(btree_is_eob(*node))  /* handle the insertion into an empty child_tree */
        return btree_ins_left(tree, *node, avl_data);

    else { /* Handle insertion into a child_tree that is not empty */
        cmpval = tree->compare(data, ((AvlTreeNode *)(*node)->data)->data);

        if(cmpval < 0) { /* Move to the left */
            if(btree_is_eob((*node)->left)) { /* (*node)->left is an empty node */

                if(btree_ins_left(tree, *node, avl_data) != 0)
                    return -1; /* failed to insert */
                *is_balanced = 0; /* marked as not balanced */

            } else { /* (*node)->left is not an empty one */
                if((retval = avltree_insert(tree, &((*node)->left), data, is_balanced)) != 0)
                    return retval;
            }
            /* =====================  */
            /* Ensure that the tree remains balanced */
            if(!(*is_balanced)) {
                /* perform the balanced adjustment */
                switch (((AvlTreeNode *)((*node)->data))->factor) {
                    case AVL_LEFT_HEAVY:
                        avltree_rotate_left(node);
                        *is_balanced = 1;
                        break;

                    case AVL_RIGHT_HEAVY:
                        ((AvlTreeNode *)((*node)->data))->factor = AVL_BALANCED;
                        *is_balanced =1 ;
                        break;

                    case AVL_BALANCED:
                        ((AvlTreeNode *)((*node)->data))->factor = AVL_LEFT_HEAVY;
                        break;
                }
            }

        } /* if(cmpval < 0) */
        else if (cmpval > 0) {
            /* Move to right */
            if(btree_is_eob((*node)->right)) {

                if(btree_ins_right(tree, *node, avl_data) != 0)
                    return -1; /* failed to insert the avl_node */
                *is_balanced = 0; /* marked as not empty */

            } else {
                if((retval = avltree_insert(tree, &((*node)->right), data, is_balanced)) != 0)
                    return retval;
            }

            if(!(*is_balanced)) {/* Ensure the tree remains balanced */
                /* perform balanced adjustment, throught the ->factor */
                switch (((AvlTreeNode *)((*node)->data))->factor) {
                    case AVL_LEFT_HEAVY:
                        ((AvlTreeNode *)((*node)->data))->factor = AVL_BALANCED;
                        *is_balanced = 1; /* marked as balanced */
                        break;

                    case AVL_BALANCED:
                        ((AvlTreeNode *)((*node)->data))->factor = AVL_RIGHT_HEAVY;
                        break;

                    case AVL_RIGHT_HEAVY:
                        avltree_rotate_right(node);
                        *is_balanced = 1; /* marked as balanced */
                        break;
                }
            }
        } /* if(cmpval > 0) */
        else { /* cmpval == 0, finding a copy of the data */
            if(!(((AvlTreeNode *)((*node)->data))->hidden))
                return 1; /* the data is in the tree and not hidden */

            else { /* insert the new data and mark it as not hidden */
                if(tree->destroy != NULL)
                    tree->destroy(((AvlTreeNode *)((*node)->data))->data);
                /* destroy the data since it has been replaced */
                ((AvlTreeNode *)((*node)->data))->data = (void *)data;
                ((AvlTreeNode *)((*node)->data))->hidden = 0; /* 0 means not hidden */

                /* tree's structure is not changed, no need to rebalance */
                *is_balanced = 1;
            }
        }
    }
    return 0;
}

static int avltree_hide(BTree *tree, BTreeNode *node,
        const void *data) {
    int cmpval, retval;

    if(btree_is_eob(node))
        return -1; /* the data is not found */

    cmpval = tree->compare(data, ((AvlTreeNode *)(node->data))->data);

    if(cmpval < 0) /* move to left */
        retval = avltree_hide(tree, node->left, data);
    else if(cmpval > 0) /* move to right */
        retval = avltree_hide(tree, node->right, data);
    else {/* cmpval == 0 */
        /* Mark the node as hidden */
        ((AvlTreeNode *)(node->data))->hidden = 1;
        retval = 0;
    }

    return retval;
}

static int lookup(BTree *tree, BTreeNode *node, void **data) {
    int cmpval, retval;

    if(btree_is_eob(node))
        return -1; /* that the data is not found */

    cmpval = tree->compare(*data, ((AvlTreeNode*)(node->data))->data);

    if (cmpval < 0) /* move to left */
        retval = lookup(tree, node->left, data);
    else if (cmpval > 0) /* move to right */
        retval = lookup(tree, node->right, data);
    else { /* cmpval == 0 */
        if(((AvlTreeNode *)(node->data))->hidden == 0) {
            /* pass back the data from the tree */
            *data = ((AvlTreeNode *)(node->data))->data;
            retval = 0;
        } else /* ...->hidden == 1 */
            return -1; /* that the data is not found */
    }

    return retval;
}

/* Public interface */

void avltree_init(AvlTree *tree,
        int (*compare)(const void *key1, const void *key2),
        int (*destroy)(void *data)) {
    tree->compare = compare;
    tree->destroy = destroy;
    tree->root = NULL;
    tree->size = 0;
}

void avltree_destroy(AvlTree *tree, const void *data) {
    avltree_destroy_left(tree, NULL);
    memset(tree, 0, sizeof(AvlTree));
}

int avltree_ins(AvlTree *tree, const void *data) {
    int is_balanced = 0;  /* mark as not balanced */
    return avltree_insert(tree, &(tree->root), data, &is_balanced);
}

int avltree_rem(AvlTree *tree, const void *data) {
    return avltree_hide(tree, tree->root, data);
}

int avltree_lookup(AvlTree *tree, void **data) {
    return lookup(tree, tree->root, data);
}
