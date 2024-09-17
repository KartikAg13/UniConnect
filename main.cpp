#include <iostream>
#include <vector>
#include <string>
using namespace std;

class User {
    public:
    string username, password, email;
    vector<string> qualities;
    vector<User *> followers;

    User() {
        username = password = email = "";
    }

    void addUser() {
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
                qualities.push_back(quality);
            else
                break;
        }
    }

    void addFollower(User *user) {
        followers.push_back(user);
    }

    void printUser() {
        cout << "Username: " << username << endl;
        cout << "Password: " << password << endl;
        cout << "Email: " << email << endl;
        cout << "Number of Qualities: " << qualities.size() << endl;
        for(int index = 0; index < qualities.size(); index++)
            cout << qualities[index] << endl;
        cout << "Number of Followers: " << followers.size() << endl;
        cout << "List of Followers: " << endl;
        for(int index = 0; index < followers.size(); index++)
            cout << followers[index]->username << endl;
    }
};

int main() {
    return 0;
}