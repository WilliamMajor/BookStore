
#include <iostream>
#include <string>
#include <map>
#include <iterator>
#include <fstream>
#include "user.h"
#include "Prints.h"
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
void adminMenu(string username);
void import_book();
void displayAllBooks(bool detailed);
void displayAllBooks(bool detailed, string state);
void searchBook(string bookTitle);
bool addQuantity(string state, int storeNumber, string book, int &quantity);
bool subtractQuantity(string state, int storeNumber, string book, int &quantity);
string getDetail(size_t pos, string delimiter, string &input);
void saveBooks();
void loadBooks();
void saveUsers();
void loadUsers();

/*
Globals Basically just maps...
*/
map<string, User> userList;
map<string, map<int, map<string, string> > > stateMap; //three layer deep map damn...
map<string, User>::iterator itr; 

/*
TODO (if we want to)
-maybe encrypt the userdata being sent to the textfile if anyone cares enough...
-do some sanity/value checking on input data. 
-bug hunting! I'm sure there are lots of them hiding...
-anything else that people want to add.
-oh, and add a bunch of books, you can just exit the userinfo.txt file and they will get loaded in the next time the program runs, fuck decorations (don't forget pull
 	before andding books and to push the code after you added your books or no one else will see them.)

*/
int main() {
	loadBooks();
	loadUsers();
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
		saveUsers();
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

	userList.insert(pair<string, User>(newUser.get_username(), newUser));
	saveUsers();
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
				<< "To return to login menu enter: 0"
				<< " or enter: 1 to try again." << endl;
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
	string bookChoice;
	int choice;
	while(1)
	{
		cout << endl << "Select an option" << endl;
		cout << "1: Display books for all stores" << endl;
		cout << "2: Display books for stores in your state" << endl;
		cout << "3: Find Book" << endl;
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
				cout << "Detailed?  Y/N";
				cin >> tempvar;
				displayAllBooks(toupper(tempvar) == 'Y', userList.find(username)->second.get_state());
				break;
			}	
			case 3:
			{
				cout << "Book Title: ";
				cin >> bookChoice;
				searchBook(bookChoice);
				break;
			}

			case 4: return;
			
			default: cout << "Invalide choice, choose again." << endl;
				break;
		}
	}

}

//Function to generate admin menu
void adminMenu(string username)
{
	char tempvar;
	string bookChoice, stateChoice, storeChoice;
	int choice, addSubChoice, quantity;
	while(1)
	{
		cout << endl << "Select an option" << endl;
		cout << "1: Display books from all stores" << endl;
		cout << "2: Display books in your state" << endl;
		cout << "3: Add Book" << endl;
		cout << "4: Find Book" << endl;
		cout << "5: Change Book Quantity" << endl;
		cout << "6: Log out" << endl;
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
				displayAllBooks(toupper(tempvar) == 'Y', userList.find(username)->second.get_state());
				break;
			}
			case 3: import_book();
				break;
			case 4:
			{
				cout << "Book Title: ";
				cin >> bookChoice;
				searchBook(bookChoice);
				break;
			}
			case 5:
			{
				cout << endl << "Would you like to add(1) or subtract(2) books? ";
				cin >> addSubChoice;
				cout << "State: ";
				cin >> stateChoice;
				cout << "Store Number: ";
				cin >> storeChoice;
				cout << "Book: ";
				cin >> bookChoice;
				cout << "Quantity: ";
				cin >> quantity;
				if(addSubChoice == 1)
				{
					if(addQuantity(stateChoice, stoi(storeChoice), bookChoice, quantity))
					{
						cout << endl << "Added " << quantity <<" copies of " << bookChoice << " to store " << storeChoice << " in " << stateChoice << endl;
						cout << "There are " << quantity << " books now available"<< endl;
					}
					else
						cout << endl << "Sorry we could not find the book you are looking for..."<< endl;	
				}
				else if(addSubChoice == 2)
				{
					if(subtractQuantity(stateChoice, stoi(storeChoice), bookChoice, quantity))
					{
						if(quantity != 0)
						{
							cout << endl << "Removed " << quantity <<" copies of " << bookChoice << " from store " << storeChoice << " in " << stateChoice << endl;
							cout << "There are " << quantity << " books now available"<< endl;

						}
						else
							cout << "Looks like you removed the last of that book there are now 0 remaining" << endl;
						
					}
					else
						cout << endl << "Sorry we could not find the book you are looking for..."<< endl;	
				}

				break;
			}
			case 6: return;

			default: cout << "Invalid choice, choose again." << endl << endl;
				break;
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

	//This is were the books are decorated with their detais this honestly not a good application for decoration, 
	//unless someone can find a way to pass an arguement all the way down, then it would be much better and we 
	//could just mass read from a file...
	Prints *basePrint = new Book();
	Prints *decoratedPrint = new Title(basePrint);
	decoratedPrint = new Author(decoratedPrint);
	decoratedPrint = new Genre(decoratedPrint);
	decoratedPrint = new Length(decoratedPrint);
	decoratedPrint = new State(decoratedPrint);
	decoratedPrint = new StoreNumber(decoratedPrint);
	decoratedPrint = new Quantity(decoratedPrint);

	bookdetails =  decoratedPrint -> getDetails();
	temp = bookdetails;

	//Need to grab some details from the decorated books
	title = getDetail(pos, delimiter, temp);
	for (int i = 0; i < 3; i++)
		getDetail(pos, delimiter, temp); //dont want
	state = getDetail(pos, delimiter, temp);
	storeNumber = stoi(getDetail(pos, delimiter, temp));

	//Fill in the 3 dimensional map...
	stateMap.insert(make_pair(state, map<int, map<string, string> >()));
	stateMap[state].insert(make_pair(storeNumber, map<string, string>()));
	stateMap[state][storeNumber].insert(make_pair(title, bookdetails));

	cout << "Book Added!" << endl;
	saveBooks();
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

//Function to disply all books nationwide, "detailed" argument is the difference between
// just the book title and getting all of the information on each book.
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
	cout << state << endl;
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

void searchBook(string bookTitle)
{
	for(auto itr = stateMap.begin(); itr != stateMap.end(); itr++)
	{
		for(auto itr2 = itr->second.begin(); itr2 != itr->second.end(); itr2++)
		{
			
			for(auto itr3 = itr2->second.find(bookTitle); itr3 != itr2->second.end(); itr3++)
			{
				cout << itr3->second << endl;
			}
		}
	}
}

//Function to save books to text file;
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

//Function to load Books to a textfile
void loadBooks()
{
	ifstream bookInformation;
	string data, temp, title, length, genre, author, state, quantity;
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
			storeNumber = stoi(getDetail(0, ",", data));
			quantity = data;

			stateMap.insert(make_pair(state, map<int, map<string, string> >()));
			stateMap[state].insert(make_pair(storeNumber, map<string, string>()));
			stateMap[state][storeNumber].insert(make_pair(title, temp));
		}
	}
}

//Function to save users to text file
void saveUsers()
{
	ofstream userInformation;
	// Clear the previous users on the list...in case we want to end up removing users...
	userInformation.open("userInfo.txt", ofstream::out | ofstream::trunc); 
	userInformation.close();

	userInformation.open("userInfo.txt");

	if(userInformation.is_open())
	{
		for(auto itr = userList.begin(); itr != userList.end(); itr++)
		{
			userInformation << itr->second.get_username() << ",";
			userInformation << itr->second.get_password() << ",";
			userInformation << itr->second.get_state() << endl;
		}
		userInformation.close();
	}
	else
		cout << "Failed to create userInfo File" << endl;
}
void loadUsers()
{
	ifstream userInformation;
	string data, temp, userName, Password, state;
	userInformation.open("userInfo.txt");


	while( getline(userInformation, data))
	{
		User loaded_user = User(); 
		temp = data;
		loaded_user.set_username(getDetail(0, ",", data));
		loaded_user.set_password(getDetail(0, ",", data));
		loaded_user.set_state(data);

		userList.insert(pair<string, User>(loaded_user.get_username(), loaded_user));
	}

}

bool addQuantity(string state, int storeNumber, string book, int &quantity)
{
	//I wish this shit was just an object and not some stupid string we got from the wrapping...
	string data, temp, tempTitle, tempAuthor, tempGenre, tempLength, tempState, tempStoreNumber;
	int tempQuantity;
	for(auto itr = stateMap.find(state); itr != stateMap.end(); itr++)
	{
		for(auto itr2 = itr->second.find(storeNumber); itr2 != itr->second.end(); itr2++)
		{
			for(auto itr3 = itr2->second.find(book); itr3 != itr2->second.end(); itr3++)
			{
				temp = itr3->second;
				tempTitle = getDetail(0, ",", temp);
				tempAuthor = getDetail(0, ",", temp);
				tempGenre = getDetail(0, ",", temp);
				tempLength = getDetail(0, ",", temp);
				tempState = getDetail(0, ",", temp);
				tempStoreNumber = getDetail(0, ",", temp);
				tempQuantity = stoi(temp);

				tempQuantity += quantity;
				quantity = tempQuantity; //change the orignal value and pass it back so we can say how many are left.

				data = tempTitle + "," + tempAuthor + "," + tempGenre + "," + tempLength + "," + tempState + "," + tempStoreNumber + "," + to_string(tempQuantity);
				stateMap[state][storeNumber].erase(book);
				stateMap[state][storeNumber].insert(make_pair(book, data));
				saveBooks();
				return true;
			}
		}
	}
	cout << "Book not found" << endl;
	return false; //book not found
}

bool subtractQuantity(string state, int storeNumber, string book, int &quantity)
{
	string data, temp, tempTitle, tempAuthor, tempGenre, tempLength, tempState, tempStoreNumber;
	int tempQuantity;
	for(auto itr = stateMap.find(state); itr != stateMap.end(); itr++)
	{
		for(auto itr2 = itr->second.find(storeNumber); itr2 != itr->second.end(); itr2++)
		{
			for(auto itr3 = itr2->second.find(book); itr3 != itr2->second.end(); itr3++)
			{
				temp = itr3->second;
				tempTitle = getDetail(0, ",", temp);
				tempAuthor = getDetail(0, ",", temp);
				tempGenre = getDetail(0, ",", temp);
				tempLength = getDetail(0, ",", temp);
				tempState = getDetail(0, ",", temp);
				tempStoreNumber = getDetail(0, ",", temp);
				tempQuantity = stoi(temp);

				if(quantity > tempQuantity)
				{
					tempQuantity = 0;
				}
				else
					tempQuantity -= quantity;
				quantity  = tempQuantity;

				data = tempTitle + "," + tempAuthor + "," + tempGenre + "," + tempLength + "," + tempState + "," + tempStoreNumber + "," + to_string(tempQuantity);
				stateMap[state][storeNumber].erase(book);
				stateMap[state][storeNumber].insert(make_pair(book, data));
				saveBooks();
				return true;
			}
		}
	}
	cout << "Book not found" << endl;
	return false; //book not found
}
