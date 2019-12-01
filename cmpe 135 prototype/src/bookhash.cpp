/*
 * bookhash.cpp
 *
 *  Created on: Nov 28, 2019
 *      Author: Brandon Neep
 */
#include "bookhash.h"
#include <iostream>
	int bookhash::hash(string title)
	{
		int temp = 1;

		for( int i = 0; i< title.length(); i ++)
		{
			temp = temp * title[i];
		}


		return abs((temp) % max_size);
	}

	void bookhash::find(string title)
	{
		int index = hash(title);
		Book* current = bookinventory[index];
		int count = 0;
		if(bookinventory[index] == NULL)
		{
			cout<<"title "<< title << " not found"<<endl;
			return;
		}

		while(current->title != title)
		{
			count ++;

			current = current ->next;
			if(current == 0)
			{
				cout<<"Title "<<title<<  " not found in hash table"<<endl;
				return;
			}
		}

		cout<<"found "<< current->title<< " in slot "<< index << ", node "<< count<<endl;
		cout<<"Length: "<< current->length<<endl;
		cout<<"Genre: "<< current->genre<<endl;
		cout<<"Author: "<< current->author<<endl;
		cout<<"Cost:  "<< current->cost<<endl;
	}

	void bookhash::insert(string title, int length, string genre, string author, int cost)
	{
		int index = hash(title);
		Book* book= new Book;
		book->title = title;
		book->length = length;
		book->genre = genre;
		book->author = author;
		book->cost = cost;
		book->next = bookinventory[index];
		bookinventory[index] = book;
		cout<<"inserted "<< title << " at "<< index<< endl;
	}

	void bookhash::removeBook(string title)
	{
		int index = hash(title);
		Book* current = bookinventory[index];
		int count = 0;
		if(bookinventory[index] == NULL)
		{
			cout<<"title "<< title << " not found"<<endl;
			return;
		}

		while(current->title != title)
		{
			count ++;

			current = current ->next;
			if(current == 0)
			{
				cout<<"Title "<<title<<  " not found in hash table"<<endl;
				return;
			}
		}
        bookinventory[index] = NULL;
        current->next = NULL;
	}
