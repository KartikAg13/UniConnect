#include "User.h"

using namespace std;

int main()
{
    User *user = new User();
    user->inputUserDetails();
    user->printUserDetails();
    user->saveUserToFile();
    delete user;
    return 0;
}
