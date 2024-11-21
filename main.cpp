#include "User.h"
#include "File.h"
#include "AVLTree.h"

using String = std::string;

class User;
class AVLTree;
class Node;

int main()
{
    
    String path = "userData/";
    Node *root = FILE_H::parseUserFiles(path);
    AVLTree *tree = new AVLTree(root);
    if (root == nullptr)
    {
        std::cerr << "Error: Could not parse user files" << std::endl;
        delete tree;
        return 1;
    }
    std::cout << "Successfully parsed user files" << std::endl;

    int choice = -1;
    do 
    {
        std::cout << "1. Register\n2. Login\n3. Exit" << std::endl;
        std::cin >> choice;
    } while(choice > 3 || choice < 1);
    if(choice == 1)
    {
        User user;
        user.inputUserDetails(tree);
    } 
    else if(choice == 2)
    {
        String username, password;
        std::cout << "Please enter your username: ";
        std::cin >> username;
        std::cout << "Please enter your password: ";
        std::cin >> password;
        if(tree->userLogin(username, password))
        {
            std::cout << "User found" << std::endl;
        }
        else
        {
            std::cout << "User not found" << std::endl;
        }
    }
    else
    {
        std::cout << "Exiting..." << std::endl;
    }
    delete tree;
    return 0;
}
