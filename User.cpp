#include "User.h"

User::User()
{
    name = "";
    username = "";
    password = "";
    email = "";
    age = 0;
    gender = Male;
}

bool User::validateEmail(const string &email)
{
    const regex email_pattern("^[\\w-\\.]+@([\\w-]+\\.)+[\\w-]{2,4}$");
    if (!regex_match(email, email_pattern))
    {
        cout << "Invalid email format. Please try again." << endl;
        return false;
    }
    return true;
}

bool User::validateAge(int age)
{
    if (age < 17 || age > 26)
    {
        cout << "Invalid age. Please enter a value between 17 and 26." << endl;
        return false;
    }
    return true;
}

bool User::validateUsername(const string &username)
{
    const regex usernamePattern("^[A-Za-z][A-Za-z0-9]{4,19}$");

    if (!regex_match(username, usernamePattern))
    {
        cout << "Invalid username. Must be 5-20 characters, start with a letter, and contain only alphanumeric characters." << endl;
        return false;
    }

    return true;
}

bool User::validatePassword(const string &password)
{
    const regex passwordPattern("^(?=.*[a-z])(?=.*[A-Z])(?=.*\\d)(?=.*[!@#$%^&*()_+])[A-Za-z\\d!@#$%^&*()_+]{8,}$");

    if (!regex_match(password, passwordPattern))
    {
        cout << "Invalid password. Must be at least 8 characters long, with at least one uppercase letter, one lowercase letter, one digit, and one special character." << endl;
        return false;
    }

    return true;
}

void User::inputUserDetails()
{
    cout << "Please enter your name: ";
    cin.ignore();
    getline(cin, name);

    do
    {
        cout << "Please enter your age (between 17 and 26): ";
        cin >> age;
    } while (!validateAge(age));

    int genderInput;
    do
    {
        cout << "Please choose your gender:\n0. Male\n1. Female\n";
        cin >> genderInput;
    } while (genderInput != 0 && genderInput != 1);

    gender = (genderInput == 1) ? Female : Male;

    do
    {
        cout << "Please enter the username: ";
        cin >> username;
    } while (!validateUsername(username));

    do
    {
        cout << "Please enter the password: ";
        cin >> password;
    } while (!validatePassword(password));

    do
    {
        cout << "Please enter your email: ";
        cin >> email;
    } while (!validateEmail(email));

    string quality;
    cout << "Enter qualities (type 'none' to stop):" << endl;
    while(true)
    {
        cout << "Quality: ";
        cin >> quality;
        if (quality == "none") break;
        qualities.push_back(quality);
    }
}

void User::addFollower(User *user) {
    if (user == nullptr)
    {
        cout << "Error: Cannot add a null follower." << endl;
        return;
    }
    followers.push_back(user);
}

void User::printUserDetails() const
{
    cout << "Name: " << name << endl;
    cout << "Age: " << age << endl;
    cout << "Gender: " << (gender == Male ? "Male" : "Female") << endl;
    cout << "Username: " << username << endl;
    cout << "Email: " << email << endl;

    cout << "Number of Qualities: " << qualities.size() << endl;
    for (const string &quality : qualities)
        cout << quality << endl;

    cout << "Number of Followers: " << followers.size() << endl;
    cout << "List of Followers: " << endl;
    for (const User *follower : followers)
        cout << follower->username << endl;
}

bool User::saveUserToFile(const string& filePath) const
{
    try
    {
        ofstream file(filePath, ios::app);
        if (!file)
        {
            cout << "Error: Could not open file " << filePath << " for writing" << endl;
            return false;
        }

        file << name << "," << username << "," << password << "," << email << "," << age << "," << gender << "\n";

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
