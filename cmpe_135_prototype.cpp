//============================================================================
// Name        : cmpe.cpp
// Author      : Brandon Neep
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>
#include "user.h"
#include "prints.h"
#include "printDetails.h"
#include "bookDetails.h"
#include "concreateComponents.h"

using namespace std;

void runLoginMenu();




//TODO these will check strings of hash map to ensure
// 1. Username exists
// 2. Password matches

//bool enter_usersname()
//{
//
//}
//
//bool enter_password()
//{
//
//}

int main() {
	//runLoginMenu();
	//cout<<"login finished"<<endl;
	Prints *basePrint = new Book();

	Prints *decoratedPrint = new Title(basePrint);

	decoratedPrint = new Length(decoratedPrint);
	decoratedPrint = new Genre(decoratedPrint);
	decoratedPrint = new Author(decoratedPrint);

	cout << decoratedPrint -> getDetails() << endl;
	cout << decoratedPrint -> cost() << endl;


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
	}

	if(menu_select == 1)
	{
		User *new_user = new User();
		string temp;
		cout<<"Enter Username: ";
		cin>>temp;
		new_user->set_username(temp);

		cout<<"Enter Password: ";
		cin>>temp;
		new_user->set_password(temp);

		cout<<"Enter the state you live in: ";
		cin>>temp;
		new_user->set_state(temp);

		cout<<new_user->get_username()<<endl;
		cout<<new_user->get_password()<<endl;
		cout<<new_user->get_state()<<endl;

		//TODO enter username/password into hashmap for login purposes

	}

	if(menu_select == 2)
	{
//		if(enter_username())
//		{
//			if(enter_password())
//			{
//
//			}
//			else
//			{
//				cout<<"incorrect password"<<endl;
//			}
//		}
//		else
//		{
//			cout<<"invalid username"<<endl;
//		}

		return;
	}
	if(menu_select == 3)
	{
		exit(0);
	}


}