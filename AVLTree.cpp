#include "AVLTree.h"

AVLTree::AVLTree()
{
    root = nullptr;
}

AVLTree::AVLTree(Node *node)
{
    this->root = node;
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
    return height(node->left) - height(node->right);
}

Node *AVLTree::rightRotate(Node *y)
{
    Node *x = y->left;
    Node *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = std::max(height(y->left), height(y->right)) + 1;
    x->height = std::max(height(x->left), height(x->right)) + 1;

    return x;
}

Node *AVLTree::leftRotate(Node *x)
{
    Node *y = x->right;
    Node *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = std::max(height(x->left), height(x->right)) + 1;
    y->height = std::max(height(y->left), height(y->right)) + 1;

    return y;
}

int AVLTree::compareUsername(User *u1, User *u2)
{
    return u1->getUsername().compare(u2->getUsername());
}

Node *AVLTree::insert(Node *node, User *user)
{
    if (node == nullptr)
    {
        return new Node(user);
    }

    int compare = compareUsername(user, node->user);
    if (compare < 0)
    {
        node->left = insert(node->left, user);
    }
    else if (compare > 0)
    {
        node->right = insert(node->right, user);
    }
    else 
    {
        std::cout << "Duplicate user detected: " << user->getUsername() << std::endl;
        return node; 
    }

    node->height = 1 + std::max(height(node->left), height(node->right));

    int balance = getBalance(node);
    std::cout << "Balance for " << user->getUsername() << ": " << balance << std::endl;

    if (balance > 1 && compareUsername(user, node->left->user) < 0)
    {
        return rightRotate(node);
    }

    if (balance < -1 && compareUsername(user, node->right->user) > 0)
    {
        return leftRotate(node);
    }

    if (balance > 1 && compareUsername(user, node->left->user) > 0)
    {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && compareUsername(user, node->right->user) < 0)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    std::cout << "Inserted user: " << user->getUsername() << std::endl;
    return node;
}

void AVLTree::insert(User *user)
{
    if (user == nullptr) {
        std::cerr << "Error: Attempting to insert a nullptr into AVLTree" << std::endl;
        return;
    }

    std::cout << "Inserting user: " << user->getUsername() << std::endl;
    root = insert(root, user);
}


Node *AVLTree::search(Node *node, const String &username)
{
    if(node == nullptr || node->user->getUsername() == username)
        return node;

    if(username < node->user->getUsername())
        return search(node->left, username);

    return search(node->right, username);
}

bool AVLTree::searchUser(const String &username)
{
    return search(root, username) != nullptr;
}

bool AVLTree::userLogin(const String &username, const String &password)
{
    Node *node = search(root, username);
    if(node == nullptr)
    {
        return false;
    }
    else if(node->user->getPassword() == password)
    {
        return true;
    }
    return false;
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
        std::cout << node->user->getUsername() << std::endl;
        inOrder(node->right);
    }
}