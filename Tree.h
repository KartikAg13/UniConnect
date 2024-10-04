#ifndef TREE_H
#define TREE_H

#include <iostream>
#include "Node.h"
#include "User.h"

using namespace std;

class Tree {
    private:
    Node *root;

    int height(Node *);

    int getBalance(Node *);

    Node *rightRotate(Node *);

    Node *leftRotate(Node *);

    Node *insert(Node *, User *);

    Node *search(Node *, const string &);

    int compareUsername(User *, User *);

    public:
    Tree();

    void insert(User *);

    Node *search(const string &);

    void inOrder(Node *);

    Node *getRoot();
};

#endif
