#include "User.h"
#include "File.h"
#include "AVLTree.h"
#include "Graph.h"
#include "Chat.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include <cstdlib>

using namespace std;

void move(User, AVLTree *);

int main()
{
    String path = "userData/";
    Node *root = FILE_H::parseUserFiles(path);
    AVLTree *tree = new AVLTree(root);
    if (tree == nullptr)
    {
        cerr << "Error: Could not parse user files" << endl;
        delete tree;
        return 1;
    }
    else
    {
        cout << "Successfully parsed user files" << endl;
        system("clear");
    }

    Graph graph;
    graph.buildGraphFromAVL(tree);

    int choice = -1;
    do 
    {
        cout << "1. Register\n2. Login\n3. Exit" << endl;
        cin >> choice;
    } while(choice > 3 || choice < 1);
    system("clear");
    if(choice == 1)
    {
        User user;
        user.inputUserDetails(tree);
        system("clear");
        move(user, tree);
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
                graph.collectUsersFromAVL(tree->getRoot(), allUsers);

                User targetUser = *loggedInUser; // Copy the logged-in user for suggestions

                // Get suggestions
                vector<User> suggestions = graph.suggestUsers(targetUser);

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

void move(User user, AVLTree *tree)
{
    int choice = -1;
    do
    {
        cout << "1. Chat\n2.Add Follower\n3.Profile" << endl;
        cin >> choice;
    } while(choice > 3 || choice < 1);
    system("clear");
    if(choice == 1)
    {
        PostManager post;
        string message;
        cout << "Please enter the message: ";
        cin >> message;
        post.addPost(user, message);
    }
    else if(choice == 2)
    {
        string search;
        cout << "Please enter the username you want to search: ";
        cin >> search;
        User *foundUser = tree->search(tree->getRoot(), search)->user;
        if(foundUser)
        {
            user.addFollower(foundUser);
        }
        else
        {
            cout << "User not found" << endl;
        }
    }
    else
    {
        user.printUserDetails();
    }
}