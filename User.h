#ifndef USER_H
#define USER_H

#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <regex>
#include <cstdlib>

using String = std::string;

class AVLTree;

class User {
private:
    String name;
    String username;
    String password;
    String email;
    int age;
    bool gender;
    std::vector<String> qualities;
    std::vector<String> followers;

    bool validateEmail(const String &);

    bool validateAge(int);

    bool validateUsername(const String &);
    
    bool validatePassword(const String &);

public:
    User();
    
    User(String, String, String, String, int, bool, std::vector<String>, std::vector<String>);

    void inputUserDetails(AVLTree *);

    void addFollower(User *);

    void printUserDetails() const;

    String getName() const;

    String getUsername() const;

    String getPassword() const;

    String getEmail() const;

    int getAge() const;

    bool getGender() const;

    std::vector<String> getQualities() const;

    std::vector<String> getFollowers() const;

    String getGenderAsString() const;
};

#endif
