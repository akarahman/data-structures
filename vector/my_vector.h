#ifndef MY_VECTOR

#include <iostream>
#include <cmath>

template <class T>
class my_vector {
public:

    /* constructors and destructor */
    my_vector();
    my_vector(int cap);
    ~my_vector();
    /* [] operator overload */
    T& operator[](int idx) { return arr[idx]; }
    /* getters */
    int get_size() { return size; }
    int get_capacity() { return capacity; }
    bool empty() { return size; }
    T at(int idx) { return arr[idx]; }
    int find(T value);
    /* modifiers */
    void insert(int idx, T val);
    void push_back(T val);
    void push_front(T val);
    void remove(int idx);
    void pop();

private:
    int capacity;
    int size;
    T* arr;
    void resize(int cap, int skip_idx);
};

/* 
 * Requires: None.
 * Modifies: None.
 * Effects: Initializes empty array with capacity 16.
 */
template <class T>
my_vector<T>::my_vector()
{
    capacity = 16;
    size = 0;
    arr = new T[capacity];
    std::cout << "created vector of size " << size << " and capacity " << capacity
              << " at address " << arr << "\n";
}

/* 
 * Requires: cap is a positive integer
 * Modifies: None.
 * Effects: Initializes an empty vector with cap, rounded to nearest pow of 2
 */
template <class T>
my_vector<T>::my_vector(int cap)
{
    capacity = pow(2, ceil(log2((double) cap))); /* capacity set to power of 2 */
    size = 0;
    arr = new T[capacity];
    std::cout << "created vector of size " << size << " and capacity " << capacity
              << " at address " << arr << "\n";
}

/* 
 * Requires: None.
 * Modifies: None.
 * Effects: destroys instance of vector
 */
template <class T>
my_vector<T>::~my_vector()
{
    std::cout << "destroying vector created at address " << arr << "\n";
    delete [] arr;
}

/* 
 * Requires: cap is a positive integer, skip_idx is a non-negative integer
 *           skip_idx is size if there should be no empty space in the new array
 *           for insertion, else it is the index of the empty space
 * Modifies: None.
 * Effects: resizes the array to cap, leaves an empty space if requested
 */
template <class T>
void my_vector<T>::resize(int cap, int skip_idx)
{
    capacity = cap;
    T* new_arr = new T[cap];
    /* copy over items at positions < skip_idx */
    for (int i = 0; i < skip_idx; ++i)
    {
        new_arr[i] = arr[i];
    }
    /* shift over items >= skip_idx by 1 and copy */
    for (int i = skip_idx; i < size; ++i)
    {
        new_arr[i+1] = arr[i];
    }
    delete [] arr;
    arr = new_arr;
}

/* 
 * Requires: idx is a non-negative integer within the range [0, size),
 *           val is an instance of class T
 * Modifies: None.
 * Effects: Inserts val at position idx in the array, increments the size,
 *          resizes the array if needed
 */
template <class T>
void my_vector<T>::insert(int idx, T val)
{
    if (size == capacity)
    {
        resize(capacity*2, idx); /* double capacity, leave empty space */
    }
    arr[idx] = val;
    size++;
    std::cout << "inserted an element with value " << val << " at index " << idx
              << " in vector now of size " << size << " and capacity " << capacity << "\n";
}

/* 
 * Requires: val is an instance of class T
 * Modifies: None.
 * Effects: Inserts val to the back of array
 */
template <class T>
void my_vector<T>::push_back(T val)
{
    insert(size, val);
}

/* 
 * Requires: val is an instance of class T
 * Modifies: None.
 * Effects: inserts val at the beginning of the array
 */
template <class T>
void my_vector<T>::push_front(T val)
{
    insert(0, val);
}

/* 
 * Requires: idx is a non-negative integer within the range [0, size)
 * Modifies: None.
 * Effects: removes item at idx, decrements size, resizes if necessary
 */
template <class T>
void my_vector<T>::remove(int idx)
{
    /* shift all items at positions > idx to the left by 1 */
    for (int i = idx; i < size - 1; ++i)
    {
        arr[i] = arr[i+1];
    }
    size--;
    /* if size is reduced to 1/4 of capacity, resize to half*/
    if (size == capacity/4)
    {
        resize(capacity/2, size);
    }
}

/* 
 * Requires: None.
 * Modifies: None.
 * Effects: deletes the last item of the array
 */
template <class T>
void my_vector<T>::pop()
{
    remove(size - 1);
}

/* 
 * Requires: val is an instance of class T.
 * Modifies: None.
 * Effects: finds the first item in the array with value val and 
 *          returns the index if found, else returns -1
 */
template <class T>
int my_vector<T>::find(T val)
{
    /* perform linear search */
    for (int i = 0; i < size; ++i)
    {
        if (arr[i] == val)
        {
            return i;
        }
    }
    return -1;
}

#endif