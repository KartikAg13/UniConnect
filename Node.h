#ifndef NODE_H
#define NODE_H

#include "User.h"

#include <iostream>

class User;

class Node
{
    public:
    User *user;
    Node *left;
    Node *right;
    int height;

    Node();

    Node(User *);
};

#endif
