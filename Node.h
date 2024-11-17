#include "User.h"

#ifndef NODE_H
#define NODE_H

#include <iostream>

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
