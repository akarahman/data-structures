#ifndef MY_LIST
#include <iostream>

template <class T>
struct my_list_node {
    T item;
    my_list_node<T>* next;
    my_list_node(T item_in) : item(item_in), next(nullptr) {}
    my_list_node(T item_in, my_list_node<T>* n) : item(item_in), next(n) {}
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
};

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
        head = new my_list_node<T>(val);
    }
    else if (idx == 0)
    {
        head = new my_list_node<T>(val, head);
    }
    else
    {
        my_list_node<T>* n = head;
        for (int i = 0; i < idx-1; ++i)
        {
            n = n->next;
        }
        my_list_node<T>* temp = n->next;
        n->next = new my_list_node<T>(val, temp);
    }
    ++size;
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
    if (idx == 0)
    {
        head = head->next;
    }
    else
    {
        my_list_node<T>* n = head;
        for (int i = 0; i < idx-1; ++i)
        {
            n = n->next;
        }
        n->next = n->next->next;
    }
    --size;
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
    if (idx < 0 || idx >= size)
    {
        throw std::out_of_range("index out of range");
    }
    my_list_node<T>* n = head;
    for (int i = 0; i < idx; ++i)
    {
        n = n->next;
    }
    return n->item;
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
        my_list_node<T>* prev = nullptr;
        my_list_node<T>* n = head;
        my_list_node<T>* temp;
        while (n != nullptr)
        {
            temp = n->next;
            n->next = prev;
            prev = n;
            n = temp;
        }
        head = prev;
    }
}

/*
 * Requires: value is an instance of T
 * Modifies: Nothing.
 * Effects: removes the first item in the list that has the value 
 */
template <class T>
void my_list<T>::remove_value(T value)
{
    if (head != nullptr)
    {
        my_list_node<T>* n = head;
        my_list_node<T>* prev = nullptr;
        while (n != nullptr)
        {
            if (n->item == value)
            {
                if (prev == nullptr)
                {
                    head = n->next;
                }
                else
                {
                    prev->next = n->next;
                }
                --size;
                return;
            }
            prev = n;
            n = n->next;
        }
    }
}

#endif