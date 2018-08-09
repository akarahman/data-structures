#include <fstream>
#include "heapq.h"

int main(int argc, char const *argv[])
{
    if (argc < 2)
    {
        std::cerr << "must provide at least one input\n";
        exit(1);
    }

    std::fstream infile;
    int val;
    heapq<int> pq;
    std::vector<int> v;
    for (int i = 1; i < argc; ++i)
    {
        infile.open(argv[i]);
        while (infile >> val)
        {
            pq.insert(val);
            v.push_back(val);
        }
        while (pq.size() > 0)
        {
            auto it = std::max_element(v.begin(), v.end());
            assert(pq.extract_max() == *it);
            v.erase(it);
        }
        infile.close();
        std::cout << argv[i] << " passed.\n\n";
    }

    return 0;
}
