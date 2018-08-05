#include <functional>
#include <unordered_map>
#include <cassert>
#include "my_map.h"
void map_generator_helper(my_map<char, int> &m);
void map_generator_helper_with_collision(my_map<char, int> &m);
bool is_anagram(std::string s1, std::string s2);
void test_constructors();
void test_insert_basic();
void test_iterator_begin();
void test_iterator_advance();
void test_iterator_dereference();
void test_iterator_end();
void test_erase_basic();
void test_collision_insert_find();
void test_collision_delete();

int main(int argc, char const *argv[])
{
    test_constructors();
    test_insert_basic();
    test_iterator_begin();
    test_iterator_advance();
    test_iterator_dereference();
    test_iterator_end();
    test_erase_basic();
    test_collision_insert_find();
    test_collision_delete();

    return 0;
}

void map_generator_helper(my_map<char, int> &m)
{
    for (char c : "helo,wrd")
    {
        if (c == '\0') break;
        m.insert(std::pair<char, int>(c, c));
    }
    assert(m.size() == 8);
}

void map_generator_helper_with_collision(my_map<char, int> &m)
{
    for (char c : "helo,wrd")
    {
        m.insert(std::pair<char, int>(c, c));
    }
    assert(m.size() == 9);
}

bool is_anagram(std::string s1, std::string s2)
{
    if (s2.length() != s1.length())
    {
        return false;
    }
    std::unordered_map<char, int> letters;
    for (char c : s1)
    {
        letters[c] = 1;
    }
    for (char c : s2)
    {
        if (letters.find(c) == letters.end())
        {
            return false;
        }
        if (letters[c] <= 0)
        {
            return false;
        }
        letters[c]--;
    }
    return true;
}

void test_constructors()
{
    std::cout << "\nTesting constructors...\n\n";
    my_map<int, int> m1;
    assert(m1.empty());
    my_map <char, std::string> m2;
    assert(m2.empty());
    my_map<char, int> m3(300);
    assert(m3.empty());
}

void test_insert_basic()
{
    std::cout << "\nTesting insert basic...\n\n";
    my_map<char, int> m1;
    m1.insert(std::pair<char, int>('a', 1));
    m1.insert(std::make_pair<char, int>('b', 2));
    assert(m1.at('a') == 1);
    assert(m1.at('b') == 2);
    assert(m1.size() == 2);
}

void test_iterator_begin()
{
    std::cout << "\nTesting iterator begin...\n\n";
    my_map<char, int> m1;
    m1.insert(std::pair<char, int>('h', 10));
    assert(m1.size() == 1);
    assert(m1.begin()->first == 'h' && m1.begin()->second == 10);
}

void test_iterator_advance()
{
    std::cout << "\nTesting iterator advance...\n\n";
    my_map<char, int> m1;
    m1.insert(std::pair<char, int>('h', 10));
    m1.insert(std::pair<char, int>('e', 12));
    assert(m1.size() == 2);
    my_map<char, int>::iterator it = m1.begin();
    if (it->first == 'h')
    {
        ++it;
        assert(it->first == 'e');
    }
    else
    {
        ++it;
        assert(it->first == 'h');
    }   
}

void test_iterator_end()
{
    std::cout << "\nTesting iterator end...\n\n";
    my_map<char, int> m1;
    assert(m1.begin() == m1.end());
    map_generator_helper(m1);
    assert(m1.size() == 8);
    assert(m1.begin() != m1.end());
    std::string keys = "";
    for (my_map<char, int>::iterator it = m1.begin(); it != m1.end(); ++it)
    {
        keys += it->first;
    }
    std::cout << keys << "\n";
    assert(is_anagram(keys, "helo,wrd"));
}

void test_iterator_dereference()
{
    std::cout << "\nTesting iterator dereference...\n\n";
    my_map<char, int> m1;
    map_generator_helper(m1);
    assert(m1.begin()->first == (*(m1.begin())).first);
}


void test_erase_basic()
{
    my_map<char, int> m1;
    std::cout << "\nTesting erase basic...\n\n";
    map_generator_helper(m1);
    int size = m1.size();
    int count = 0;
    for (my_map<char, int>::iterator it = m1.begin(); it != m1.end(); ++it)
    {
        ++count;
        m1.erase(it);
        assert(m1.size() == size - count);
    }
    assert(m1.size() == 0);
}

void test_collision_insert_find()
{
    std::cout << "\nTesting collision with insert and find...\n\n";
    my_map<char, int> m1;
    map_generator_helper_with_collision(m1);
    assert(m1.at('\0') == '\0');
    assert(m1.at('d') == 'd');
    assert(m1.at('e') == 'e');
}

void test_collision_delete()
{
    std::cout << "\nTesting collision with delete and find...\n\n";
    my_map<char, int> m1;
    map_generator_helper_with_collision(m1);
    m1.erase(m1.find('\0'));
    assert(m1.find('\0') == m1.end());
    assert(m1.at('d') == 'd');
    assert(m1.at('e') == 'e');
    m1.insert(std::make_pair<char, int>('\0', '\0'));
    m1.erase(m1.find('d'));
    assert(m1.at('\0') == '\0');
    assert(m1.at('e') == 'e');
    m1.erase(m1.find('e'));
    assert(m1.at('\0') == '\0');
}
