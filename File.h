#ifndef FILE_H
#define FILE_H

#include "User.h"
#include "Node.h"
#include "AVLTree.h"

#include <iostream>
#include <fstream>
#include <experimental/filesystem>
#include <vector>

using String = std::string;

bool saveUserToFile(User *user);

User *loadFromFile(const String &);

Node *parseUserFiles(const String & = "userData/");

#endif
