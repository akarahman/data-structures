#include <functional>
#include <unordered_map>
#include <cassert>
#include "my_map.h"
void map_generator_helper(my_map<char, int> &m);
bool is_anagram(std::string s1, std::string s2);
void test_constructors();
void test_insert_basic();
void test_iterator_begin();
void test_iterator_advance();
void test_iterator_dereference();
void test_iterator_end();
void test_erase_basic();

int main(int argc, char const *argv[])
{
    test_constructors();
    test_insert_basic();
    test_iterator_begin();
    test_iterator_advance();
    test_iterator_dereference();
    test_iterator_end();
    test_erase_basic();
    return 0;
}

void map_generator_helper(my_map<char, int> &m)
{
    for (char c : "helo,wrd")
    {
        if (c == '\0') break;
        m.insert(std::pair<char, int>(c, 20));
    }
    assert(m.size() == 8);
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
        std::cout << it->first << "\n";
        ++it;
        std::cout << it->first << "\n";
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
    
}
