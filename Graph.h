#ifndef GRAPH_H
#define GRAPH_H

#include "User.h"
#include "AVLTree.h"
#include "Node.h"

#include <iostream>
#include <vector>
#include <list>
#include <unordered_map>
#include <string>
#include <algorithm>

using String = std::string;

// hash function for User
namespace std 
{
    template <>
    struct hash<User> 
    {
        size_t operator()(const User& user) const 
        {
            // use username as identifier for hashing
            return hash<std::string>()(user.getUsername());
        }
    };
}

class Graph 
{
private:
    std::unordered_map<User, std::list<std::pair<User, int>>> adjacencyList;

    void addEdge(const User& u, const User& v, int weight);

    int calculateSimilarity(const User& u1, const User& u2) const;

public:
    Graph();

    void print() const;

    std::list<std::pair<User, int>> getNeighbors(const User& u) const;

    void buildGraph(const std::vector<User>& users);

    std::vector<User> suggestUsers(const User& targetUser, int topN = 3) const;

    void buildGraphFromAVL(AVLTree* tree);

    void collectUsersFromAVL(Node* node, std::vector<User>& users);
};

#endif
