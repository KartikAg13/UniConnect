#include "Tree.h"

Tree::Tree() {
    root = nullptr;
}

int Tree::height(Node *node) {
    if(node == nullptr)
        return 0;
    return node->height;
}

int Tree::getBalance(Node *node) {
    if(node == nullptr)
        return 0;
    return height(root->left) - height(root->right);
}
