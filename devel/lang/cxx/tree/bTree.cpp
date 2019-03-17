#include<string>
#include<cstdio>
#include<iostream>
#include<fstream>
#include<list>
#include<functional>

#include"bTree.hpp"

using namespace std;

#define OUTPUT_DOT "bTreeDot.dot"

// constructors
template<class T>
bTreeNode<T>::bTreeNode(const T & key) {
    this->key = key;
    this->parent = nullptr;

    this->left = nullptr;
    this->right = nullptr;
}

template<class T>
bTreeNode<T>::bTreeNode(const T & key,
        const T & kyLeft) {
    this->key = key;
    this->parent = nullptr;

    this->left = new bTreeNode<T>(kyLeft);
    this->left->parent = this;

    this->right = nullptr;
}

template<class T>
bTreeNode<T>::bTreeNode(const T & key,
        const T & kyLeft,
        const T & kyRight) {
    this->key = key;
    this->parent = nullptr;

    this->left = new bTreeNode<T>(kyLeft);
    this->left->parent = this;

    this->right = new bTreeNode<T>(kyRight);
    this->right->parent = this;
}

template<class T>
bTreeNode<T>::bTreeNode(const T & key,
        const bTreeNode<T> * pLeft) {
    this->key = key;
    this->parent = nullptr;

    this->left = pLeft;
    this->left->parent = this;

    this->right = nullptr;
}

template<class T>
bTreeNode<T>::bTreeNode(const T & key,
        const bTreeNode<T> * pLeft,
        const bTreeNode<T> * pRight) {
    this->key = key;
    this->parent = nullptr;

    this->left = (bTreeNode<T> *)pLeft;
    this->left->parent = this;

    this->right = (bTreeNode<T> *)pRight;
    this->right->parent = this;
}
///////////////////

//  destructor
template<class T>
bTreeNode<T>::~bTreeNode() {
    function<void(bTreeNode<T> *)> bTreeFree =
        [&](bTreeNode<T> * nd) {
            if(nd->left != nullptr) {
                bTreeFree(nd->left);
                delete nd->left;
                nd->left = nullptr;
            }

            if(nd->right != nullptr) {
                bTreeFree(nd->right);
                delete nd->right;
                nd->right = nullptr;
            }
        };

    bTreeFree(this);
}

///////
#if 1 /* preorder, inorder, postorder, level-order */
template<class T>
void bTreeNode<T>::preorder_bTree() {
    cout << this->key << endl;

    if(this->left != nullptr)
        this->left->preorder_bTree();

    if(this->right != nullptr)
        this->right->preorder_bTree();
}

template<class T>
void bTreeNode<T>::inorder_bTree() {
    if(this->left != nullptr)
        this->left->inorder_bTree();

    cout << this->key << endl;

    if(this->right != nullptr)
        this->right->inorder_bTree();
}

template<class T>
void bTreeNode<T>::postorder_bTree() {
    if(this->left != nullptr)
        this->left->postorder_bTree();

    if(this->right != nullptr)
        this->right->postorder_bTree();

    cout << this->key << endl;
}
#endif /* preorder, inorder, postorder, level-order */

#if 1 /* return high, return n_nodes, return root, find a node */
template<class T>
int bTreeNode<T>::n_nodes_bTree() {
    int i = 1;

    if(this->left != nullptr)
        i += this->left->n_nodes_bTree();

    if(this->right != nullptr)
        i += this->right->n_nodes_bTree();

    return i;
}

template<class T>
int bTreeNode<T>::n_high_bTree() {
    int hl = 0,
        hr = 0;
    if(this->left != nullptr)
        hl = this->left->n_high_bTree();

    if(this->right != nullptr)
        hr = this->right->n_high_bTree();

    return hl > hr ? ++hl : ++hr;
}

template<class T>
bTreeNode<T> * bTreeNode<T>::root() {
    if(this->parent != nullptr)
        return this->parent->root();
    else
        return this;
}

template<class T>
bTreeNode<T> * bTreeNode<T>::index(T val) {
    if(this->key == val)
        return this;
    if(this->left != nullptr)
        return this->left->index(val);
    if(this->right != nullptr)
        return this->right->index(val);
    return nullptr;
}
#endif

#if 1 /* write to a dot file, then generate png */
/* fork from "http://eli.thegreenplace.net/2009/11/23/visualizing-binary-trees-with-graphviz"
 * after run the program successfully
 * then 0$>_ dot -Tpng <input>.dot -o <output>.png
 * then 1$>_ view the png file
 */

/*template<class T> void bTreeNode<T>::print_dot_null(const T & key,
  fstream & stream) {
  stream << "\tnull" << nullcnt << " [shape=point];\n";
  stream << "\t" << key << " -> null" << nullcnt << ";\n";
  }*/

template<class T>
void bTreeNode<T>::print_dot_aux(const bTreeNode<T> * node,
        fstream & stream, int *nullcnt) {
    auto print_dot_null = [&](const T & key,
            fstream & stream,
            int nilcnt) {
        stream << "\tnull" << nilcnt
            << " [shape=point];\n";
        stream << "\t" << key <<
            " -> null" << nilcnt << ";\n";
    };

    if (node->left) {
        stream << "\t" << node->key << " -> " <<
            node->left->key << " [color=red];\n";
        print_dot_aux(node->left, stream, nullcnt);
    } else {
        print_dot_null(node->key, stream, *nullcnt);
        (*nullcnt)++;
    }

    if (node->right) {
        stream << "\t" << node->key << " -> " <<
            node->right->key << " [color=blue];\n";
        print_dot_aux(node->right, stream, nullcnt);
    } else {
        print_dot_null(node->key, stream, *nullcnt);
        (*nullcnt)++;
    }
}

template<class T>
void bTreeNode<T>::print_dot(string filename) {
    int nullcnt = 0;
    fstream stream(filename, ios::binary | ios::out);
    if(!stream.is_open()) {
        cout << "faile to write a new dot file, \n";
        return;
    }

    stream << "digraph BST {\n";
    stream << "\tnode [fontname=\"Arial\"];\n";

    if (!this->right && !this->left)
        stream << "\t" << this->key << ";\n";
    else
        print_dot_aux(this, stream, &nullcnt);

    stream <<  "}\n";
    stream.close();
}
#endif

#if 0 /* binary search tree test, so many bug version !!! */
/* as it's rarely used, do not fix and explore more */
/* bsearch */
bTreeNode<int> * bstree_search(const bTreeNode<int> * node,
        const int key) {
    if(node == nullptr || node->key == key)
        return const_cast<bTreeNode<int> *>(node);
    if(key < node->key)
        return bstree_search(node->left, key);
    else
        return bstree_search(node->right, key);
}

bTreeNode<int> * bstree_max(const bTreeNode<int> * node) {
    if(node == nullptr)
        return nullptr;
    while(node->right != nullptr)
        node = node->right;
    return const_cast<bTreeNode<int> *>(node);
}

bTreeNode<int> * bstree_min(const bTreeNode<int> * node) {
    if(node == nullptr)
        return nullptr;
    while(node->left != nullptr)
        node = node->left;
    return const_cast<bTreeNode <int> *>(node);
}

bTreeNode<int> * bstree_predecessor(const bTreeNode<int> * node) {
    // basic definition: max of left
    if(node->left != nullptr)
        return bstree_max(node->left);

    // if
    //  node is a right-leaf,
    // predecessor is its parent
    //
    // if
    //  node is a left-leaf
    // predecessor is its parent with a right-child
    bTreeNode<int> * y = node->parent;
    while((y != nullptr) && (node == y->left)) {
        node = y;
        y = y->parent;
    }
    return y;

}

bTreeNode<int> * bstree_successor(const bTreeNode<int> * node) {
    // basic definition: min of right
    if(node->right != nullptr)
        return const_cast<bTreeNode<int> *>(node);

    // if
    //  node is a left-leaf,
    // successor is its parent
    //
    // if
    //  node is a right-leaf
    // successor is its parent with a left-child
    bTreeNode<int> * y = node->parent;
    while((y != nullptr) && (node == y->right)) {
        node = y;
        y = y->parent;
    }
    return y;
}

/* bst insert */
static bTreeNode<int> * bstree_insert(bTreeNode<int> * root,
        bTreeNode<int> * z) {
    bTreeNode<int> * y = nullptr;
    bTreeNode<int> * x = root;

    if(x == nullptr)
        return z;

    // find position of z
    while(x != nullptr) {
        y = x;
        if(z->key < x->key)
            x = x->left;
        else
            x = x->right;
    }

    if(z->key < y->key)
        y->left = z;
    else
        y->right = z;

    z->parent = y;
    return root;
}
// public interface
bTreeNode<int> * insert_bstree(bTreeNode<int> * root,
        int key) {
    bTreeNode<int> * z = new bTreeNode<int>(key);
    return bstree_insert(root, z);
}

/* bst delete node */
static bTreeNode<int> * bstree_delete(bTreeNode<int> * root,
        bTreeNode<int> * z) {
    bTreeNode<int> * x = nullptr;
    bTreeNode<int> * y = nullptr;

    if((z->left == nullptr) || (z->right == nullptr))
        y = z;
    else
        y = bstree_successor(z);

    if(y->left != nullptr)
        x = y->left;
    else
        x = y->right;

    if(x != nullptr)
        x->parent = y->parent;

    if(y->parent == nullptr)
        root = x;
    else if(y == y->parent->left)
        y->parent->left = x;
    else
        y->parent->right = x;

    if(y != z)
        z->key = y->key;

    if(y != nullptr) {
        y->left = nullptr;
        y->right = nullptr;
        delete y;
    }

    return root;
}

bTreeNode<int> * delete_bstree(bTreeNode<int> * root,
        int key) {
    bTreeNode<int> * z = bstree_search(root, key);
    cout << "search finish\n";
    if(z != nullptr)
        root = bstree_delete(root, z);
    return root;
}

int bst_test(void) {
    int arr[] = {1, 5, 4, 3, 2, 6, 2};
    int len = sizeof(arr) / sizeof(arr[0]);

    bTreeNode<int> * root = nullptr;
    for(int i = 0; i < len; i++) {
        root = insert_bstree(root, arr[i]);
        //inorder_bTree(root);
        //cout << "insert finish" << endl;
        //getchar();
    }
    cout << "max key: " << bstree_max(root)->key << endl;
    cout << "min key: " << bstree_min(root)->key << endl;
#if  0
    root = delete_bstree(root, 5);
    cout << "delete finished\n";
    inorder_bTree(root);
#endif

    root->print_dot("bstree.dot");
}
#endif

int entry(void) {
    bTreeNode<string> * root = NULL;
    root = new bTreeNode<string>("root",
            new bTreeNode<string>("daily",
                new bTreeNode<string>("hello", "A", "B"),
                new bTreeNode<string>("byebye", "C", "D")),
            new bTreeNode<string>("chaos",
                new bTreeNode<string>("darkness", "E", "F"),
                new bTreeNode<string>("corruption", "G", "H")));
    root->print_dot(OUTPUT_DOT);
    //root->preorder_bTree();
    root->inorder_bTree();
    //root->postorder_bTree();
    cout << "number of nodes: " << root->n_nodes_bTree() << endl;
    cout << "high of nodes: " << root->n_high_bTree() << endl;

#if 1 /* find root, find key */
    auto node = root->index("X");
    if(node != nullptr)
        cout << node->key << endl;
    else
        cout << "not found" << endl;

    node = node->root();
    cout << node->key << endl;
#endif

    delete root;
}

int main( int argc, char **argv ) {
    //entry();
    //bst_test();
    return 0;
}
