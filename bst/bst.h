#include <iostream>
#include <algorithm>
#include <cassert>

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
template <class T> void insert_helper(bst_node<T>* root, T &k);
// Modifies: root, if nullptr
// Effects: inserts a new node in the tree with key k
template <class T> void insert(bst_node<T>* &root, T &k);
// Effects: removes node with Key k
template <class T> void remove(bst_node<T>* root, T &k);
// Effects: deletes the tree
template <class T> void delete_tree(bst_node<T>* root);
// Effects: returns the bst node with key k
template <class T> bst_node<T>* search(bst_node<T>* root, T &k);
// Effects: returns the parent node of the node with key k
template <class T> bst_node<T>* find_parent(bst_node<T>* root, T &k);
// Effects: returns the parent node of the min node
template <class T> bst_node<T>* find_parent_of_min(bst_node<T>* root);
// Effects: returns the minimum value in the tree
template <class T> T& get_min(bst_node<T>* root);
// Effects: returns the max value in the tree
template <class T> T& get_max(bst_node<T>* root);
// Effects: returns true if tree is bst, false otherwise
template <class T> bool is_bst(bst_node<T>* root);


template <class T> int size(bst_node<T>* root)
{
    if (root == nullptr) return 0;
    return 1 + size(root->left) + size(root->right);
}

template <class T> int height(bst_node<T>* root)
{
    if (root == nullptr) return 0;
    return 1 + std::max(height(root->left), height(root->right));
}

template <class T> void traverse_inorder(bst_node<T>* root)
{
    if (root == nullptr) return;
    traverse_inorder(root->left);
    std::cout << root->key << " ";
    traverse_inorder(root->right);
}

template <class T> void traverse_preorder(bst_node<T>* root)
{
    if (root == nullptr) return;
    std::cout << root->key << " ";
    traverse_preorder(root->left);
    traverse_preorder(root->right);
}

template <class T> void traverse_postorder(bst_node<T>* root)
{
    if (root == nullptr) return;
    traverse_postorder(root->left);
    traverse_postorder(root->right);
    std::cout << root->key << " ";
}

template <class T> bool is_bst(bst_node<T>* root)
{
    if (root == nullptr) return true;
    if (root->right && root->key >= root->right->key) return false;
    if (root->left && root->key < root->left->key) return false;
    if (!is_bst(root->right)) return false;
    if (!is_bst(root->left)) return false;
    return true;
}

template <class T> void insert_helper(bst_node<T>* root, T &k)
{
    if (k <= root->key)
    {
        if (root->left) { insert_helper(root->left, k); }
        else { root->left = new bst_node<T>(k, nullptr, nullptr); }
    }
    else
    {
        if (root->right) { insert_helper(root->right, k); }
        else { root->right = new bst_node<T>(k, nullptr, nullptr); }
    }
}

template <class T> void insert(bst_node<T>* &root, T &k)
{
    if (root == nullptr) { root = new bst_node<T>(k, nullptr, nullptr); }
    else { insert_helper(root, k); }
    std::cout << "inserted " << k << "\n";
}

template <class T> bst_node<T>* search(bst_node<T>* root, T &k)
{
    if (root == nullptr) return nullptr;
    if (root->key == k) return root;
    if (root->key >= k) { return search(root->left, k); }
    return search(root->right, k);
}

template <class T> bst_node<T>* find_parent(bst_node<T>* root, T &k)
{
    if (root == nullptr)
    {
        //throe error
    }
    if (root->key == k) return nullptr;
    if (k <= root->key)
    {
        if (root->left->key == k) return root;
        return find_parent(root->left, k);
    }
    if (root->right->key == k) return root;
    return find_parent(root->right, k);
}

template <class T> bst_node<T>* find_parent_of_min(bst_node<T>* root)
{
    assert(root);
    if (root->left == nullptr) return nullptr;
    if (root->left->left == nullptr) return root;
    bst_node<T>* n = root;
    while (n->left->left)
    {
        n = n->left;
    }
    return n;
}

template <class T> T& get_min(bst_node<T>* root)
{
    if (root == nullptr)
    {
        // throw error
    }
    if (root->left == nullptr) return root->key;
    return get_min(root->left);
}

template <class T> T& get_max(bst_node<T>* root)
{
    if (root == nullptr)
    {
        // throw error
    }
    if (root->right == nullptr) return root->key;
    return get_max(root->right);
}

template <class T> void remove(bst_node<T>* root, T &k)
{
    if (root == nullptr)
    {
        // throw error
    }
    bst_node<T>* parent = find_parent(root, k);
    bst_node<T>* n;
    if (parent == nullptr) n = root;
    else if (parent->right && parent->right->key == k) n = parent->right;
    else n = parent->left;

    bst_node<T>* del;

    /* if the node to be removed has two children */
    if (n->right && n->left)
    {
        bst_node<T>* parent_of_min = find_parent_of_min(n->right);
        bst_node<T>* min;
        if (parent_of_min == nullptr)
        {
            parent_of_min = n;
            min = n->right;
        }
        else
        {
            min = parent_of_min->left;
        }
        n->key = min->key;

        if (parent_of_min == n)
        {
            del = parent_of_min->right;
            parent_of_min->right = parent_of_min->right->right;
        }
        else
        {
            del = parent_of_min->left;
            parent_of_min->left = nullptr;
        }
    }
    /* if the node to be removed has at most one child */
    else if (n->right || n->left)
    {
        if (parent->left == n)
        {
            parent->left = (n->left) ? n->left : n->right;
        }
        else
        {
            parent->right = (n->left) ? n->left : n->right;
        }
        del = n;
    }
    else
    {
        if (parent->left == n) parent->left = nullptr;
        else parent->right = nullptr;
        del = n;
    }

    delete del;
    std::cout << "removed " << k << "...\n";
}

template <class T> void delete_tree(bst_node<T>* root)
{
    if (root == nullptr) return;
    if (root->left) delete_tree(root->left);
    if (root->right) delete_tree(root->right);
    delete root;
}