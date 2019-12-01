/*
 * userhash.cpp
 *
 *  Created on: Nov 24, 2019
 *      Author: Brandon Neep
 */

#include "userhash.h"
#include <iostream>


int userhash::hash(string username)
{
	int temp = 1;

	for( int i = 0; i< username.length(); i ++)
	{
		temp = temp * username[i];
	}


	return abs((temp) % userhash_size);
}

void userhash::find(string username)
{
	int index = hash(username);
	User* current = inventory[index];
	int count = 0;
	if(inventory[index] == NULL)
	{
		cout<<"username "<< username << " not found"<<endl;
		return;
	}

	while(current->username != username)
	{
		count ++;

		current = current ->next;
		if(current == 0)
		{
			cout<<"username "<<username<<  " not found in hash table"<<endl;
			return;
		}
	}

	cout<<"found "<< username<< " in slot "<< index << ", node "<< count<<endl;
}

bool userhash::checkusername(string username)
{
	int index = hash(username);
	User*current = inventory[index];
	int count = 0;
	if(inventory[index] == NULL)
	{
		cout<<"username "<< username << " not found"<<endl;
		return(0);
	}
	while(current->username != username)
	{
		count ++;

		current = current ->next;
		if(current == 0)
		{
			cout<<"username "<<username<<  " not found in hash table"<<endl;
			return(0);
		}
	}
	return(1);

}

bool userhash::checkpassword(string username, string password)
{
	int index = hash(username);
	User*current = inventory[index];
	int count = 0;
	while(current->username != username)
	{
		count ++;

		current = current ->next;
		if(current == 0)
		{
			cout<<"username "<<username<<  " not found in hash table"<<endl;
			return(0);
		}
	}

	if(current->password!= password)
	{
		cout<<"Incorrect password"<<endl;
		return(0);
	}
	else return(1);
}

void userhash::insert(string username , string password, string state)
{
	int index = hash(username);
	User* node= new User;
	node->username = username;
	node->password = password;
	node->state    = state;
	node->next = inventory[index];
	inventory[index] = node;
	//cout<<"inserted "<< username << " at "<< index<< endl;
}


string userhash::returnstate(string username)
{
	int index = hash(username);
	User*current = inventory[index];
	return current->state;
}
