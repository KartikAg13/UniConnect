#include "Node.h"

#ifndef AVLTREE_H
#define AVLTREE_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

class AVLTree {
    private:
    Node* root;

    int height(Node *);

    int getBalance(Node *);

    Node* rightRotate(Node *);

    Node* leftRotate(Node *);

    int compareUsername(User *, User *);

    Node* insert(Node *, User *);

    Node* search(Node *, const string &);

    public:
    AVLTree();

    void insert(User *);

    bool searchUser(const string &);

    void loadFromFile(const string & = "users.txt");

    Node* getRoot();

    void inOrder(Node *);
};

#endif
