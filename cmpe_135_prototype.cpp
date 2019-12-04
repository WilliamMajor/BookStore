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
#include <fstream>
#include "user.h"
#include "prints.h"
#include "printDetails.h"
#include "bookDetails.h"
#include "concreateComponents.h"

using namespace std;

void runLoginMenu();
void createUser(User &newUser);
bool login(string &UserNaem);
bool checkPassword(User toCheck);
void userMenu(string username);
void adminMenu(string);
void import_book();
void displayAllBooks(bool detailed);
void displayAllBooks(bool detailed, string state);
string getDetail(size_t pos, string delimiter, string &input);

/*
Globals
*/
map<string, User> userList;
map<string, map<int, map<string, string>>> stateMap; //three layer deep map damn...
map<string, User>::iterator itr; 

int main() {
	while (1)
		runLoginMenu();
}


void runLoginMenu()
{
	int menu_select = 0;
	cout << endl << "Select an option" << endl;
	cout << "1: Create User" << endl;
	cout << "2: Login" << endl;
	cout << "3: Quit" << endl;

	cin >> menu_select;

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
		string userName;
		if(login(userName)) // we pass by refference a string so we can capture who logged in
		{
			if(userName == "admin")
			{
				cout << "Admin level permissions granted" << endl;
				adminMenu(userName);
			}
			else
			{
				cout << "login successul" << endl;
				userMenu(userName);
			}


		}
		
		break;
	}
	case 3: exit(0);
		break;
	default:
		cout << "Invalid option, pick again" << endl << endl;
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

bool login(string &userName)
{
	string choice;
	while(1) //loop to allow multiple login
	{
		cout << "Enter Username: ";
		cin >> userName;
		if(userList.find(userName) == userList.end())
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
				for(itr = userList.find(userName); itr != userList.end(); ++itr)
				{
					if(!checkPassword(itr->second))
						cout << "Incorrect Password... Try again" << endl;
					else
						return true; //correct password found
					
					
				}
			}
		}
	}
	return false;
}

void userMenu(string username)
{
	char tempvar;
	int choice;
	while(1)
	{
		cout << "Select an option" << endl;
		cout << "1: Search all stores" << endl;
		cout << "2: Search stores in your state" << endl;
		cout << "3: Log out" << endl;
		cin >> choice;

		switch(choice)
		{
			case 1:
			{
				cout << "Detailed? Y/N ";
				cin >> tempvar;
				displayAllBooks(toupper(tempvar) == 'Y');
				break;
			}
			case 2:
			{
				break;
			}	
			case 3: return;
			
			case 4: cout << "Invalide choice, choose again." << endl << endl;
				break;
		}
	}

}

void adminMenu(string username)
{
	char tempvar;
	int choice;
	while(1)
	{
		cout << "Select an option" << endl;
		cout << "1: Search all stores" << endl;
		cout << "2: Search stores in your state" << endl;
		cout << "3: Add Book" << endl;
		cout << "4: Log out" << endl;
		cin >> choice;

		switch(choice)
		{
			case 1:
			{
				cout << "Detailed? Y/N ";
				cin >> tempvar;
				displayAllBooks(toupper(tempvar) == 'Y');
				break;
			}
			case 2:
			{
				cout << "Detailed? Y/N ";
				cin >> tempvar;
				displayAllBooks(toupper(tempvar) == 'Y', userList.find(username)->first);
				break;
			}	
			case 3: import_book();
				break;
			case 4: return;
		}
	}
	
}

void import_book() //Couldn't find a way to do this on a large scale... decorators are not the way to go for this tbh
{
	string bookdetails, state, title, temp;
	int storeNumber;
	string delimiter = ",";
	size_t pos = 0;

	Prints *basePrint = new Book();
	Prints *decoratedPrint = new Title(basePrint);
	decoratedPrint = new Length(decoratedPrint);
	decoratedPrint = new Genre(decoratedPrint);
	decoratedPrint = new Author(decoratedPrint);
	decoratedPrint = new State(decoratedPrint);
	decoratedPrint = new StoreNumber(decoratedPrint);

	bookdetails =  decoratedPrint -> getDetails();
	temp = bookdetails;
	title = getDetail(pos, delimiter, temp);

	for (int i = 0; i < 3; i++)
		getDetail(pos, delimiter, temp); //dont want

	state = getDetail(pos, delimiter, temp);
	storeNumber = stoi(getDetail(pos, delimiter, temp));

	stateMap.insert(make_pair(state, map<int, map<string, string>>()));
	stateMap[state].insert(make_pair(storeNumber, map<string, string>()));
	stateMap[state][storeNumber].insert(make_pair(title, bookdetails));
}

string getDetail(size_t pos, string delimiter, string &input)
{
	string output;
	pos = input.find(delimiter);
    output = input.substr(0, pos);
    input.erase(0, pos + delimiter.length());
	return output;
}

void displayAllBooks(bool detailed)
{
	for(auto itr = stateMap.begin(); itr != stateMap.end(); itr++)
	{
		cout << endl << "State: " << itr->first << endl;
		for(auto itr2 = itr->second.begin(); itr2 != itr->second.end(); itr2++)
		{
			cout << "Store Number: " << itr2->first << endl;
			for(auto itr3 = itr2->second.begin(); itr3 != itr2->second.end(); itr3++)
			{
				if(detailed)
					cout << itr3->second << endl;
				else
					cout << itr3->first << endl;
				
			}
		}
	}
}

void displayAllBooks(bool detailed, string state)
{
	if(stateMap.find(state) != stateMap.end())
	{
		cout << endl << "State: " << stateMap.find(state)->first << endl;
		for(auto itr2 = stateMap.find(state)->second.begin(); itr2 != stateMap.find(state)->second.end(); itr2++)
		{
			cout << "Store Number: " << itr2->first << endl;
			for(auto itr3 = itr2->second.begin(); itr3 != itr2->second.end(); itr3++)
			{
				if(detailed)
					cout << itr3->second << endl;
				else
					cout << itr3->first << endl;
				
			}
		}
	}
	else
		cout << "Sorry there are no books located in your state." << endl;
}
