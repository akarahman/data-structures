#include <iostream>
#include <vector>
#include <math.h>
#include <cassert>

template <class T>
class heapq
{
public:
    heapq() {}
    ~heapq() {}
    /*
     * Effects: inserts item into the priority queue
     */
    void insert(T &item);
    /*
     * Effects: returns the max element in the priority queue
     */
    T extract_max();
    /*
     * Effects: returns the size of the priority queue
     */
    int size();

    void clear();

private:
    std::vector<T> v;
    /*
     * Requires: node > 0
     * Effects: returns the position of the parent of node in the heap
     */
    int get_parent(int node);
    /*
     * Effects: returns the position of the left child of the parent in the heap
     *          (or where it would be if the parent had a left child)
     */
    int left_child(int parent);
    /*
     * Effects: returns the position of the right child of the parent in the heap
     *          (or where it would be if the parent had a right child)
     */
    int right_child(int parent);
    /*
     * Effects: sifts node up if the heap invariant is violated
     */
    void sift_up(int node);
    /*
     * Effects: sifts node down if the heap invariant is violated
     */
    void sift_down(int node);
};

template <class T> int heapq<T>::size()
{
    return v.size();
}

template <class T> void heapq<T>::clear()
{
    return v.clear();
}

template <class T> int heapq<T>::get_parent(int node)
{
    assert(node);
    return ceil((double)node/2) - 1;
}

template <class T> int heapq<T>::left_child(int parent)
{
    return 2 * parent + 1;
}

template <class T> int heapq<T>::right_child(int parent)
{
    return 2 * parent + 2;
}

template <class T> void heapq<T>::sift_up(int node)
{
    T temp;
    int parent;
    while (true)
    {
        if (node == 0) return;
        parent = get_parent(node);

        if (v[parent] < v[node])
        {
            std::cout << v[node] << " violates heap property. Sifting up...\n";
            /* swap nodes */
            temp = v[node];
            v[node] = v[parent];
            v[parent] = temp;
            
            node = parent;
        }
        else return;
    }
}

template <class T> void heapq<T>::sift_down(int node)
{
    T temp;
    int child;
    
    while (true)
    {
        if (left_child(node) >= v.size() && right_child(node) >= v.size()) return;
        else if (right_child(node) >= v.size()) child = left_child(node);
        else child = (v[left_child(node)] > v[right_child(node)]) ? left_child(node) : right_child(node);

        if (v[child] > v[node])
        {
            std::cout << v[node] << " violates heap property. Sifting down...\n";

            /* swap nodes */
            temp = v[node];
            v[node] = v[child];
            v[child] = temp;
            
            node = child;
        }
        else return;
    }
}

template <class T> void heapq<T>::insert(T &item)
{
    std::cout << "inserting " << item << "...\n";
    v.push_back(item);
    sift_up(v.size()-1);
}

template <class T> T heapq<T>::extract_max()
{
    T ret = v[0];
    v[0] = v.back();
    v.pop_back();
    std::cout << ret << " extracted from heap\n";
    sift_down(0);
    return ret;
}