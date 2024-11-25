#include "User.h"
#include "File.h"
#include "AVLTree.h"
#include "suggestion_model.h"
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

// Function to collect all users from the AVLTree
void collectUsers(Node* node, vector<User>& users) {
    if (node == nullptr) return;
    collectUsers(node->left, users);
    users.push_back(*(node->user));
    collectUsers(node->right, users);
}

int main()
{
    String path = "userData/";
    Node *root = FILE_H::parseUserFiles(path);
    AVLTree *tree = new AVLTree(root);
    if (root == nullptr)
    {
        cerr << "Error: Could not parse user files" << endl;
        delete tree;
        return 1;
    }
    cout << "Successfully parsed user files" << endl;

    int choice = -1;
    do 
    {
        cout << "1. Register\n2. Login\n3. Exit" << endl;
        cin >> choice;
    } while(choice > 3 || choice < 1);
    if(choice == 1)
    {
        User user;
        user.inputUserDetails(tree);
    } 
    else if(choice == 2)
    {
        String username, password;
        cout << "Please enter your username: ";
        cin >> username;
        cout << "Please enter your password: ";
        cin >> password;
        if(tree->userLogin(username, password))
        {
            cout << "User found" << endl;
            User *loggedInUser = nullptr;

            // Find the logged-in user in the tree
            Node *node = tree->search(tree->getRoot(), username);
            if (node != nullptr) {
                loggedInUser = node->user;
            }

            if (loggedInUser) {
                vector<User> allUsers;
                // Collect all users from the AVLTree
                collectUsers(tree->getRoot(), allUsers);

                User targetUser = *loggedInUser; // Copy the logged-in user for suggestions

                // Get suggestions
                vector<User> suggestions = suggestUsers(targetUser, allUsers);

                cout << "Suggested users for " << targetUser.getUsername() << ":\n";
                for (const auto& user : suggestions) {
                    cout << user.getUsername() << "\n";
                }
            } else {
                cout << "User not found in tree." << endl;
            }
        }
        else
        {
            cout << "User not found" << endl;
        }
    }
    else
    {
        cout << "Exiting..." << endl;
    }
    delete tree;
    return 0;
}
