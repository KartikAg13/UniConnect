#include "User.h"
#include "Node.h"
#include "AVLTree.h"

#ifndef FILE_H
#define FILE_H

#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>

using String = std::string;

bool saveUserToFile(User *user);

User *loadFromFile(const String &);

Node *parseUserFiles(const String & = "userData/");

#endif
