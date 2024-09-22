#ifndef USER_H
#define USER_H

#include<iostream>
#include<vector>
#include<string>

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
    
    public:
    User();
    
    void inputUserDetails();

    void addFollower(User *);

    void printUserDetails();
};

#endif