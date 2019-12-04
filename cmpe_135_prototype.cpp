
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

//Function Declarations...
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
void saveBooks();
void loadBooks();
void saveUsers();
void loadUsers();

/*
Globals Basically just maps...
*/
map<string, User> userList;
map<string, map<int, map<string, string>>> stateMap; //three layer deep map damn...
map<string, User>::iterator itr; 

int main() {
	loadBooks();
	while (1)
		runLoginMenu();
}

//Function to hadle the initial login menu
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
				cout << endl << "Admin level permissions granted" << endl;
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
	case 3: 
	{
		saveBooks();
		exit(0);
		break;
	}
		
	default:
		cout << "Invalid option, pick again" << endl << endl;
		break;
	}
}

//Function to Create a new user and save it to the userList map
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

//Function to perform the login operations
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

//Funtion to generate standard user menu
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

//Function to generate admin menu
void adminMenu(string username)
{
	char tempvar;
	int choice;
	while(1)
	{
		cout << endl << "Select an option" << endl;
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
//Function to bring in new books to the map
void import_book() //Couldn't find a way to do this on a large scale... decorators are not the way to go for this tbh
{
	string bookdetails, state, title, temp;
	int storeNumber;
	string delimiter = ",";
	size_t pos = 0;

	//This is were the books are decorated with their detais
	Prints *basePrint = new Book();
	Prints *decoratedPrint = new Title(basePrint);
	decoratedPrint = new Author(decoratedPrint);
	decoratedPrint = new Genre(decoratedPrint);
	decoratedPrint = new Length(decoratedPrint);
	decoratedPrint = new State(decoratedPrint);
	decoratedPrint = new StoreNumber(decoratedPrint);

	bookdetails =  decoratedPrint -> getDetails();
	temp = bookdetails;

	//Need to grab some details from the decorated books
	title = getDetail(pos, delimiter, temp);
	for (int i = 0; i < 3; i++)
		getDetail(pos, delimiter, temp); //dont want
	state = getDetail(pos, delimiter, temp);
	storeNumber = stoi(getDetail(pos, delimiter, temp));

	//Fill in the 3 dimensional map...
	stateMap.insert(make_pair(state, map<int, map<string, string>>()));
	stateMap[state].insert(make_pair(storeNumber, map<string, string>()));
	stateMap[state][storeNumber].insert(make_pair(title, bookdetails));

	cout << "Book Added!" << endl;
}

//Function to parse for the details up to the first commma, it deletes what it just read...
string getDetail(size_t pos, string delimiter, string &input)
{
	string output;
	pos = input.find(delimiter);
    output = input.substr(0, pos);
    input.erase(0, pos + delimiter.length());
	return output;
}

//Function to disply all books nationwide, detailed option is the difference between just the book title and getting all of the information on each book.
void displayAllBooks(bool detailed)
{
	for(auto itr = stateMap.begin(); itr != stateMap.end(); itr++)
	{
		cout << endl << "State: " << itr->first << endl;
		for(auto itr2 = itr->second.begin(); itr2 != itr->second.end(); itr2++)
		{
			cout << "Store Number: " << itr2->first << endl;
			if(detailed)
				cout << "(Title, Author, Genre, Lenght, State, Store Number)" << endl;
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

//Function to display all books in a particular state.
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

void saveBooks()
{
	ofstream bookInformation;
	// Clear the previous books on the list
	bookInformation.open("bookInfo.txt", ofstream::out | ofstream::trunc); 
	bookInformation.close();

	bookInformation.open("bookInfo.txt");

	if(bookInformation.is_open())
	{
		for(auto itr = stateMap.begin(); itr != stateMap.end(); itr++)
	{
		for(auto itr2 = itr->second.begin(); itr2 != itr->second.end(); itr2++)
		{
			for(auto itr3 = itr2->second.begin(); itr3 != itr2->second.end(); itr3++)
			{
				bookInformation << itr3->second << endl;
			}
		}
	}
	bookInformation.close();
	}
	else
		cout << "Failed to open bookInfo.txt file" << endl;
}

void loadBooks()
{
	ifstream bookInformation;
	string data, temp, title, length, genre, author, state;
	int storeNumber;
	bookInformation.open("bookInfo.txt");

	if(bookInformation.is_open())
	{
		while( getline(bookInformation, data))
		{
			temp = data;
			title = getDetail(0, ",", data);
			author = getDetail(0, ",", data);
			genre = getDetail(0, ",", data);
			length = getDetail(0, ",", data);
			state = getDetail(0, ",", data);
			storeNumber = stoi(data);

			stateMap.insert(make_pair(state, map<int, map<string, string>>()));
			stateMap[state].insert(make_pair(storeNumber, map<string, string>()));
			stateMap[state][storeNumber].insert(make_pair(title, temp));
		}
	}
}

void saveUsers()
{
}
void loadUsers()
{

}
