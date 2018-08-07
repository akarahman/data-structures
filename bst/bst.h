#include <iostream>

template <class T>
struct bst_node
{
    T key;
    bst_node<T>* left;  // left subtree
    bst_node<T>* right; // right subtree
    bst_node(T key_in, bst_node<T>* left_in, bst_node<T>* right_in) : key(key_in), 
                                                                      left(left_in), 
                                                                      right(right_in) {}
};

// Effects: returns the number of nodes in the tree
template <class T> int size(bst_node<T>* root);
// Effects: returns the height of the tree
template <class T> int height(bst_node<T>* root);
// Effects: prints keys in order
template <class T> void traverse_inorder(bst_node<T>* root);
// Effects: prints keys pre order
template <class T> void traverse_preorder(bst_node<T>* root);
// Effects: prints keys post order
template <class T> void traverse_postorder(bst_node<T>* root);
// Effects: inserts a new node in the tree with key k
template <class T> void insert(bst_node<T>* root, T &k);
// Effects: removes node with Key k
template <class T> void remove(bst_node<T>* root, T &k);
