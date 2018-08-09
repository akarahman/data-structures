#include <fstream>
#include "bst.h"

int main(int argc, char const *argv[])
{
    std::string command;
    int value;
    std::ifstream infile;
    for (int i = 1; i < argc; ++i)
    {
        infile.open(argv[i]);
        if (!infile)
        {
            std::cerr << "error opening file " << argv[i] << "\n";
            continue;
        }
        bst_node<int>* tree = nullptr;
        while (infile >> command)
        {
            if (command == "i")
            {
                infile >> value;
                insert(tree, value);
            }
            else if (command == "r")
            {
                infile >> value;
                remove(tree, value);
            }
            else if (command == "s")
            {
                std::cout << "bst size is " << size(tree) << "\n";
            }
            else if (command == "h")
            {
                std::cout << "bst height is " << height(tree) << "\n";
            }
            else if (command == "inorder")
            {
                traverse_inorder(tree);
                std::cout << "\n";
            }
            else if (command == "preorder")
            {
                traverse_preorder(tree);
                std::cout << "\n";
            }
            else if (command == "postorder")
            {
                traverse_postorder(tree);
                std::cout << "\n";
            }
            else
            {
                std::cerr << "unknown command " << command << "\n";
                exit(1);
            }
        }
        infile.close();
        std::cout << "\n";
    }
    return 0;
}
