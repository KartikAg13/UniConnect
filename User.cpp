#include "User.h"
#include "File.h"
#include "AVLTree.h"

User::User()
{
    name = "";
    username = "";
    password = "";
    email = "";
    age = 0;
    gender = false;
}

User::User(String name, String username, String password, String email, int age, bool gender, std::vector<String> qualities, std::vector<String> followers)
{
    this->name = name;
    this->username = username;
    this->password = password;
    this->email = email;
    this->age = age;
    this->gender = gender;
    this->qualities = qualities;
    this->followers = followers;
}

bool User::validateEmail(const String &email)
{
    const std::regex email_pattern("^\\d+@mail\\.jiit\\.ac\\.in$");
    if (!regex_match(email, email_pattern))
    {
        std::cout << "Invalid email format. Please try again." << std::endl;
        return false;
    }
    return true;
}

bool User::validateAge(int age)
{
    if (age < 17 || age > 26)
    {
        std::cout << "Invalid age. Please enter a value between 17 and 26." << std::endl;
        return false;
    }
    return true;
}

bool User::validateUsername(const String &username)
{
    const std::regex usernamePattern("^[A-Za-z][A-Za-z0-9]{4,19}$");

    if (!regex_match(username, usernamePattern))
    {
        std::cout << "Invalid username. Must be 5-20 characters, start with a letter, and contain only alphanumeric characters." << std::endl;
        return false;
    }

    return true;
}

bool User::validatePassword(const String &password)
{
    const std::regex passwordPattern("^(?=.*[a-z])(?=.*[A-Z])(?=.*\\d)(?=.*[!@#$%^&*()_+])[A-Za-z\\d!@#$%^&*()_+]{8,}$");

    if (!regex_match(password, passwordPattern))
    {
        std::cout << "Invalid password. Must be at least 8 characters long, with at least one uppercase letter, one lowercase letter, one digit, and one special character." << std::endl;
        return false;
    }

    return true;
}

void User::inputUserDetails(AVLTree *root)
{
    std::cout << "Please enter your name: ";
    std::cin.ignore();
    std::getline(std::cin, name);

    do
    {
        std::cout << "Please enter your age (between 17 and 26): ";
        std::cin >> age;
    } while (!validateAge(age));

    int genderInput;
    do
    {
        std::cout << "Please choose your gender:\n0. Male\n1. Female\n";
        std::cin >> genderInput;
    } while (genderInput != 0 && genderInput != 1);

    gender = (genderInput == 1) ? true : false;
    
    do
    {
        std::cout << "Please enter the username: ";
        std::cin >> username;
        if(root->searchUser(username) == false)
        {
            std::cout << "Username already exists. Please try again." << std::endl;
            continue;
        }
    } while (!validateUsername(username));

    do
    {
        std::cout << "Please enter the password: ";
        std::cin >> password;
    } while (!validatePassword(password));

    do
    {
        std::cout << "Please enter your email: ";
        std::cin >> email;
    } while (!validateEmail(email));

    String quality;
    int max_qualities = 5;
    std::cout << "Please enter " << max_qualities << " qualities: " << std::endl;
    while(qualities.size() < max_qualities)
    {
        std::cout << "Quality: ";
        std::cin >> quality;
        qualities.push_back(quality);
    }

    if(FILE_H::saveUserToFile(this))
        std::cout << "User successfully registered" << std::endl;
    else
    {
        std::cout << "Could not register User" << std::endl;
        exit(1);
    }
}

void User::addFollower(User *user) {
    if (user == nullptr)
    {
        std::cout << "Error: Cannot add a null follower." << std::endl;
        return;
    }
    followers.push_back(user->username);
}

void User::printUserDetails() const
{
    std::cout << "Name: " << name << std::endl;
    std::cout << "Age: " << age << std::endl;
    std::cout << "Gender: " << (gender == false ? "Male" : "Female") << std::endl;
    std::cout << "Username: " << username << std::endl;
    std::cout << "Email: " << email << std::endl;

    std::cout << "Number of Qualities: " << qualities.size() << std::endl;
    for (const String &quality : qualities)
    {
        std::cout << quality << std::endl;
    }

    std::cout << "Number of Followers: " << followers.size() << std::endl;
    std::cout << "List of Followers: " << std::endl;
    for (const String follower : followers) 
    {
        std::cout << follower << std::endl;
    }
}

String User::getName() const
{
    return name;
}

String User::getUsername() const
{
    return username;
}

String User::getPassword() const
{
    return password;
}

String User::getEmail() const
{
    return email;
}

int User::getAge() const
{
    return age;
}

bool User::getGender() const
{
    return gender;
}

std::vector<String> User::getQualities() const
{
    return qualities;
}

std::vector<String> User::getFollowers() const
{
    return followers;
}

String User::getGenderAsString() const
{
    return gender == false ? "Male" : "Female";
}
