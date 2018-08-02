#ifndef MY_LIST
#include <iostream>
#include <cassert>

template <class T>
struct my_list_node {
    T item;
    my_list_node<T>* next;
    my_list_node<T>* prev;
    my_list_node() : item(0), next(this), prev(this) {}
    my_list_node(T item_in, my_list_node<T>* n, my_list_node<T>* p) : item(item_in), 
                                                                      next(n), 
                                                                      prev(p) {}
};

template <class T>
class my_list {
public:

    my_list();
    ~my_list();
    int get_size() { return size; }
    bool empty() { return size; }
    T value_at(int idx);
    void push_back(T val);
    void push_front(T val);
    void insert(int idx, T val);
    void pop_front();
    void pop_back();
    T front();
    T back();
    void erase(int idx);
    T value_n_from_end(int n);
    void reverse();
    void remove_value(T value);
    template <class TT>
    friend std::ostream& operator<<(std::ostream& os, const my_list<TT>& list);

private:
    int size;
    my_list_node<T>* head; /* sentinel */
    void assert_invariants();
    void assert_node_invariants(my_list_node<T>* n);
    my_list_node<T>* get_node_at(int idx);
    void remove_node(my_list_node<T>* n);
};

/*
 * Requires: idx is an integer within the range [-1, size)
 * Modifies: Nothing.
 * Effects: returns the node at idx. If idx is -1, returns the sentinel.
 */
template <class T>
my_list_node<T>* my_list<T>::get_node_at(int idx)
{
    if (idx < -1 || idx >= size)
    {
        throw std::out_of_range("index out of range");
    }
    
    if (idx == size-1) { return head->prev; }

    my_list_node<T>* n = head;
    for (int i = -1; i < idx; ++i)
    {
        n = n->next;
    }
    
    return n;
}

/*
 * Requires: n is not null, not sentinel
 * Modifies: deallocates n
 * Effects: removes node from list, decrements size
 */
template <class T>
void my_list<T>::remove_node(my_list_node<T>* n)
{
    if (n == head)
    {
        //throw error
    }
    n->prev->next = n->next;
    n->next->prev = n->prev;
    assert_node_invariants(n->next);
    assert_node_invariants(n->prev);
    delete n;
    --size;
    assert_invariants();
}

/*
 * Requires: Nothing.
 * Modifies: Nothing.
 * Effects: aborts if list invariants are violated
 */
template <class T>
void my_list<T>::assert_invariants()
{
    assert(head != nullptr);
    my_list_node<T>* n = head->next;
    int count = 0;
    while (n != head)
    {
        ++count;
        n = n->next;
    }
    assert(size == count);
}

/*
 * Requires: n is not null.
 * Modifies: Nothing.
 * Effects: aborts if node invariants are violated
 */
template <class T>
void my_list<T>::assert_node_invariants(my_list_node<T>* n)
{
    assert(n->next != nullptr);
    assert(n->prev != nullptr);
    assert(n->next->prev == n);
    assert(n->prev->next == n);
}

template <class TT>
std::ostream& operator<<(std::ostream& os, const my_list<TT>& list)
{
    my_list_node<TT>* n = list.head->next;
    while(n != list.head)
    {
        os << n->item << " -> ";
        n = n->next;
    }
    os << "nullptr\n";
    return os;
}

/*
 * Requires: None.
 * Modifies: None.
 * Effects: Creates a new list with sentinel.
 */
template <class T>
my_list<T>::my_list()
{
    size = 0;
    head = new my_list_node<T>(); /* sentinel */
}

/*
 * Requires: None.
 * Modifies: None.
 * Effects: Destroys this.
 */
template <class T>
my_list<T>::~my_list()
{
    my_list_node<T>* del;
    my_list_node<T>* n = head->next;
    while (n != head)
    {
        del = n;
        n = n->next;
        delete del;
    }
    delete head;
}

/*
 * Requires: idx is a non-negative integer within the range [0, size]
 *           val is an instance of class T
 * Modifies: Nothing.
 * Effects: inserts val at the specified idx
 */
template <class T>
void my_list<T>::insert(int idx, T val)
{
    if (idx < 0 || idx > size)
    {
        throw std::out_of_range("index out of range");
    }

    my_list_node<T>* n = get_node_at(idx-1);
    n->next = new my_list_node<T>(val, n->next, n);
    n->next->next->prev = n->next;

    ++size;
    assert_invariants();
    assert_node_invariants(n->next);
    std::cout << "inserted item at with value " << val << " at index " << idx << "\n";
}

/*
 * Requires: val is an instance of T
 * Modifies: Nothing.
 * Effects: inserts val at the end of list.
 */
template <class T>
void my_list<T>::push_back(T val)
{
    insert(size, val);
}

/*
 * Requires: val is an instance of T
 * Modifies: Nothing.
 * Effects: inserts val at the front of list.
 */
template <class T>
void my_list<T>::push_front(T val)
{
    insert(0, val);
}

/*
 * Requires: idx is a non-negative integer within the range [0, size)
 * Modifies: Nothing.
 * Effects: erases item at idx
 */
template <class T>
void my_list<T>::erase(int idx)
{
    if (idx < 0 || idx >= size)
    {
        throw std::out_of_range("index out of range");
    }
    remove_node(get_node_at(idx));
    std::cout << "deleted item at index " << idx << "\n";
}

/*
 * Requires: Nothing.
 * Modifies: Nothing.
 * Effects: erases the first item of the list
 */
template <class T>
void my_list<T>::pop_front()
{
    erase(0);
}

/*
 * Requires: Nothing.
 * Modifies: Nothing.
 * Effects: erases the last item of the list
 */
template <class T>
void my_list<T>::pop_back()
{
    erase(size-1);
}

/*
 * Requires: idx is a non-negative integer within the range [0,size)
 * Modifies: Nothing.
 * Effects: returns item at idx
 */
template <class T>
T my_list<T>::value_at(int idx)
{
    return get_node_at(idx)->item;
}

/*
 * Requires: Nothing.
 * Modifies: Nothing.
 * Effects: returns the first item in the list
 */
template <class T>
T my_list<T>::front()
{
    return value_at(0);
}

/*
 * Requires: Nothing.
 * Modifies: Nothing.
 * Effects: returns the last item in the list
 */
template <class T>
T my_list<T>::back()
{
    return value_at(size-1);
}

/*
 * Requires:  n is a non-negative integer within the range [0, size)
 * Modifies: Nothing.
 * Effects: returns the nth value from the end of the list
 */
template <class T>
T my_list<T>::value_n_from_end(int n)
{
    return value_at(size-1-n);
}

/*
 * Requires: Nothing.
 * Modifies: Nothing.
 * Effects: reverses the order of the list.
 */
template <class T>
void my_list<T>::reverse()
{
    if (size > 1)
    {
        my_list_node<T>* n = head;
        my_list_node<T>* temp;

        for (int i = 0; i < size + 1; ++i)
        {
            temp = n->next;
            n->next = n->prev;
            n->prev = temp;
            n = temp;
        }

        /* debug purposes */
        n = head;
        assert_node_invariants(n);
        n = n->next;
        while (n != head)
        {
            assert_node_invariants(n);
            n = n->next;
        }
        assert_invariants();
    }
}

/*
 * Requires: value is an instance of T
 * Modifies: Nothing.
 * Effects: removes the first item in the list that has the value, if exists 
 */
template <class T>
void my_list<T>::remove_value(T value)
{
    my_list_node<T>* n = head->next;
    while (n != head)
    {
        if (n->item == value)
        {
            remove_node(n);
            return;
        }
        n = n->next;
    }
}

#endif