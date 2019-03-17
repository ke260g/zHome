/* red-black tree */
#include<string>
#include<cstdio>
#include<iostream>
#include<fstream>
#include<list>
#include<functional>

#include"bTree.hpp"

using namespace std;

#define OUTPUT_DOT "bTreeDot.dot"

template<class T>
class RBTreeNode : public bTreeNode<T> {
    private:
        bool color; //
    public:
        const static int Black =  0;
        const static int Red = 1;

        RBTreeNode(const T & key);

        bool getColor();
        void setColor(bool newColor) { color = newColor; }
};

template<class T>
bool RBTreeNode<T>::getColor() { return color; }

template<class T>
RBTreeNode<T>::RBTreeNode(const T & key) : bTreeNode<T>(key)
{
    color = this->Red;
}

template<class T>
void RBTreeInsertFixUp(RBTreeNode<T> *z) {
    // node is root, set to black
    if(z->parent == nullptr) {
        z->setColor = 1;
        return;
    }

    // node is not root, else tree need to fixup
    RBTreeNode<T> * y = nullptr; // pointed to uncle node

    while(1) {
        if(z->parent == nullptr) {
            z->setColor = 1;
            return;
        }
        if(z->parent->getColor() == 1) {
            //if(z->parent == z->parent

        }
    }

    // z pointed to "current-node", which is dynamic
    while(z->parent->getColor() == 1) { // parent is red
        if(z->parent == z->parent->parent->left) {
            y = z->parent->parent->right;
            if(y->getColor() == 1) { // uncle is red
                z->parent->setColor(0);
                y->setColor(0);
                z->parent->parent->setColor(1);
                z = z->parent->parent;
            } else { // y->color == 0 , uncle is black

            }
        }

        else // z->parent == z->parent->right
            ;
    }
}

template<class T>
RBTreeNode<T> * RBTreeInsert(RBTreeNode<T> *node, T val) {
    // new inserted node
    RBTreeNode<T> * z = new RBTreeNode<T>(val);
    if(node == nullptr) {
        z->setColor(0);
        return z;
    }

    bTreeNode<T> * x = node->root(); // preview inserted position
    bTreeNode<T> * y = nullptr; // parent of inserted position

    while(y != nullptr) {
        y = x;
        if(val < x->key)
            x = x->left;
        else
            x = x->right;
    }
    z->parent = y; // y is parent of inserted position

    if(z->key < y->key)
        y->left = z;
    else // z->key >= y->key
        y->right = z;

    RBTreeInsertFixUp(z);
    return z->root();
}

template<class T>
void RBTreeDeleteFixUp(RBTreeNode<T> *x) {
    RBTreeNode<T> *w;
    while(x->parent != nullptr && x->color == RBTreeNode<T>::Black) {
        if(x == x->parent->left) {
           w = x->parent->right;
           if(w->color == RBTreeNode<T>::Red) {
               w->color = RBTreeNode<T>::Black;
               x->parent->color = RBTreeNode<T>::Red;
               // left roate x->parent;
               w = x->parent->right;
           }
        }

        if(x == x->parent->left) {

        }
    }

    x->color = RBTreeNode<T>::Black;
}

template<class T>
void RBTreeDelete(RBTreeNode<T> *nd, T val) {
    RBTreeNode<T> * z; // val-node
    RBTreeNode<T> * y; // will deleted node (has one or zero child)
    RBTreeNode<T> * x; // y's child or nullptr

    // z = find where val is
    if(z == nullptr)
        return;

    if(z->left == nullptr || z->right == nullptr)
        y = z;
    else // z must have a successor
        ; //y = z.successor();

    x = nullptr;
    if(y->left != nullptr)
        x = y->left;
    else if(y->right != nullptr)
        x = y->right;


    // change x parent and parent's child
    if(x != nullptr)
        x->parent = y->parent;
    if(y == y->parent->left)
        y->parent->left = x;
    else if(y == y->parent->right)
        y->parent->right = x;

    if(y != z)
        z->key = y->key;

    if(y->getColor == RBTreeNode<T>::Black)
        if(x != nullptr)
            RBTreeDeleteFixUp(x);
    delete y;
}
