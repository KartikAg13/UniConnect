#include "Graph.h"

Graph::Graph() {}

void Graph::addEdge(const User& u, const User& v, int weight) 
{
    auto& neighbors = adjacencyList[u];

    auto it = std::find_if(neighbors.begin(), neighbors.end(), [&](const std::pair<User, int>& p) {
        return p.first.getUsername() == v.getUsername();
    });

    if (it == neighbors.end()) 
    {
        neighbors.emplace_back(v, weight);
        adjacencyList[v].emplace_back(u, weight);
    }
}


int Graph::calculateSimilarity(const User& u1, const User& u2) const 
{
    int similarity = 0;

    const auto& qualities1 = u1.getQualities();
    const auto& qualities2 = u2.getQualities();

    for (const auto& quality1 : qualities1) 
    {
        if (std::find(qualities2.begin(), qualities2.end(), quality1) != qualities2.end())
        {
            similarity++;
        }
    }
    return similarity;
}


void Graph::print() const 
{
    for (const auto& entry : adjacencyList) 
    {
        std::cout << entry.first.getUsername() << ": ";
        for (const auto& neighbor : entry.second) 
        {
            std::cout << "(" << neighbor.first.getUsername() << ", " << neighbor.second << ") ";
        }
        std::cout << std::endl;
    }
}

void Graph::buildGraph(const std::vector<User>& users) 
{
    for (size_t i = 0; i < users.size(); ++i) 
    {
        for (size_t j = i + 1; j < users.size(); ++j) 
        {
            int similarity = calculateSimilarity(users[i], users[j]);
            if (similarity > 0) 
            {
                addEdge(users[i], users[j], similarity);
            }
        }
    }
}

std::vector<User> Graph::suggestUsers(const User& targetUser, int topN) const 
{
    std::vector<std::pair<User, int>> similarityScores;

    auto it = adjacencyList.find(targetUser);
    if (it != adjacencyList.end()) 
    {
        similarityScores.assign(it->second.begin(), it->second.end());
    }

    std::sort(similarityScores.begin(), similarityScores.end(),
              [](const std::pair<User, int>& a, const std::pair<User, int>& b) {
                  return a.second > b.second;
              });

    std::vector<User> suggestions;
    for (int i = 0; i < std::min(topN, static_cast<int>(similarityScores.size())); ++i) 
    {
        suggestions.push_back(similarityScores[i].first);
    }

    return suggestions;
}

void Graph::buildGraphFromAVL(AVLTree* tree) 
{
    std::vector<User> users;
    collectUsersFromAVL(tree->getRoot(), users);

    for (const auto& user : users) 
    {
        for (const auto& followerUsername : user.getFollowers()) 
        {
            auto it = std::find_if(users.begin(), users.end(), [&](const User& u) {
                return u.getUsername() == followerUsername;
            });

            if (it != users.end()) 
            {
                int similarity = calculateSimilarity(user, *it);
                if (similarity > 0) 
                {
                    addEdge(user, *it, similarity);
                }
            }
        }
    }
}


void Graph::collectUsersFromAVL(Node* node, std::vector<User>& users) 
{
    if (node == nullptr) 
    {
        return;
    }

    collectUsersFromAVL(node->left, users);
    users.push_back(*node->user);
    collectUsersFromAVL(node->right, users);
}