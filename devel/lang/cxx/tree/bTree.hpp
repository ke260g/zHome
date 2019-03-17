#ifndef BTREE_HPP
#include<fstream>
#include<string>

template<class T>
class bTreeNode {
    private:
        // for print_dot
        void print_dot_aux(const bTreeNode<T> * node, std::fstream & stream, int *nullcnt);
    public:
        T key;
        bTreeNode<T> * left;
        bTreeNode<T> * right;
        bTreeNode<T> * parent;

        // overload constructor
        bTreeNode(const T & key);
        bTreeNode(const T & key,
                const T & kyLeft);
        bTreeNode(const T & key,
                const T & kyLeft, // key of left node
                const T & kyRight); // key of right node
        bTreeNode(const T & key,
                const bTreeNode<T> * pLeft);
        bTreeNode(const T & key,
                const bTreeNode<T> * pLeft,
                const bTreeNode<T> * pRight);
        ~bTreeNode();

        // method
        void print_dot(std::string filename);

        // print out on console
        void preorder_bTree();
        void inorder_bTree();
        void postorder_bTree();
        void levelorder_bTree();

        int n_nodes_bTree();
        int n_high_bTree();
        bTreeNode<T> * root();
        bTreeNode<T> * index(T val);
};
#endif /* BTREE_HPP */
