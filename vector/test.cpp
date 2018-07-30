#include <string>
#include <cassert>
#include "my_vector.h"

template <class T>
void print_vector_contents(my_vector<T> v);
void test_create();
void test_push_back_basic();
void test_push_back_resize();
void test_insert_middle();
void test_insert_middle_resize();
void test_insert_illegal();
void test_push_front_basic();
void test_push_front_resize();
void test_remove_front();
void test_remove_middle();
void test_remove_illegal();
void test_pop_basic();
void test_pop_empty();
void test_pop_resize();
void test_find_basic();
void test_find_multiple();
void test_find();

int main()
{
    test_create();
    test_insert_middle();
    test_insert_middle_resize();
    test_insert_illegal();
    test_push_back_basic();
    test_push_back_resize();
    test_push_front_basic();
    test_push_front_resize();
    test_remove_front();
    test_remove_middle();
    test_remove_illegal();
    test_pop_basic();
    test_pop_empty();
    test_pop_resize();
    test_find_basic();
    test_find_multiple();
    test_find();
    return 0;
}

template <class T>
void print_vector_contents(my_vector<T> v)
{
    int i;
    std::cout << "[ ";
    for (i = 0; i < v.get_size() - 1; ++i)
    {
        std::cout << v[i] << ", ";
    }
    if (v.get_size())
    {
        std::cout << v[i];
    }
    std::cout << " ]\n";
}

void test_create()
{
    std::cout << "\nTesting constructors...\n\n";

    my_vector<int> v1; /* default */
    assert(v1.get_capacity() == 16);
    my_vector<int> v2(8); /* smaller than min */
    assert(v2.get_capacity() == 16);
    my_vector<int> v3(17); /* not pow of 2 */
    assert(v3.get_capacity() == 32);
    my_vector<int> v4(16); /* starting size */
    assert(v4.get_capacity() == 16);

    my_vector<std::string> v5;
    assert(v5.get_capacity() == 16);
    my_vector<std::string> v6(8);
    assert(v6.get_capacity() == 16);
    my_vector<std::string> v7(17);
    assert(v7.get_capacity() == 32);
    my_vector<std::string> v8(16);
    assert(v8.get_capacity() == 16);
}

void test_insert_middle()
{
    std::cout << "\nTesting insert in middle...\n\n";

    my_vector<int> v1;
    for (int i = 0; i < 10; ++i)
    {
        v1.insert(0, i);
    }
    assert(v1.get_size() == 10);
    print_vector_contents(v1);
    v1.insert(5, 100);
    assert(v1.get_size() == 11);
    assert(v1[5] == 100);
    print_vector_contents(v1);
}

void test_insert_middle_resize()
{
    std::cout << "\nTesting insert in middle with resize...\n\n";

    my_vector<int> v1;
    for (int i = 0; i < 16; ++i)
    {
        v1.insert(0, i);
    }
    assert(v1.get_size() == 16);
    print_vector_contents(v1);
    v1.insert(8, 100);
    assert(v1[8] == 100);
    assert(v1.get_size() == 17);
    assert(v1.get_capacity() == 32);
    print_vector_contents(v1);
}

void test_insert_illegal()
{
    std::cout << "\nTesting insert at invalid index...\n\n";

    my_vector<int> v1;
    for (int i = 0; i < 5; ++i)
    {
        v1.push_back(i);
    }
    try 
    {
        v1.insert(20, 100);
    }
    catch (const std::exception &e)
    {
        std::cout << "Exception caught: " << e.what() << "\n";
        try
        {
            v1.insert(10, 50);
        }
        catch (const std::exception &e)
        {
            std::cout << "Exception caught: " << e.what() << "\n";
            return;
        }
    }
    assert(false);
}

void test_push_back_basic()
{
    std::cout << "\nTesting push_back basic...\n\n";

    /* no resize */
    my_vector<int> v1;
    v1.push_back(5);
    assert(v1.get_size() == 1);
    print_vector_contents(v1);

    my_vector<std::string> v2;
    v2.push_back("hello");
    assert(v2.get_size() == 1);
    print_vector_contents(v2);
}

void test_push_back_resize()
{
    std::cout << "\nTesting push_back with resize...\n\n";

    my_vector<int> v1;
    for (int i = 0; i <= 16; ++i)
    {
        v1.push_back(i);
    }
    assert(v1.get_size() == 17);
    assert(v1.get_capacity() == 32);
    print_vector_contents(v1);

    my_vector<std::string> v2;
    for (int i = 0; i <= 16; ++i)
    {
        v2.push_back("hello");
    }
    assert(v2.get_size() == 17);
    assert(v2.get_capacity() == 32);
    print_vector_contents(v2);
}

void test_push_front_basic()
{
    std::cout << "\nTesting push_front basic...\n\n";

    /* no resize */
    my_vector<int> v1;
    v1.push_front(5);
    assert(v1.get_size() == 1);
    print_vector_contents(v1);

    my_vector<std::string> v2;
    v2.push_front("hello");
    assert(v2.get_size() == 1);
    print_vector_contents(v2);
}

void test_push_front_resize()
{
    std::cout << "\nTesting push_front with resize...\n\n";

    my_vector<int> v1;
    for (int i = 0; i <= 16; ++i)
    {
        v1.push_front(i);
    }
    assert(v1.get_size() == 17);
    assert(v1.get_capacity() == 32);
    print_vector_contents(v1);

    my_vector<std::string> v2;
    for (int i = 0; i <= 16; ++i)
    {
        v2.push_front("hello");
    }
    assert(v2.get_size() == 17);
    assert(v2.get_capacity() == 32);
    print_vector_contents(v2);
}

void test_remove_front()
{
    std::cout << "\nTesting remove from front...\n\n";

    my_vector<int> v1;
    for (int i = 0; i < 3; ++i)
    {
        v1.push_front(i);
    }
    assert(v1.get_size() == 3);
    assert(v1.get_capacity() == 16);
    print_vector_contents(v1);
    for (int i = 0; i < 3; ++i)
    {
        v1.remove(0);
        print_vector_contents(v1);
    }

    my_vector<std::string> v2;
    for (int i = 0; i < 3; ++i)
    {
        v2.push_front("hello");
    }
    assert(v2.get_size() == 3);
    assert(v2.get_capacity() == 16);
    print_vector_contents(v2);
    for (int i = 0; i < 3; ++i)
    {
        v2.remove(0);
        print_vector_contents(v2);
    }
}

void test_remove_middle()
{
    std::cout << "\nTesting remove from middle...\n\n";

    my_vector<int> v1;
    for (int i = 0; i < 3; ++i)
    {
        v1.push_front(i);
    }
    assert(v1.get_size() == 3);
    assert(v1.get_capacity() == 16);
    print_vector_contents(v1);

    v1.remove(1);
    print_vector_contents(v1);

    my_vector<std::string> v2;
    for (int i = 0; i < 3; ++i)
    {
        v2.push_front("hello");
    }
    assert(v2.get_size() == 3);
    assert(v2.get_capacity() == 16);
    print_vector_contents(v2);
    v2.remove(1);
    print_vector_contents(v2);
}

void test_remove_illegal()
{
    std::cout << "\nTesting remove at invalid index...\n\n";

    my_vector<int> v1;
    for (int i = 0; i < 5; ++i)
    {
        v1.push_back(i);
    }
    try 
    {
        v1.remove(20);
    }
    catch (const std::exception &e)
    {
        std::cout << "Exception caught: " << e.what() << "\n";
        try
        {
            v1.remove(10);
        }
        catch (const std::exception &e)
        {
            std::cout << "Exception caught: " << e.what() << "\n";
            return;
        }
    }
    assert(false);
}

void test_pop_basic()
{
    std::cout << "\nTesting pop basic...\n\n";

    my_vector<int> v1;
    v1.push_back(0);
    v1.push_back(1);
    assert(v1.get_size() == 2);
    print_vector_contents(v1);
    v1.pop();
    v1.pop();
    assert(v1.get_size() == 0);
    print_vector_contents(v1);

    my_vector<std::string> v2;
    v2.push_back("hello");
    v2.push_back("world");
    assert(v2.get_size() == 2);
    print_vector_contents(v2);
    v2.pop();
    v2.pop();
    assert(v2.get_size() == 0);
    print_vector_contents(v2);
}

void test_pop_empty()
{
    std::cout << "\nTesting pop empty vector...\n\n";

    my_vector<int> v1;
    try {
        v1.pop();
    }
    catch(const std::exception &e)
    {
        std::cout << "Exception caught: " << e.what() << "\n";
        return;
    }
    assert(false);
}

void test_pop_resize()
{
    std::cout << "\nTesting pop with resize...\n\n";

    my_vector<int> v1(32);
    for (int i = 0; i < 9; ++i)
    {
        v1.push_back(10);
    }
    assert(v1.get_size() == 9);
    assert(v1.get_capacity() == 32);
    print_vector_contents(v1);
    v1.pop();
    assert(v1.get_size() == 8);
    assert(v1.get_capacity() == 16);
    print_vector_contents(v1);
    for (int i = 0; i < 4; ++ i)
    {
        v1.pop();
    }
    assert(v1.get_size() == 4);
    assert(v1.get_capacity() == 16);
    print_vector_contents(v1);
}

void test_find_basic()
{
    std::cout << "\nTesting find...\n\n";
    my_vector<int> v1;
    for (int i = 0; i < 5; ++i)
    {
        v1.push_back(i);
    }
    print_vector_contents(v1);

    for (int i = 0; i < 5; ++i)
    {
        std::cout << "item with value " << i << " located at index " << v1.find(i) << "\n";
    }
}

void test_find_multiple()
{
    std::cout << "\nTesting find with multiple instances of the same element...\n\n";
    my_vector<int> v1;
    for (int i = 0; i < 10; ++i)
    {
        v1.push_back(i % 2);
    }
    print_vector_contents(v1);

    for (int i = 0; i < 5; ++i)
    {
        int pos = v1.find(0);
        std::cout << "item with value 0 located at index " << pos << "\n";
        v1.remove(pos);
    }
    print_vector_contents(v1);
}

void test_find()
{
    my_vector<int> v1;
    for (int i = 0; i < 10; ++i)
    {
        v1.push_front(i);
    }
    assert(v1.find(5));
    assert(v1.find(10) == -1);
}
