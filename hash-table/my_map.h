#ifndef MY_MAP
#include <iostream>
#include <vector>

template <class Key, class T, class Hash = std::hash<Key> >
class my_map
{
public:
    /* constructors and destructors */

    my_map();

    /*
     * Requires: size is a positive integer
     * Effects: creates a map with the specified size
     */
    my_map(int size);

    ~my_map();

    class iterator 
    {
    public:
        /*
         * Effects: returns a reference to the key-value pair
         */
        std::pair<Key, T>& operator* () const;

        /*
         * Effects: returns a pointer to the key-value pair
         */
        std::pair<Key, T>* operator-> () const;

        /*
         * Effects: returns an iterator to the next item in the map,
         *          undefined behavior when incremented past the end
         */
        iterator& operator++ ();

        /*
         * Effects: returns an iterator to the previous item before this in the map,
         *          undefined behavior when decremented below begin
         */
        iterator operator-- ();

        bool operator== (iterator rhs) const;
        bool operator!= (iterator rhs) const;

    private:
        my_map<Key, T, Hash> *owner;
        int index; /* index of the item in the underlying container */
        friend class my_map;
        iterator(my_map<Key, T, Hash> *p, int idx) : owner(p), index(idx) {}
    };

    /* iterators */

    /*
     * Effects: returns an iterator to the first item in the map,
     *          if map is empty, begin() == end()
     */
    iterator begin();

    /*
     * Effects: returns an iterator to the address one past the last item
     */
    iterator end();

    /* capacity */
    bool empty();
    int size();

    /* modifiers */

    /*
     * Effects: removes all items from the map
     */
    void clear();

    /*
     * Effects: inserts kvpair into the map and returns an iterator to the item
     */
    iterator insert(std::pair<Key, T> kvpair);

    /*
     * Requires: it is an iterator to an item in the map, undefined behavior otherwise
     * Effects: removes the item pointed to by it from the map
     */
    void erase(iterator it);

    /* lookup */

    /*
     * Effects: returns a reference to the value associated with k
     */
    T& at(Key k);

    /*
     * Effects: returns an iterator to the key-value pair associated with k
     */
    iterator find(Key k);

private:
    std::vector<std::pair<Key, T> > v; /* hash table */
    std::vector<bool> deleted;         /* flag to mark a deleted item */
    std::vector<bool> empty_slot;      /* flag to mark an empty slot */
    int map_size;
    int num_buckets;
    int first;                         /* index of the first item */
    int last;                          /* index to the last + 1 item */
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
    std::cout << "created new map at address " << this << "\n";
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
    std::cout << "created new map at address " << this << "\n";
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
    std::cout << "incremented iterator\n";
    return *this;
}

template <class Key, class T, class Hash>
typename my_map<Key, T, Hash>::iterator my_map<Key, T, Hash>::iterator::operator-- ()
{
    while (--index != owner->first && owner->empty_slot[index]);
    std::cout << "decremented iterator\n";
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
    std::cout << "clearing map of " << map_size << " elements.\n";
    for (int i = 0; i < v.capacity(); ++i)
    {
        deleted[i] = false;
        empty_slot[i] = true;
    }
    first = 0;
    last = 0;
    map_size = 0;
}

template <class Key, class T, class Hash>
typename my_map<Key, T, Hash>::iterator my_map<Key, T, Hash>::insert(std::pair<Key, T> kvpair)
{
    int offset = 0;
    int hash;
    while (!empty_slot[hash = (Hash()(kvpair.first) + offset) % num_buckets])
    {
        std::cout << "Collision occured. " << kvpair.first << " hashed to the same value as " << v[hash].first << ".\n";
        ++offset;
    }

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
    std::cout << "inserted item with key " << kvpair.first << " and value " << kvpair.second << " at index " << hash
              << ", map is now of size " << map_size << ".\n";
    return iterator(this, hash);
}

template <class Key, class T, class Hash>
void my_map<Key, T, Hash>::erase(iterator it)
{
    std::cout << "erasing item with key " << it->first << " and value " << it->second << " at index " << it.index << "\n";
    deleted[it.index] = true;
    empty_slot[it.index] = true;
    if (it.index == first)
    {
        first = (++it).index;
    } 
    else if (it.index + 1 == last && last != first)
    {
        last = (--it).index + 1;
    }
    --map_size;
    std::cout << "map is now of size " << map_size << "\n";
}

template <class Key, class T, class Hash>
T& my_map<Key, T, Hash>::at(Key k)
{
    my_map<Key, T, Hash>::iterator it = find(k);
    if (it == this->end())
    {
        throw std::out_of_range("key does not exist");
    }
    return it->second;
}

template <class Key, class T, class Hash>
typename my_map<Key, T, Hash>::iterator my_map<Key, T, Hash>::find(Key k)
{
    int offset = 0;
    int hash = Hash()(k) % num_buckets;
    while (!empty_slot[hash] || deleted[hash])
    {
        if (!empty_slot[hash])
        {
            if (v[hash].first == k)
            {
                std::cout << "item with key " << k << " found after " << offset + 1 << " probe(s).\n";
                return iterator(this, hash);
            }
        }
        std::cout << "item with key " << k << " not found at index " << hash << ", re-probing...\n";
        ++offset;
        hash = (Hash()(k) + offset) % num_buckets;
    }
    std::cout << "item with key " << k << " not found.\n";
    return iterator(this, this->last);
}