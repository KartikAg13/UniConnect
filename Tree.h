#ifndef TREE_H
#define TREE_H

#include "Node.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

class Tree {
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
    Tree();

    void insert(User *);

    Node* search(const string &);

    void loadFromFile(const string & = "users.txt");

    Node* getRoot();

    void inOrder(Node *);
};

#endif
