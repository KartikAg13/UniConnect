#include "Node.h"

#ifndef AVLTREE_H
#define AVLTREE_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

using String = std::string;

class AVLTree {
    private:
    Node* root;

    int height(Node *);

    int getBalance(Node *);

    Node* rightRotate(Node *);

    Node* leftRotate(Node *);

    int compareUsername(User *, User *);

    Node* insert(Node *, User *);

    Node* search(Node *, const String &);

    public:
    AVLTree();

    void insert(User *);

    bool searchUser(const String &);

    void loadFromFile(const String &);

    Node* getRoot();

    void inOrder(Node *);
};

#endif
