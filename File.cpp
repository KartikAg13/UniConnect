#include "File.h"
#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;

bool saveUserToFile(User *user)
{
    try
    {
        const String filePath = "userData/" + user->getUsername() + ".txt";
        std::ofstream file(filePath, std::ios::app);
        if (file.is_open() == false)
        {
            std::cout << "Error: Could not open file " << filePath << " for writing" << std::endl;
            return false;
        }
        file << user->getUsername() << std::endl;
        file << user->getName() << std::endl;
        file << user->getPassword() << std::endl;
        file << user->getEmail() << std::endl;
        file << user->getAge() << std::endl;
        file << user->getGenderAsString() << std::endl;

        std::vector<String> qualities = user->getQualities();
        int size_qualities = qualities.size();
        std::vector<String> followers = user->getFollowers();
        int size_followers = followers.size();

        file << "Qualities: ";
        for(int index = 0; index < size_qualities; index++)
            file << qualities[index] << ", ";
        file << std::endl;

        file << "Followers: ";
        for(int index = 0; index < size_followers; index++)
            file << followers[index] << ", ";
        file << std::endl;

        if (file.good() == false)
        {
            std::cout << "Error: Writing to file failed" << std::endl;
            return false;
        }
    }
    catch (const std::ofstream::failure& e)
    {
        std::cerr << "Exception while handling file: " << e.what() << std::endl;
        return false;
    }
    return true;
}

User* loadFromFile(const String& filename) 
{
    std::ifstream file(filename);
    if (file.is_open() == false) 
    {
        std::cerr << "Error: Could not open file" << filename << std::endl;
        return nullptr;
    }
    String username, name, password, email, genderStr, line;
    int age;
    bool gender;
    std::vector<String> qualities, followers;
    getline(file, username);
    getline(file, name);
    getline(file, password);
    getline(file, email);
    getline(file, line);
    
    try
    {
        age = std::stoi(line);
    }
    catch (const std::invalid_argument& e)
    {
        std::cerr << "Invalid age value in file " << filename << ": " << line << std::endl;
        return nullptr;
    }

    getline(file, line);
    gender = (line == "Male") ? false : true;

    getline(file, line);
    String qualitiesStr = line;
    std::stringstream ss(qualitiesStr);
    String quality;
    while (getline(ss, quality, ',') && qualities.size() < 5) 
    {
        qualities.push_back(quality);
    }
    
    getline(file, line);
    String followersStr = line;
    std::stringstream fs(followersStr);
    String follower;
    while (getline(fs, follower, ',')) 
    {
        followers.push_back(follower);
    }
    
    file.close();
    return new User(name, username, password, email, age, gender, qualities, followers);
}


Node *parseUserFiles(const String &path)
{
    AVLTree root;
    if (fs::exists(path) == false) 
    {
        std::cerr << "Error: Path does not exist: " << path << std::endl;
        return nullptr;
    }
    if (fs::is_directory(path) == false) 
    {
        std::cerr << "Error: Path is not a directory: " << path << std::endl;
        return nullptr;
    }
    for (const auto& entry : fs::directory_iterator(path))
    {
            String filepath = entry.path().string();
            if(filepath.find(".txt") == String::npos)
            {
                std::cout << "Parsing complete" << std::endl;
                break;
            }
            User* user = loadFromFile(filepath);
            if(user == nullptr)
            {
                std::cerr << "Error loading user from file: " << filepath << std::endl;
                continue;
            }
            else
            {
                root.insert(user);
            }
    }
    return root.getRoot();
}
