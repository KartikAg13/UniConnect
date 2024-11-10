#ifndef USER_H
#define USER_H

#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <regex>
#include <cstdlib>

using namespace std;

class User
{
    private:
    string name;
    string username;
    string password;
    string email;
    int age;
    bool gender;
    vector<string> qualities;
    vector<User *> followers;

    bool validateEmail(const string &);

    bool validateAge(int);

    bool validateUsername(const string &);

    bool validatePassword(const string &);

    public:
    User();

    User(string, string, string, string, int, bool);

    void inputUserDetails();

    void addFollower(User *);

    void printUserDetails() const;

    string getName() const;

    string getUsername() const;

    string getPassword() const;

    string getEmail() const;

    int getAge() const;

    bool getGender() const;

    vector<string> getQualities() const;

    vector<User *> getFollowers() const;

    string getGenderAsString() const;
};

#endif
