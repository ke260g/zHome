#include<string>
#include<cstdio>
#include<memory>
#include<iostream>
#include<fstream>

#define OUTPUT_DOT "bTreeDot.dot"
using namespace std;

template<class T> class bTreeNode {
    private:
        // for print_dot
        int nullcnt;
        void print_dot_null(const T & key,
                fstream & stream);
        void print_dot_aux(const bTreeNode<T> * node, fstream & stream);
        /////////////
    public:
        T key;
        shared_ptr<bTreeNode<T>> left;
        shared_ptr<bTreeNode<T>> right;

        // overload constructor
        bTreeNode(const T & key);
        bTreeNode(const T & key,
                const T & kyLeft);
        bTreeNode(const T & key,
                const T & kyLeft, // key of left node
                const T & kyRight); // key of right node
        bTreeNode(const T & key,
                const shared_ptr<bTreeNode<T>> pLeft);
        bTreeNode(const T & key,
                const shared_ptr<bTreeNode<T>> pLeft,
                const shared_ptr<bTreeNode<T>> pRight);
        ~bTreeNode();

        // method
        void print_dot(string filename);
};

// constructors
template<class T> bTreeNode<T>::bTreeNode(const T & key) {
    this->key = key;
    this->left = nullptr;
    this->right = nullptr;
}

template<class T> bTreeNode<T>::bTreeNode(const T & key,
        const T & kyLeft) {
    this->key = key;
    this->left = make_shared<bTreeNode<T>>(kyLeft);
    this->right = nullptr;
}

template<class T> bTreeNode<T>::bTreeNode(const T & key,
        const T & kyLeft,
        const T & kyRight) {
    this->key = key;
    this->left = make_shared<bTreeNode<T>>(kyLeft);
    this->right = make_shared<bTreeNode<T>>(kyRight);
}

template<class T> bTreeNode<T>::bTreeNode(const T & key,
        const shared_ptr<bTreeNode<T>> pLeft) {
    this->key = key;
    this->left = pLeft;
    this->right = nullptr;
}

template<class T> bTreeNode<T>::bTreeNode(const T & key,
        const shared_ptr<bTreeNode<T>> pLeft,
        const shared_ptr<bTreeNode<T>> pRight) {
    this->key = key;
    this->left = pLeft;
    this->right = pRight;
}
///////////////////

//  destructor
template<class T> bTreeNode<T>::~bTreeNode() { }
///////

#if 1 /* write to a dot file, then generate png */
/* fork from "http://eli.thegreenplace.net/2009/11/23/visualizing-binary-trees-with-graphviz"
 * after run the program successfully
 * then 0$>_ dot -Tpng <input>.dot -o <output>.png
 * then 1$>_ view the png file
 */
template<class T> void bTreeNode<T>::print_dot_null(const T & key,
        fstream & stream) {
    stream << "\tnull" << nullcnt << " [shape=point];\n";
    stream << "\t" << key << " -> null" << nullcnt << ";\n";
}

template<class T> void bTreeNode<T>::print_dot_aux(const bTreeNode<T> * node,
        fstream & stream) {
    if ((node->left).get()) {
        stream << "\t" << node->key << " -> " << (node->left).get()->key << " [color=red];\n";
        print_dot_aux((node->left).get(), stream);
    } else {
        print_dot_null(node->key, stream);
        nullcnt++;
    }

    if ((node->right).get())
    {

        stream << "\t" << node->key << " -> " << (node->right).get()->key << " [color=blue];\n";
        print_dot_aux((node->right).get(), stream);
    } else {
        print_dot_null(node->key, stream);
        nullcnt++;
    }
}

template<class T> void bTreeNode<T>::print_dot(string filename) {
    nullcnt = 0;
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
        print_dot_aux(this, stream);

    stream <<  "}\n";
    stream.close();
    nullcnt = 0;
}
#endif

int entry(void) {
    shared_ptr<bTreeNode<string>> root;
    root = make_shared<bTreeNode<string>>("root",
            (make_shared<bTreeNode<string>>("daily", "hello", "byebye")),
            (make_shared<bTreeNode<string>>("chaos", "darkness", "corruption")));
    root->print_dot(OUTPUT_DOT);
}

int main( int argc, char **argv ) {
    entry();
    return 0;
}
