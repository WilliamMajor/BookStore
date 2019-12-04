//============================================================================
// Name        : cmpe.cpp
// Author      : Brandon Neep
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================


#include <iostream>
#include <cstring>
#include <vector>
#include <fstream>
#include <string>
#include <array>

#include "bookhash.h"
#include "userhash.h"
using namespace std;



void nationalSearch(bookhash nationalArray[50][5], string title)
{
	for(int i = 0; i < 50; i++){
		for (int j = 0; j < 5; j++){
			nationalArray[i][j].find(title);
		}
	}
}

void stateSearch(bookhash stateArray[5], string title)
{
	for(int i = 0; i < 5; i++){
		stateArray[i].find(title);
	}
}



void loaduserinfo(userhash &table)
{
	ifstream infile("userinfo.txt");
	string a, b, c;

	while(infile >>a >> b >> c)
	{
		table.insert(a, b, c);
	}
}

string login_menu(userhash &table)
{
	string  username, password, state;
	int menu_select = 0;

	while(menu_select != 1 && menu_select != 2 && menu_select != 3)
	{
		cout<<"Select an option"<<endl;
		cout<<"1: Create User"<<endl;
		cout<<"2: Login"<<endl;
		cout<<"3: Quit"<<endl;
		cin>>menu_select;
		//TODO menu breaks when chars are inputted
		if(menu_select != 1 && menu_select != 2 && menu_select != 3)
		{
			cout<<"invalid option: select again"<<endl;
		}
		if(menu_select == 1)
		{
			bool is_valid = false;
			while(is_valid ==false)
			{
				cout<<"Enter Username: ";
				cin>>username;
				if(table.checkusername(username) == 1)
				{
					cout<<"Invalid username, or username taken. Try again"<<endl;
				}
				else
				{
					is_valid = true;
				}
			}

			cout<<"Enter Password: ";
			cin>>password;

			cout<<"Enter the state you live in: ";
			cin>>state;

			table.insert(username, password, state);

			ofstream log;
			log.open("userinfo.txt", fstream::app);
			log<<"\n"<<username<<" "<<password<<" "<<state;
			cout<<"Account created."<<endl;
			menu_select = 2;

		}

		if(menu_select == 2)
		{
			if(username == "")
			{
				cout<<"Enter Username: ";
				cin>>username;
			}
			if(table.checkusername(username))
			{
				if(password == "")
				{
					cout<<"Enter Password: ";
					cin>>password;
				}
				if(table.checkpassword(username, password))
				{

					cout<<"login successful"<<endl;
					return username;

				}
				else
				{
					password = "";
					cout<<endl;
					username = "";
					menu_select = 0;
				}
			}
			else
			{
				password = "";
				cout<<endl;
				username = "";
				menu_select = 0;
			}


		}
		if(menu_select == 3)
		{
			exit(0);
		}
	}
}

int statetoint(string state);


void user_menu(bookhash x[50][5], string username, userhash y)
{
	string tempvar;
	int menu_select = 0;
	while(1)
	{
		cout<<"Select an option"<<endl;
		cout<<"1: Search all stores"<<endl;
		cout<<"2: Search stores in your state"<<endl;
		cout<<"3: Log out"<<endl;

		while(menu_select != 1 && menu_select != 2 && menu_select != 3 && menu_select != 4)
		{
			cin>>menu_select;
			//TODO menu breaks when chars are inputted
			if(menu_select != 1 && menu_select != 2 && menu_select != 3 && menu_select != 4)
			{
				cout<<"invalid option: select again"<<endl;
			}
		}
		if(menu_select == 1)
		{
			cout<<"enter book title"<<endl;
			cin>>tempvar;
			nationalSearch(x, tempvar);
			menu_select = 0;

		}

		if(menu_select == 2)
		{
			cout<<"enter book title"<<endl;
			cin>>tempvar;
			int state = statetoint(y.returnstate(username));

			stateSearch(x[state], tempvar);

		}

		if(menu_select == 3)
		{
			cout<<"exiting"<<endl;
			exit(0);
		}
	}

}





	//TODO testing
	void loadbooktable(bookhash array[50][5])
	{
		ifstream infile("bookinfo.txt");
		string title, genre, author, state;
		int storenumber, cost, length;

		int state_int;
		while(infile >>title >> length >> genre >> author >> cost >> state >> storenumber)
		{
			state_int = statetoint(state);
			array[state_int][storenumber].insert(title, length, genre, author, cost);
		}
	}


	void import_books(bookhash array[50][5])
	{
		cout<<"enter textfilename + .txt  Example: textfile.txt"<<endl;
		string textfile;
		cin>>textfile;

		ifstream f(textfile.c_str());
		if(f.good())
		{
			ifstream infile(textfile);
			string title, genre, author, state;
			int storenumber, cost, length;
			int state_int;
			ofstream log;
			while(infile >>title >> length >> genre >> author >> cost >> state >> storenumber)
			{
				state_int = statetoint(state);
				array[state_int][storenumber].insert(title, length, genre, author, cost);
				log.open("bookinfo.txt", fstream::app);
				log<<"\n"<<title<<" "<<length<<" "<<genre<<" "<<author<<" "<<cost<<" "<<state<<" "<<storenumber;
			}




		}
		else
		{
			cout<<"couldn't find file"<<endl;
		}


	}

	void admin_menu(bookhash array[50][5])
	{
		string temp;
		int menu_select = 0;
		while(1)
		{
			cout<<"Select an option"<<endl;
			cout<<"1: add books"<<endl;
			cout<<"2: Quit"<<endl;

			while(menu_select != 1 && menu_select != 2 )
			{
				cin>>menu_select;
				//TODO menu breaks when chars are inputted
				if(menu_select != 1 && menu_select != 2 )
				{
					cout<<"invalid option: select again"<<endl;
				}
			}
			if(menu_select == 1)
			{
				import_books(array);
				menu_select = 0;
			}


			if(menu_select == 2)
			{
				exit(0);
			}
		}
	}

int main() {
	bookhash nationalArray[50][5];
	loadbooktable(nationalArray);
	userhash usertable;
	loaduserinfo(usertable);
	string username = login_menu(usertable);
	if(username != "admin")
	{
		user_menu(nationalArray, username, usertable);
	}

	if(username == "admin")
	{
		admin_menu(nationalArray);
		//TODO
		//add to admin_menu
	}


}








int statetoint(string state)
{
	if(state == "AK")
	{
		return(1);
	}
	if(state == "AL")
	{
		return(2);
	}
	if(state == "AZ")
	{
		return(3);
	}
	if(state == "AR")
	{
		return(4);
	}
	if(state == "CA")
	{
		return(5);
	}
	if(state == "CO")
	{
		return(6);
	}
	if(state == "CT")
	{
		return(7);
	}
	if(state == "DE")
	{
		return(8);
	}
	if(state == "FL")
	{
		return(9);
	}
	if(state == "GA")
	{
		return(10);
	}
	if(state == "HI")
	{
		return(11);
	}
	if(state == "ID")
	{
		return(12);
	}
	if(state == "IL")
	{
		return(13);
	}
	if(state == "IN")
	{
		return(14);
	}
	if(state == "IA")
	{
		return(15);
	}
	if(state == "KS")
	{
		return(16);
	}
	if(state == "KY")
	{
		return(17);
	}
	if(state == "LA")
	{
		return(18);
	}
	if(state == "ME")
	{
		return(19);
	}
	if(state == "MD")
	{
		return(20);
	}
	if(state == "MA")
	{
		return(21);
	}
	if(state == "MI")
	{
		return(22);
	}
	if(state == "MN")
	{
		return(23);
	}
	if(state == "MS")
	{
		return(24);
	}
	if(state == "MO")
	{
		return(25);
	}
	if(state == "MT")
	{
		return(26);
	}
	if(state == "NE")
	{
		return(27);
	}
	if(state == "NV")
	{
		return(28);
	}
	if(state == "NH")
	{
		return(29);
	}
	if(state == "NJ")
	{
		return(30);
	}
	if(state == "NM")
	{
		return(31);

	}
	if(state == "NY")
	{
		return(32);

	}
	if(state == "NC")
	{
		return(33);

	}
	if(state == "ND")
	{
		return(34);

	}
	if(state == "OH")
	{
		return(35);

	}
	if(state == "OK")
	{
		return(36);

	}
	if(state == "OR")
	{
		return(37);

	}
	if(state == "PA")
	{
		return(38);
	}
	if(state == "RI")
	{
		return(39);
	}
	if(state == "SC")
	{
		return(40);
	}
	if(state == "SD")
	{
		return(41);
	}
	if(state == "TN")
	{
		return(42);
	}
	if(state == "TX")
	{
		return(43);
	}
	if(state == "UT")
	{
		return(44);
	}
	if(state == "VT")
	{
		return(45);
	}
	if(state == "VA")
	{
		return(46);
	}
	if(state == "WA")
	{
		return(47);
	}
	if(state == "WV")
	{
		return(48);
	}
	if(state == "WI")
	{
		return(49);
	}
	if(state == "WY")
	{
		return(50);
	}
}
