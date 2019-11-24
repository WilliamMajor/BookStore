#include "user.h"

#include <iostream>
#include <string>

using namespace std;

User::User()
{
//Don't know if we have anything to pass in 
}

void User::set_username(string username)
{
    Username = username;
}

void User::set_password(string password)
{
    Password = password;
}

void User::set_state(string state)
{
    State = state;
}

string User::get_username()
{
    return Username;
}

string User::get_password()
{
    return Password;
}

string User::get_state()
{
    return State;
}

