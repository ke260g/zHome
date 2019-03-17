/* three method to traverse the btree */
/* preorder, inorder, postorder */
/* to make them into a singly list */

#include"slist/slist.h"
#include"btree.h"

int preorder(const BTreeNode *node, SList *list) {
    if(!btree_is_eob(node)) {
        if(slist_ins_next(list, list->tail, node->data))
            return -1;

        if(!btree_is_eob(node->left))
            if(preorder(node->left, list))
                return -1;

        if(!btree_is_eob(node->right))
            if(preorder(node->right, list))
                return -1;

    }
    return 0;
}
int inorder(const BTreeNode *node, SList *list) {
    if(!btree_is_eob(node)) {
        if(!btree_is_eob(node->left))
            if(inorder(node->left, list))
                return -1;

        if(slist_ins_next(list, list->tail, node->data))
            return -1;

        if(!btree_is_eob(node->right))
            if(inorder(node->right, list))
                return -1;

    }
    return 0;
}
int postorder(const BTreeNode *node, SList *list) {
    if(!btree_is_eob(node)) {
        if(!btree_is_eob(node->left))
            if(postorder(node->left, list))
                return -1;

        if(!btree_is_eob(node->right))
            if(postorder(node->right, list))
                return -1;

        if(slist_ins_next(list, list->tail, node->data))
            return -1;

    }
    return 0;
}
