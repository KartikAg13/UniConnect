#ifndef USER_H
#define USER_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <stdexcept>
#include <regex>

using namespace std;

class User
{
    private:
    string name;
    string username;
    string password;
    string email;
    int age;
    enum Gender { Male, Female } gender;
    vector<string> qualities;
    vector<User *> followers;

    bool validateEmail(const string &);

    bool validateAge(int);

    bool validateUsername(const string &);

    bool validatePassword(const string &);

    public:
    User();

    void inputUserDetails();

    void addFollower(User *);

    void printUserDetails() const;

    bool saveUserToFile(const string & = "users.txt") const;

    friend class Tree;
};

#endif
