#include<string>
#include<cstdio>
#include<memory>
#include<iostream>
#include<fstream>

#define OUTPUT_DOT "bTreeDot.dot"
using namespace std;
template<class T> class bTreeNode {
    private:
        T Key;
        shared_ptr<bTreeNode<T>> Left;
        shared_ptr<bTreeNode<T>> Right;

        // for print_dot
        int nullcnt;
        void print_dot_null(const T & key,
                fstream & stream);
        void print_dot_aux(const bTreeNode<T> * node, fstream & stream);
        /////////////

    public:
        T key() const { return Key; }
        bTreeNode<T> * left() const { return Left.get(); }
        bTreeNode<T> * right() const { return Right.get(); }

        // overload constructor
        bTreeNode & operator=(const bTreeNode &) = delete;
        bTreeNode(const T & key);
        bTreeNode(const T & key,
                const T & kyLeft);
        bTreeNode(const T & key,
                const T & kyLeft, // key of left node
                const T & kyRight); // key of right node
        bTreeNode(const bTreeNode<T> &); // assign
        bTreeNode(const T & key,
                const bTreeNode<T> * pLeft);
        bTreeNode(const T & key,
                const bTreeNode<T> * pLeft,
                const bTreeNode<T> * pRight);
        ~bTreeNode();

        // method
        void print_dot(string filename);
};

// constructors
template<class T> bTreeNode<T>::bTreeNode(const T & key) {
    this->Key = key;
    this->Left = nullptr;
    this->Right = nullptr;
}

template<class T> bTreeNode<T>::bTreeNode(const T & key,
        const T & kyLeft) {
    this->Key = key;
    this->Left = shared_ptr<bTreeNode<T>>(new bTreeNode<T>(kyLeft));
    this->Right = nullptr;
}

template<class T> bTreeNode<T>::bTreeNode(const T & key,
        const T & kyLeft,
        const T & kyRight) {
    this->Key = key;
    this->Left = shared_ptr<bTreeNode<T>>(new bTreeNode<T>(kyLeft));
    this->Right = shared_ptr<bTreeNode<T>>(new bTreeNode<T>(kyRight));
}

template<class T> bTreeNode<T>::bTreeNode(const bTreeNode<T> & node) {
    this->Key = node->key();
    this->Left = node->left();
    this->Right = node->right();
}

template<class T> bTreeNode<T>::bTreeNode(const T & key,
        const bTreeNode<T> * pLeft) {
    this->Key = key;
    this->Left = shared_ptr<bTreeNode<T>>((bTreeNode<T> *)pLeft);
    this->Right = nullptr;
}

template<class T> bTreeNode<T>::bTreeNode(const T & key,
        const bTreeNode<T> * pLeft,
        const bTreeNode<T> * pRight) {
    this->Key = key;
    this->Left = shared_ptr<bTreeNode<T>>((bTreeNode<T> *)pLeft);
    this->Right = shared_ptr<bTreeNode<T>>((bTreeNode<T> *)pRight);
}

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
    bTreeNode<T> *node_l = node->left();
    bTreeNode<T> *node_r = node->right();

    if (node_l) {
        stream << "\t" << node->key() << " -> " << node_l->key() << " [color=red];\n";
        print_dot_aux(node_l, stream);
    } else {
        print_dot_null(node->key(), stream);
        nullcnt++;
    }

    if (node_r) {
        stream << "\t" << node->key() << " -> " << node_r->key() << " [color=blue];\n";
        print_dot_aux(node_r, stream);
    } else {
        print_dot_null(node->key(), stream);
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

    if (!this->Right && !this->Left)
        stream << "\t" << this->Key << ";\n";
    else
        print_dot_aux(this, stream);

    stream <<  "}\n";
    stream.close();
    nullcnt = 0;
}
#endif

//  destructor
template<class T> bTreeNode<T>::~bTreeNode() { }
///////


int entry(void) {
    shared_ptr<bTreeNode<string>> root
        (new bTreeNode<string>("root",
            new bTreeNode<string>("daily", "hello", "byebye"),
            new bTreeNode<string>("chaos", "darkness", "corruption")));
    root->print_dot(OUTPUT_DOT);
}

int main( int argc, char **argv ) {
    entry();
    return 0;
}
