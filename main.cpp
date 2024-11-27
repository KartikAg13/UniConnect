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

void moving(User, AVLTree *, Graph);

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
        moving(user, tree, graph);
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
            Node *node = tree->search(tree->getRoot(), username);
            if(node != nullptr)
            {
                loggedInUser = node->user;
                User target = *loggedInUser;
                moving(target, tree, graph);
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
    system("clear");
    delete tree;
    return 0;
}

void moving(User user, AVLTree *tree, Graph graph)
{
    system("clear");
    int choice = -1;
    do
    {
        cout << "1. Chat\n2. Add Follower\n3. Profile\n4. Suggest followers" << endl;
        cin >> choice;
    } while(choice > 4 || choice < 1);
    system("clear");
    if(choice == 1)
    {
        PostManager post;
        string message;
        post.loadPostsFromFile("post.txt");
        post.displayPosts();
        cout << "Please enter the message: ";
        cin >> message;
        post.addPost(user, message);
        post.savePostsToFile("post.txt");
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
            cout << foundUser->getUsername() << "has been added to followers" << endl;
        }
        else
        {
            cout << "User not found" << endl;
        }
    }
    else if(choice == 3)
    {
        user.printUserDetails();
    }
    else
    {
        vector<User> suggestions = graph.suggestUsers(user);
        cout << "Suggested users for " << user.getUsername() << ":\n";
        for (const auto& some : suggestions) 
        {
            cout << some.getUsername() << endl;
        }
    }
}