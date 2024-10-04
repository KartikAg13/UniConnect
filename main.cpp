#include <iostream>

#include "User.h"
#include "Node.h"
#include "Tree.h"

using namespace std;

int main()
{
    User *user = new User();
    user->inputUserDetails();
    user->printUserDetails();
    cout << "Hello" << endl;
    delete user;
    return 0;
}
