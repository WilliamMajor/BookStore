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
void createUser(User &newUser);
bool login();
bool checkPassword(User toCheck);

/*
Globals
*/
map<string, User> userList;
map<string, User>::iterator itr; 

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
	case 2: 
	{
		if(login())
		{
			cout << "login successul" << endl;
			//User menu will go here...
		}
		
		break;
	}
	case 3: exit(0);
		break;
	default:
		break;
	}
}

void createUser(User &newUser)
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
				case 2: return; // just return from the function
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

//Function to check the validity of the users password
bool checkPassword(User toCheck) 
{
	string password;
	cout << "Password: ";
	cin >> password;
	if(password == toCheck.get_password())
		return true;
	else
		return false;
	
}

bool login()
{
	string username;
	string choice;
	while(1) //loop to allow multiple login
	{
		cout << "Enter Username: ";
		cin >> username;
		if(userList.find(username) == userList.end())
		{
			cout << "No Username found matching" << endl
				<< "To return to login menu hit enter: 0"
				<< " or hit enter to try again." << endl;
			cin >> choice;
			if(choice == "0") //break from loop and return to menu
				break;
		}
		else
		{
			while(1)//allow the user to try to enter their password over and over again
			{
				//find our wanted user and call the function that will check
				// if the password matches the stored value
				for(itr = userList.find(username); itr != userList.end(); ++itr)
				{
					if(!checkPassword(itr->second))
					{
						cout << "Incorrect Password... Try again" << endl;
					}
					else
						return true; //the password was correct return from function
					
				}
			}
		}
	}
	return false;
}
