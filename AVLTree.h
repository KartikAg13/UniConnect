#ifndef AVLTREE_H
#define AVLTREE_H

#include "Node.h"
#include "User.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

using String = std::string;

class Node;
class User;

class AVLTree 
{
private:
    Node* root;

    int height(Node *);

    int getBalance(Node *);

    Node* rightRotate(Node *);

    Node* leftRotate(Node *);

    int compareUsername(User *, User *);

    Node* insert(Node *, User *);

public:
    AVLTree();

    AVLTree(Node *);

    void insert(User *);

    bool searchUser(const String &);

    bool userLogin(const String &, const String &);

    void loadFromFile(const String &);

    Node* getRoot();

    void inOrder(Node *);

    Node* search(Node *, const String &);
};

#endif
