#ifndef MY_MAP
#include <iostream>
#include <vector>

template <class Key, class T, class Hash = std::hash<Key> >
class my_map
{
public:
    /* constructors and destructors */
    my_map();
    my_map(int size);
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
        friend class my_map;
        iterator(std::pair<Key, T> *p) : ptr(p) {}
    };

    /* capacity */
    bool empty();
    int size();

    /* modifiers */
    void clear();
    iterator insert(std::pair<Key, T> kvpair);
    void erase(iterator &it);

    /* lookup */
    T& operator[](const Key k) const;
    iterator find(Key k);

private:
    std::vector<std::pair<Key, T> > v;
    std::vector<bool> deleted;
    std::vector<bool> empty_slot;
    int map_size;
    int num_buckets;
};

#endif


template <class Key, class T, class Hash>
my_map<Key, T, Hash>::my_map()
{
    v.reserve(100);
    map_size = 0;
    num_buckets = 100;
    deleted.reserve(100);
    empty_slot.reserve(100);
    for (int i = 0; i < 100; ++i)
    {
        deleted[i] = false;
        empty_slot[i] = true;
    }
}

template <class Key, class T, class Hash>
my_map<Key, T, Hash>::my_map(int size)
{
    v.reserve(size);
    this->map_size = 0;
    num_buckets = size;
    deleted.reserve(size);
    empty_slot.reserve(size);
    for (int i = 0; i < size; ++i)
    {
        deleted[i] = false;
        empty_slot[i] = true;
    }
}

template <class Key, class T, class Hash>
my_map<Key, T, Hash>::~my_map() {}

template <class Key, class T, class Hash>
T& my_map<Key, T, Hash>::iterator::operator* () const
{
    assert(ptr);
    return *ptr;
}

template <class Key, class T, class Hash>
T* my_map<Key, T, Hash>::iterator::operator-> () const
{
    assert(ptr);
    return ptr;
}

template <class Key, class T, class Hash>
typename my_map<Key, T, Hash>::iterator& my_map<Key, T, Hash>::iterator::operator++ ()
{
    // TODO
}

template <class Key, class T, class Hash>
typename my_map<Key, T, Hash>::iterator& my_map<Key, T, Hash>::iterator::operator-- ()
{
    // TODO
}

template <class Key, class T, class Hash>
bool my_map<Key, T, Hash>::iterator::operator== (iterator rhs) const
{
    return ptr == rhs.ptr; 
}

template <class Key, class T, class Hash>
bool my_map<Key, T, Hash>::iterator::operator!= (iterator rhs) const
{
    return ptr != rhs.ptr; 
}

template <class Key, class T, class Hash>
bool my_map<Key, T, Hash>::empty()
{
    return map_size == 0;
}

template <class Key, class T, class Hash>
int my_map<Key, T, Hash>::size()
{
    return map_size;
}

template <class Key, class T, class Hash>
void my_map<Key, T, Hash>::clear()
{
    // TODO
}

template <class Key, class T, class Hash>
typename my_map<Key, T, Hash>::iterator my_map<Key, T, Hash>::insert(std::pair<Key, T> kvpair)
{
    // TODO: linear probing
    v[Hash(kvpair.first) % num_buckets] = kvpair;
    ++map_size;
}

template <class Key, class T, class Hash>
void my_map<Key, T, Hash>::erase(iterator &it)
{
    int hash = Hash(it->first) % num_buckets;
    deleted[hash] = true;
    empty_slot[hash] = true;
}

template <class Key, class T, class Hash>
T& my_map<Key, T, Hash>::operator[](const Key k) const
{
    // TODO: probing
    return v[Hash(k) % num_buckets].second;
}

template <class Key, class T, class Hash>
typename my_map<Key, T, Hash>::iterator my_map<Key, T, Hash>::find(Key k)
{
    // TODO: probing
    return iterator(&v[Hash(k) % num_buckets]);
}