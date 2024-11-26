#ifndef CHAT_H
#define CHAT_H

#include "User.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

using String = std::string;

class Post 
{
private:
    String username;
    String message;

public:
    Post(const String& username, const String& message);

    String getUsername() const;

    String getMessage() const;
};

class PostManager 
{
private:
    std::vector<Post> posts;

public:
    void addPost(const User& user, const String& message);

    void displayPosts() const;

    void savePostsToFile(const String& filename) const;

    void loadPostsFromFile(const String& filename);
};

#endif
