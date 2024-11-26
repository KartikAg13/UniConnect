#include "Chat.h"

Post::Post(const String& username, const String& message) 
{
    this->username = username;
    this->message = message;
}

String Post::getUsername() const 
{
    return username;
}

String Post::getMessage() const 
{
    return message;
}

void PostManager::addPost(const User& user, const String& message) 
{
    if (message.empty()) 
    {
        std::cerr << "Message cannot be empty!" << std::endl;
        return;
    }

    posts.emplace_back(user.getUsername(), message);
    std::cout << "Post added successfully by " << user.getUsername() << "!" << std::endl;
}

void PostManager::displayPosts() const 
{
    if (posts.empty()) 
    {
        std::cout << "No posts available." << std::endl;
        return;
    }

    std::cout << "All Posts:\n";
    for (const auto& post : posts) 
    {
        std::cout << post.getUsername() << ": " << post.getMessage() << std::endl;
    }
}

void PostManager::savePostsToFile(const String& filename) const 
{
    std::ofstream outFile(filename);
    if (!outFile) 
    {
        std::cerr << "Error: Unable to open file for writing!" << std::endl;
        return;
    }

    for (const auto& post : posts) 
    {
        outFile << post.getUsername() << "," << post.getMessage() << std::endl;
    }

    outFile.close();
    std::cout << "Posts saved successfully to " << filename << "!" << std::endl;
}

void PostManager::loadPostsFromFile(const String& filename) 
{
    std::ifstream inFile(filename);
    if (!inFile) 
    {
        std::cerr << "Error: Unable to open file for reading!" << std::endl;
        return;
    }

    posts.clear();
    String line, username, message;
    while (std::getline(inFile, line)) 
    {
        std::istringstream iss(line);
        std::getline(iss, username, ',');
        std::getline(iss, message);

        posts.emplace_back(username, message);
    }

    inFile.close();
    std::cout << "Posts loaded successfully from " << filename << "!" << std::endl;
}
