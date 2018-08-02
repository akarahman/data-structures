#ifndef MY_LIST
#include <iostream>
#include <cassert>

template <class T>
struct my_list_node {
    T item;
    my_list_node<T>* next;
    my_list_node<T>* prev;
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
    my_list_node<T>* head;
    my_list_node<T>* tail;
    void assert_invariants();
    void assert_node_invariants(my_list_node<T>* n);
    my_list_node<T>* get_node_at(int idx);
    void remove_node(my_list_node<T>* n);
};

/*
 * Requires: idx is a non-negative integer within the range [0, size)
 * Modifies: Nothing.
 * Effects: returns the node at idx
 */
template <class T>
my_list_node<T>* my_list<T>::get_node_at(int idx)
{
    if (idx < 0 || idx >= size)
    {
        throw std::out_of_range("index out of range");
    }

    my_list_node<T>* n = head;
    if (idx == 0) { return head; }
    else if (idx == size-1) { return tail; }
    else
    { 
        for (int i = 0; i < idx; ++i) { n = n->next; }
    }

    return n;
}

/*
 * Requires: n is not null
 * Modifies: deallocates n
 * Effects: removes node from list, decrements size
 */
template <class T>
void my_list<T>::remove_node(my_list_node<T>* n)
{
    if (n->prev)
    {
        /* set prev node to node after n */
        n->prev->next = n->next;
        /* if tail is not being deleted */
        if (n->next) { n->prev->next->prev = n->prev; }
        else { tail = tail->prev; }
    }
    else
    {
        head = n->next;
        if (head) { head->prev = nullptr; }
        else { tail = nullptr; }
    }
    assert_node_invariants(n->prev);
    assert_node_invariants(n->next);
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
    if (size <= 1) { assert(head == tail); }
    else 
    { 
        assert(head == get_node_at(0));
        assert(tail == get_node_at(size - 1));
    }
}

/*
 * Requires: n is not null.
 * Modifies: Nothing.
 * Effects: aborts if node invariants are violated
 */
template <class T>
void my_list<T>::assert_node_invariants(my_list_node<T>* n)
{
    if (n == nullptr) { return; }
    if (n->next) { assert(n->next->prev == n); }
    if (n->prev) { assert(n->prev->next == n); }
}

template <class TT>
std::ostream& operator<<(std::ostream& os, const my_list<TT>& list)
{
    my_list_node<TT>* n = list.head;
    while(n != nullptr)
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
 * Effects: Creates a new list.
 */
template <class T>
my_list<T>::my_list()
{
    size = 0;
    head = nullptr;
    tail = nullptr;
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
    while (head != nullptr)
    {
        del = head;
        head = head->next;
        delete del;
    }
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
    if (head == nullptr)
    {
        head = new my_list_node<T>(val, nullptr, nullptr);
        tail = head;
    }
    else if (idx == 0)
    {
        head = new my_list_node<T>(val, head, nullptr);
        head->next->prev = head;
        assert_node_invariants(head);
        assert_node_invariants(head->next);
    }
    else if (idx == size)
    {
        tail->next = new my_list_node<T>(val, nullptr, tail);
        tail = tail->next;
        assert_node_invariants(tail);
        assert_node_invariants(tail->prev);
    }
    else
    {
        my_list_node<T>* n = get_node_at(idx-1);
        my_list_node<T>* temp = n->next;
        n->next = new my_list_node<T>(val, temp, n);
        if (temp == nullptr)
        {
            tail = n->next;
        }
        else
        {
            temp->prev = n->next;
        }
        assert_node_invariants(n);
        assert_node_invariants(n->next);
        assert_node_invariants(n->next->next);
    }
    ++size;
    assert_invariants();
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
        while (n != nullptr)
        {
            temp = n->next;
            n->next = n->prev;
            n->prev = temp;
            n = temp;
        }
        temp = tail;
        tail = head;
        head = temp;

        /* debug purposes */
        n = head;
        while (n != nullptr)
        {
            assert_node_invariants(n);
            n = n->next;
        }
    }
    assert_invariants();
}

/*
 * Requires: value is an instance of T
 * Modifies: Nothing.
 * Effects: removes the first item in the list that has the value, if exists 
 */
template <class T>
void my_list<T>::remove_value(T value)
{
    if (head != nullptr)
    {
        my_list_node<T>* n = head;
        while (n != nullptr)
        {
            if (n->item == value)
            {
                remove_node(n);
                assert_invariants();
                return;
            }
            n = n->next;
        }
    }
}

#endif