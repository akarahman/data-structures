#include "my_list.h"

void test_node_constructors();
void test_insert();
void test_erase();
void test_remove_value();
void test_get_value();
void test_value_n_from_end();
void test_reverse();
void test_get_value_illegal();
void test_insert_illegal();
void test_remove_illegal();

int main()
{
    test_node_constructors();
    test_insert();
    test_erase();
    test_remove_value();
    test_get_value();
    test_value_n_from_end();
    test_reverse();
    test_get_value_illegal();
    test_insert_illegal();
    test_remove_illegal();
}

void test_node_constructors()
{
    std::cout << "\nTesting constructors...\n\n";
    my_list<int> l1;
    assert(l1.get_size() == 0);
    my_list_node<int> n1(0);
    my_list_node<int> n2(1, &n1);
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

void test_insert_illegal()
{
    std::cout << "\nTesting insert at illegal index...\n\n";

    my_list<int> l1;
    try {
        l1.insert(1, 0);
        assert(false);
    }
    catch (std::exception &e)
    {
        std::cout << "Exception caught: " << e.what() << "\n";
    }
    l1.insert(0, 0);
    try {
        l1.insert(5, 0);
        assert(false);
    }
    catch (std::exception &e)
    {
        std::cout << "Exception caught: " << e.what() << "\n";
    }
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
    l1.remove_value(0);
    l1.remove_value(4);
    for (int i = 1; i < 4; ++i)
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
    for (int i = 0; i < 5; ++i)
    {
        l1.remove_value(1);
    }
    assert(l1.get_size() == 0);
    std::cout << l1;
}

void test_remove_illegal()
{
    std::cout << "\nTesting remove at illegal index...\n\n";

    my_list<int> l1;
    try {
        l1.erase(0);
        assert(false);
    }
    catch (std::exception &e)
    {
        std::cout << "Exception caught: " << e.what() << "\n";
    }
    l1.insert(0,0);
    try {
        l1.erase(5);
        assert(false);
    }
    catch (std::exception &e)
    {
        std::cout << "Exception caught: " << e.what() << "\n";
    }
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

void test_get_value_illegal()
{
    std::cout << "\nTesting get value illegal...\n\n";
    my_list<int> l1;
    try {
        l1.value_at(1);
        assert(false);
    }
    catch (std::exception &e)
    {
        std::cout << "Exception caught: " << e.what() << "\n";
    }
    try {
        l1.value_n_from_end(3);
        assert(false);
    }
    catch (std::exception &e)
    {
        std::cout << "Exception caught: " << e.what() << "\n";
    }
    l1.push_front(2);

    try {
        l1.value_n_from_end(8);
        assert(false);
    }
    catch (std::exception &e)
    {
        std::cout << "Exception caught: " << e.what() << "\n";
    }
    try {
        l1.value_at(8);
        assert(false);
    }
    catch (std::exception &e)
    {
        std::cout << "Exception caught: " << e.what() << "\n";
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
