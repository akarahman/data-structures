#include "my_vector.h"

void test_create();
void test_push_back_basic();
void test_push_back_resize();
void test_insert_basic();
void test_insert_resize();
void test_insert_middle();
void test_insert_illegal();
void test_push_front_basic();
void test_push_front_resize();
void test_pop_basic();
void test_pop_empty();
void test_pop_resize();

int main()
{
    test_create();
    return 0;
}

void test_create()
{
    my_vector<int> v1;
    my_vector<int> v2(8);
    my_vector<int> v3(17);
    my_vector<int> v4(16);

    my_vector<std::string> v5;
    my_vector<std::string> v6(8);
    my_vector<std::string> v7(17);
    my_vector<std::string> v8(16);
}

void test_push_back_basic()
{
    my_vector<int> v1;
    v1.push_back(5);

    my_vector<std::string> v2;
    v2.push_back("hello");
}

void test_push_back_resize()
{
    my_vector<int> v1;
    for (int i = 0; i <= 16; ++i)
    {
        v1.push_back(5);
    }

    my_vector<std::string> v2;
    for (int i = 0; i <= 16; ++i)
    {
        v2.push_back("hello");
    }
}

void test_insert_basic()
{

}

void test_insert_resize()
{

}

void test_insert_middle()
{

}

void test_insert_illegal()
{

}

void test_push_front_basic()
{

}

void test_push_front_resize()
{

}

void test_pop_basic()
{

}

void test_pop_empty()
{

}

void test_pop_resize()
{

}