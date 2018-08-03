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
        std::pair<Key, T>& operator* () const;
        std::pair<Key, T>* operator-> () const;
        iterator& operator++ ();
        iterator operator-- ();
        bool operator== (iterator rhs) const;
        bool operator!= (iterator rhs) const;

    private:
        my_map<Key, T, Hash> *owner;
        int index;
        friend class my_map;
        iterator(my_map<Key, T, Hash> *p, int idx) : owner(p), index(idx) {}
    };

    /* iterators */
    iterator begin();
    iterator end();

    /* capacity */
    bool empty();
    int size();

    /* modifiers */
    void clear();
    iterator insert(std::pair<Key, T> kvpair);
    void erase(iterator it);

    /* lookup */
    T& at(Key k);
    iterator find(Key k);

private:
    std::vector<std::pair<Key, T> > v;
    std::vector<bool> deleted;
    std::vector<bool> empty_slot;
    int map_size;
    int num_buckets;
    int first;
    int last;
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
    first = 0;
    last = 0;
    std::cout << "created new map\n";
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
    first = 0;
    last = 0;
}

template <class Key, class T, class Hash>
my_map<Key, T, Hash>::~my_map() {}

template <class Key, class T, class Hash>
std::pair<Key, T>& my_map<Key, T, Hash>::iterator::operator* () const
{
    assert(owner);
    return owner->v[index];
}

template <class Key, class T, class Hash>
std::pair<Key, T>* my_map<Key, T, Hash>::iterator::operator-> () const
{
    assert(owner);
    return &(owner->v[index]);
}

template <class Key, class T, class Hash>
typename my_map<Key, T, Hash>::iterator& my_map<Key, T, Hash>::iterator::operator++ ()
{
    // std::cout << "first: " << owner->first << " last: " << owner->last << "\n";
    while (++index != owner->last && owner->empty_slot[index]);
    return *this;
}

template <class Key, class T, class Hash>
typename my_map<Key, T, Hash>::iterator my_map<Key, T, Hash>::iterator::operator-- ()
{
    while (--index != owner->first && owner->empty_slot[index]);
    return *this;
}

template <class Key, class T, class Hash>
bool my_map<Key, T, Hash>::iterator::operator== (iterator rhs) const
{
    return (owner == rhs.owner && index == rhs.index); 
}

template <class Key, class T, class Hash>
bool my_map<Key, T, Hash>::iterator::operator!= (iterator rhs) const
{
    return (owner != rhs.owner || index != rhs.index); 
}

template <class Key, class T, class Hash>
typename my_map<Key, T, Hash>::iterator my_map<Key, T, Hash>::begin()
{
    return iterator(this, first);
}

template <class Key, class T, class Hash>
typename my_map<Key, T, Hash>::iterator my_map<Key, T, Hash>::end()
{
    return iterator(this, last);
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
    int hash = Hash()(kvpair.first) % num_buckets;
    v[hash] = kvpair;
    if (empty())
    {
        first = hash;
        last = hash + 1;
    }
    else if (hash < first)
    {
        first = hash;
    }
    else if (hash >= last)
    {
        last = hash + 1;
    }
    deleted[hash] = false;
    empty_slot[hash] = false;
    
    ++map_size;
    return iterator(this, hash);
}

template <class Key, class T, class Hash>
void my_map<Key, T, Hash>::erase(iterator it)
{
    int hash = Hash()(it->first) % num_buckets;
    deleted[hash] = true;
    empty_slot[hash] = true;
    if (hash == first)
    {
        first = (++it).index;
    } 
    if (hash + 1 == last)
    {
        last = (--it).index + 1;
    }
    --map_size;
}

template <class Key, class T, class Hash>
T& my_map<Key, T, Hash>::at(Key k)
{
    return v[Hash()(k) % num_buckets].second;
}

template <class Key, class T, class Hash>
typename my_map<Key, T, Hash>::iterator my_map<Key, T, Hash>::find(Key k)
{
    // TODO: probing
    int hash = Hash()(k) % num_buckets;
    return iterator(this, hash);
}