/*
 * Queue implementation with singly linked list with tail pointer
 */

#ifndef MY_QUEUE
#include <iostream>
#include <vector>

template <class T>
struct my_list_node {
    T item;
    my_list_node<T>* next;
    my_list_node(T item_in) : item(item_in), next(nullptr) {}
};

template <class T>
class my_queue {
public:

    my_queue() : head(nullptr), tail(nullptr), size(0) {}
    ~my_queue() {}
    void enqueue(T val);
    void dequeue();
    T peek() { return head->item; }
    bool empty() { return head; }
    int get_size() { return size; }

private:
    my_list_node<T>* head;
    my_list_node<T>* tail;
    int size;
};

template <class T>
my_queue::~my_queue()
{
    my_list_node<T>* del;
    while (head != nullptr)
    {
        del = head;
        head = head->next;
        delete del;
    }
}

template <class T>
void my_queue<T>::enqueue(T val)
{
    tail->next = new my_list_node<T>(val);
    tail = tail->next;
    ++size;
}

template <class T>
void my_queue<T>::dequeue()
{
    my_list_node<T>* del = head;
    head = head->next;
    delete del;
    --size;
}

#endif