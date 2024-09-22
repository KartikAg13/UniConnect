#include "User.h"

using namespace std;

User::User() 
    {
        cout << "Constructor called" << endl;
        name = "";
        username = "";
        password = "";
        email = "";
        age = 0;
        gender = false;
    }

    void User::inputUserDetails() 
    {
        cout << "Please enter your name: ";
        cin >> name;
        cout << "Please enter your age: ";
        cin >> age;
        cout << "Please choose your gender: " << endl;
        cout << "0. Male" << endl;
        cout << "1. Female" << endl;
        cin >> gender;
        cout << "Please enter the username: ";
        cin >> username;
        cout << "Please enter the password: ";
        cin >> password;
        cout << "Please enter the email: ";
        cin >> email;
        string quality;
        while(true) {
            cout << "Please enter a quality: ";
            cin >> quality;
            if(quality != "none")
                break;
            else
                qualities.push_back(quality);
        }
    }

    void User::addFollower(User *user) 
    {
        followers.push_back(user);
    }

    void User::printUserDetails() 
    {
        cout << "Name: " << name << endl;
        cout << "Age: " << age << endl;
        if(gender)
            cout << "Gender: Female" << endl;
        else
            cout << "Gender: Male" << endl; 
        cout << "Username: " << username << endl;
        cout << "Email: " << email << endl;
        cout << "Number of Qualities: " << qualities.size() << endl;
        for(string quality : qualities)
            cout << quality << endl;
        cout << "Number of Followers: " << followers.size() << endl;
        cout << "List of Followers: " << endl;
        for(User *follower : followers)
            cout << follower->username << endl;
    }