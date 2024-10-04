#include "Tree.h"

Tree::Tree()
{
    root = nullptr;
}

int Tree::height(Node *node)
{
    if(node == nullptr)
        return -1;
    return node->height;
}

int Tree::getBalance(Node *node)
{
    if(node == nullptr)
        return 0;
    return height(root->left) - height(root->right);
}

Node *Tree::rightRotate(Node *y)
{
    Node *x = y->left;
    Node *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;
    return x;
}

Node *Tree::leftRotate(Node *x)
{
    Node *y = x->right;
    Node *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;
    return y;
}

int Tree::compareUsername(User *u1, User *u2)
{
    return u1->username.compare(u2->username);
}

Node *Tree::insert(Node *node, User *user)
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

Node *Tree::search(Node *node, const string &username)
{
    if(node == nullptr || node->user->username == username)
        return node;

    if(username < node->user->username)
        return search(node->left, username);

    return search(node->right, username);
}

void Tree::insert(User *user)
{
    root = insert(root, user);
}

Node *Tree::search(const string &username)
{
    return search(root, username);
}

void Tree::loadFromFile(const string &filePath)
{
    ifstream file(filePath);
    if (!file.is_open())
    {
        cerr << "Error: Could not open file " << filePath << endl;
        return;
    }

    string line;
    while (getline(file, line))
    {
        stringstream ss(line);
        string name, username, password, email, ageStr, genderStr;
        int age;
        int gender;

        getline(ss, name, ',');
        getline(ss, username, ',');
        getline(ss, password, ',');
        getline(ss, email, ',');
        getline(ss, ageStr, ',');
        getline(ss, genderStr, ',');

        age = stoi(ageStr);
        gender = stoi(genderStr);

        User* user = new User();
        user->name = name;
        user->username = username;
        user->password = password;
        user->email = email;
        user->age = age;
        user->gender = (gender == 0) ? User::Male : User::Female;

        insert(user);
    }

    file.close();
}

Node *Tree::getRoot()
{
    return root;
}

void Tree::inOrder(Node *node)
{
    if(node != nullptr)
    {
        inOrder(node->left);
        cout << node->user->username << endl;
        inOrder(node->right);
    }
}
