#ifndef NODE_H
#define NODE_H

#include <iostream>
#include "User.h"

using namespace std;

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
