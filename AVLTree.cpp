#include "AVLTree.h"

AVLTree::AVLTree()
{
    root = nullptr;
}

int AVLTree::height(Node *node)
{
    if(node == nullptr)
        return -1;
    return node->height;
}

int AVLTree::getBalance(Node *node)
{
    if(node == nullptr)
        return 0;
    return height(root->left) - height(root->right);
}

Node *AVLTree::rightRotate(Node *y)
{
    Node *x = y->left;
    Node *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;
    return x;
}

Node *AVLTree::leftRotate(Node *x)
{
    Node *y = x->right;
    Node *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;
    return y;
}

int AVLTree::compareUsername(User *u1, User *u2)
{
    return u1->getUsername().compare(u2->getUsername());
}

Node *AVLTree::insert(Node *node, User *user)
{
    if(node == nullptr)
        return new Node(user);

    int compare = compareUsername(user, node->user);
    if(compare < 0)
        node->left = insert(node->left, user);
    else if(compare > 0)
        node->right = insert(node->right, user);
    else
        return node;

    node->height = 1 + max(height(node->left), height(node->right));

    int balance = getBalance(node);

    if(balance > 1 && compareUsername(user, node->left->user) < 0)
        return rightRotate(node);
    if(balance < -1 && compareUsername(user, node->right->user) > 0)
        return leftRotate(node);
    if(balance > 1 && compareUsername(user, node->left->user) > 0)
    {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    if(balance < -1 && compareUsername(user, node->right->user) < 0)
    {
        node->right = rightRotate(node);
        return leftRotate(node);
    }

    return node;
}

Node *AVLTree::search(Node *node, const string &username)
{
    if(node == nullptr || node->user->getUsername() == username)
        return node;

    if(username < node->user->getUsername())
        return search(node->left, username);

    return search(node->right, username);
}

void AVLTree::insert(User *user)
{
    root = insert(root, user);
}

bool AVLTree::searchUser(const string &username)
{
    return search(root, username) != nullptr;
}

Node *AVLTree::getRoot()
{
    return root;
}

void AVLTree::inOrder(Node *node)
{
    if(node != nullptr)
    {
        inOrder(node->left);
        cout << node->user->getUsername() << endl;
        inOrder(node->right);
    }
}
