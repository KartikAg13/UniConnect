#include "User.h"

using namespace std;

int main()
{
    User *user = new User();
    user->inputUserDetails();
    user->printUserDetails();
    delete user;
    return 0;
}
