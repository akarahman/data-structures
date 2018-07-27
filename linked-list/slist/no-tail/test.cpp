#include <cassert>
#include "my_list.h"

void test_node_constructors();
void test_insert();
void test_erase();
void test_remove_value();
void test_get_value();
void test_value_n_from_end();
void test_reverse();

int main()
{
    test_node_constructors();
    test_insert();
    test_erase();
    test_remove_value();
    test_get_value();
    test_value_n_from_end();
    test_reverse();
}

void test_node_constructors()
{
    std::cout << "\nTesting constructors...\n\n";
    my_list<int> l1;
    assert(l1.get_size() == 0);
    my_list_node<int>* n1 = new my_list_node<int>(0);
    my_list_node<int>* n2 = new my_list_node<int>(1, n1);
}

void test_insert()
{
    std::cout << "\nTesting inserts...\n\n";
    my_list<int> l1;
    l1.push_back(3);
    l1.push_front(1);
    l1.insert(1, 2);
    l1.insert(0, 0);
    l1.insert(l1.get_size(), 4);
    assert(l1.get_size() == 5);
    std::cout << l1;
}

void test_erase()
{
    std::cout << "\nTesting erase...\n\n";

    my_list<int> l1;
    for (int i = 0; i < 5; ++i)
    {
        l1.push_front(i);
    }
    std::cout << l1;
    assert(l1.get_size() == 5);
    l1.pop_back();
    l1.pop_front();
    l1.erase(1);
    l1.erase(l1.get_size() - 1);
    l1.erase(0);
    std::cout << l1;
    assert(l1.get_size() == 0);
}

void test_remove_value()
{
    std::cout << "\nTesting remove value...\n\n";

    my_list<int> l1;
    for (int i = 0; i < 5; ++i)
    {
        l1.push_front(i);
    }
    std::cout << l1;
    assert(l1.get_size() == 5);
    for (int i = 0; i < 5; ++i)
    {
        l1.remove_value(i);
        std::cout << l1;
    }
    assert(l1.get_size() == 0);

    for(int i = 0; i < 10; ++i)
    {
        l1.push_front(i%2);
    }
    std::cout << l1;
    for (int i = 0; i < 5; ++i)
    {
        l1.remove_value(0);
    }
    assert(l1.get_size() == 5);
    std::cout << l1;
}

void test_get_value()
{
    std::cout << "\nTesting get value...\n\n";

    my_list<int> l1;
    for (int i = 0; i < 10; ++i)
    {
        l1.push_front(i);
    }
    std::cout << l1;
    int n = 9;
    for (int i = 0; i < 10; ++i)
    {
        assert(l1.value_at(i) == n);
        --n;
    }
}

void test_value_n_from_end()
{
    std::cout << "\nTesting get nth value from the end...\n\n";

    my_list<int> l1;
    for (int i = 0; i < 10; ++i)
    {
        l1.push_front(i);
    }
    std::cout << l1;
    for (int i = 0; i < 10; ++i)
    {
        assert(l1.value_n_from_end(i) == i);
    }
}

void test_reverse()
{
    std::cout << "\nTesting reverse list...\n\n";

    my_list<int> l1;
    for (int i = 0; i < 10; ++i)
    {
        l1.push_front(i);
    }
    std::cout << l1;
    l1.reverse();
    std::cout << l1;

    for (int i = 0; i < 10; ++i)
    {
        assert(l1.value_at(i) == i);
    }
}