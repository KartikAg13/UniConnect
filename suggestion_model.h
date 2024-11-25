#ifndef SUGGESTION_MODEL_H
#define SUGGESTION_MODEL_H

#include "user.h"
#include <vector>

std::vector<User> suggestUsers(const User& targetUser, const std::vector<User>& allUsers, int topN = 5);

int calculateSimilarity(const User& u1, const User& u2);

#endif // SUGGESTION_MODEL_H
