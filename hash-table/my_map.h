#ifndef MY_MAP
#include <iostream>
#include <vector>

template <class Key, class T, class Compare = std::hash<Key> >
class my_map
{
public:
    /* constructors and destructors */
    my_map();
    my_map(size);
    ~my_map();

    class iterator 
    {
    public:
        T& operator* () const;
        T* operator-> () const;
        iterator& operator++ ();
        iterator& operator-- ();
        bool operator== (iterator rhs) const;
        bool operator!= (iterator rhs) const;

    private:
        std::pair<Key, T> *ptr;
    }

    /* capacity */
    bool empty();
    int size();

    /* modifiers */
    void clear();
    iterator insert(std::pair<Key, T> kvpair);
    void erase(iterator &it);

    /* lookup */
    T& operator[] const;
    iterator find(Key k);

private:
    std::vector<T> v;
    int size;
};

#endif