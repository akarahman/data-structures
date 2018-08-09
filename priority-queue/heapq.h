#include <iostream>
#include <vector>

template <class T>
void heapify(std::vector<T>* v_in);

template <class T>
class heapq
{
public:
    heapq();
    heapq(std::vector<T> &v_in);
    ~heapq();
    void insert(T &item);
    T& extract_max();
    int size();

private:
    std::vector<T> v;
    void sift_up(int node);
    void sift_down(int node);
};