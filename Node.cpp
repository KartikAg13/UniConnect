#include "Node.h"

Node::Node()
{
    user = nullptr;
    left = nullptr;
    right = nullptr;
    height = 0;
}

Node::Node(User *newUser)
{
    user = newUser;
    left = nullptr;
    right = nullptr;
    height = 0;
}
