#include "User.h"
#include "Node.h"
#include "AVLTree.h"

#ifndef FILE_H
#define FILE_H

#include <iostream>
#include <fstream>
#include <filesystem>

using namespace std;

bool saveUserToFile(User *user);

Node *parseUserFiles(const string &);

User *loadFromFile(const string &);

#endif
