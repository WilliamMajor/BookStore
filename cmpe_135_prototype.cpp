//============================================================================
// Name        : cmpe.cpp
// Author      : Brandon Neep
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>
#include <map>
#include <iterator>
#include "user.h"
#include "prints.h"
#include "printDetails.h"
#include "bookDetails.h"
#include "concreateComponents.h"

using namespace std;

void runLoginMenu();
bool createUser(User &newUser);

/*
Globals
*/
map <string, User> userList;

int main() {
	while (1)
	{
		runLoginMenu();
	}
	
	//cout<<"login finished"<<endl;
	// Prints *basePrint = new Book();

	// Prints *decoratedPrint = new Title(basePrint);
	// decoratedPrint = new Length(decoratedPrint);
	// decoratedPrint = new Genre(decoratedPrint);
	// decoratedPrint = new Author(decoratedPrint);

	// cout << decoratedPrint -> getDetails() << endl;
	// cout << decoratedPrint -> cost() << endl;


}


void runLoginMenu()
{
	int menu_select = 0;
	cout<<"Select an option"<<endl;
	cout<<"1: Create User"<<endl;
	cout<<"2: Login"<<endl;
	cout<<"3: Quit"<<endl;
	while(menu_select != 1 && menu_select != 2 && menu_select != 3)
	{
		cin>>menu_select;
		//TODO menu breaks when chars are inputted
		if(menu_select != 1 && menu_select != 2 && menu_select != 3)
		{
			cout<<"invalid option: select again"<<endl;
		}
		cout << endl;
	}

	switch (menu_select)
	{
	case 1:
	{
		User new_user = User();
		createUser(new_user);
		break;
	}
	case 2: //fill this in later
	{
		break;
	}
	case 3: exit(0);
		break;
	default:
		break;
	}
}

bool createUser(User &newUser)
{
	string input;
	bool validUserName = false;

	while (!validUserName)
	{
		cout<<"Enter Username: ";
		cin>>input;
		if(userList.find(input) == userList.end())
		{
			newUser.set_username(input);
			validUserName = true;
		}

		//This is the case were we have found the username in the database and we are
		//letting them choose between going back and just logging in or choosing another username.
		else  
		{
			cout << endl << "UserName already exists in database..." << endl << endl
				<< "To enter another username press 1." << endl
				<< "To return to login area press 2."  << endl;
			cin>>input;
			switch (stoi(input))
			{
				case 1: //nothing to do here just break
					break;
				case 2: return false;
					break;
				default:
					cout << "Invalid option, returning to login screen" << endl;
			}
		}
			
	}
	
	cout<<"Enter Password: ";
	cin>>input;
	newUser.set_password(input);

	cout<<"Enter the state you live in: ";
	cin>>input;
	newUser.set_state(input);

	cout<<newUser.get_username()<<endl;
	cout<<newUser.get_password()<<endl;
	cout<<newUser.get_state()<<endl;
	//Add our new user to our map, this is essentially a well layed out hash table
	// but way easier to work with.
	userList.insert(pair<string, User>(newUser.get_username(), newUser));
}