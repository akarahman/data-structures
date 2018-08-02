/*
 * Queue implementation with array and circular buffer
 */

#ifndef MY_QUEUE
#include <iostream>
#include <vector>

template <class T>
class my_queue {
public:

    my_queue();
    my_queue(int cap);
    ~my_queue() {}
    void enqueue(T val);
    void dequeue();
    T peek() { return v[read]; }
    bool empty() { return read == write; }
    int get_size() { return size; }
    bool full() { return abs(read - write) == 1 && write < read; }

private:
    std::vector<T> v;
    int read;
    int write;
    int size;
};

template <class T>
my_queue<T>::my_queue()
{
    v.reserve(100);
    read = 0; 
    write = 0; 
    size = 0;
}

template <class T>
my_queue<T>::my_queue(int cap)
{
    v.reserve(cap+1);
    read = 0;
    write = 0;
    size = 0;
}

template <class T>
void my_queue<T>::enqueue(T val)
{
    if (full())
    {
        throw std::length_error("queue is full");
    }
    v[write] = val;
    write = (write + 1) % v.capacity();
    ++size;
}

template <class T>
void my_queue<T>::dequeue()
{
    read = (read + 1) % v.capacity();
    --size;
}

#endif