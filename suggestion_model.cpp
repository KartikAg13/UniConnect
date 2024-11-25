#include "suggestion_model.h"
#include "AVLTree.h"
#include <vector>
#include <algorithm>
#include <iostream>

// Function to calculate similarity between two users
int calculateSimilarity(const User& u1, const User& u2) {
    int similarity = 0;
    for (const auto& quality1 : u1.getQualities()) {
        for (const auto& quality2 : u2.getQualities()) {
            if (quality1 == quality2) {
                similarity++;
            }
        }
    }
    return similarity;
}

// Function to suggest users with common qualities
std::vector<User> suggestUsers(const User& targetUser, const std::vector<User>& allUsers, int topN) {
    std::vector<std::pair<User, int>> similarityScores;
    for (const auto& user : allUsers) {
        if (user.getUsername() != targetUser.getUsername()) {
            int similarity = calculateSimilarity(targetUser, user);
            similarityScores.push_back(std::make_pair(user, similarity));
        }
    }
    
    std::sort(similarityScores.begin(), similarityScores.end(), [](const std::pair<User, int>& lhs, const std::pair<User, int>& rhs) {
        return lhs.second > rhs.second;
    });

    std::vector<User> suggestions;
    for (int i = 0; i < std::min(topN, static_cast<int>(similarityScores.size())); i++) {
        suggestions.push_back(similarityScores[i].first);
    }

    return suggestions;
}
