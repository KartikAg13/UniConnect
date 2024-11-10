#include "File.h"
#include <vector>

namespace fs = std::filesystem;

bool saveUserToFile(User *user)
{
    try
    {
        const string filePath = user->getUsername() + ".txt";
        ofstream file(filePath, ios::app);
        if (!file.is_open())
        {
            cout << "Error: Could not open file " << filePath << " for writing" << endl;
            return false;
        }
        file << user->getName() << endl;
        file << user->getPassword() << endl;
        file << user->getEmail() << endl;
        file << user->getAge() << endl;
        file << user->getGenderAsString() << endl;

        vector<string> qualities = user->getQualities();
        int size_qualities = qualities.size();
        vector<User *> followers = user->getFollowers();
        int size_followers = followers.size();

        file << "Qualities: ";
        for(int index = 0; index < size_qualities; index++)
            file << qualities[index] << ", ";
        file << endl;

        file << "Followers: ";
        for(int index = 0; index < size_qualities; index++)
            file << followers[index]->getUsername() << ", ";
        file << endl;

        if (!file.good())
        {
            cout << "Error: Writing to file failed" << endl;
            return false;
        }
    }
    catch (const ofstream::failure& e)
    {
        cerr << "Exception while handling file: " << e.what() << endl;
        return false;
    }

    return true;
}

User* loadFromFile(const string& filename) {
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "Error: Could not open file " << filename << endl;
        return nullptr;
    }

    string name, username, password, email, genderStr, temp;
    int age;
    bool gender;

    getline(file, name);

    getline(file, username);

    getline(file, password);

    getline(file, email);

    getline(file, temp);
    age = stoi(temp);

    getline(file, temp);
    gender = (temp == "Male") ? false : true;

    file.close();

    return new User(name, username, password, email, age, gender);
}


Node *parseUserFiles(const string &path)
{
    AVLTree root;
    for (const auto& entry : fs::directory_iterator(path))
    {
            std::string filepath = entry.path().string();
            User* user = loadFromFile(filepath);
            if (user != nullptr)
                root.insert(user);
    }
    return root.getRoot();
}
