#include "user.h"
#include <map>

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

void User::updateUser(map<string, map<int, map<string, string> > > bookList)
{
    for(auto itr = watchList.begin(); itr != watchList.end(); itr++)
    {
        for(auto itr2 = bookList.begin(); itr2 != bookList.end(); itr2++)
        {
            for(auto itr3 = itr2->second.begin(); itr3 != itr2->second.end(); itr3++)
            {
                if(itr3->second.find(itr->first) != itr3->second.end())
                {
                    cout << endl << "Your book: " << itr3->second.find(itr->first)->first << " has been found in " << itr2->first << " store: " << itr3->first <<  endl;
                }
            }
        }
    }
}

void User::addToWatch(string title)
{
    watchList.insert(pair<string, string>(title, ""));

    cout << title << " has been added to the watchlist" << endl;
}

void User::removeWatch(string title)
{

    if(watchList.find(title) != watchList.end())
    {
        cout << "We have erased: " << watchList.find(title)->first << " from your watchlist" << endl;
        watchList.erase(title);
    }
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

