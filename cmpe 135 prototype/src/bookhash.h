/*
 * bookhash.h
 *
 *  Created on: Nov 28, 2019
 *      Author: Brandon Neep
 */

#ifndef BOOKHASH_H_
#define BOOKHASH_H_


#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

const int max_size = 1000;

class bookhash
{
public:
	bookhash()
{
		for(int i = 0; i< max_size; i++)
		{
			bookinventory[i] = NULL;
		}
}
	int hash(string title);
	void find(string title);
    void insert(string title, int length, string genre, string author, int cost);
    void removeBook(string title);

private:
	struct Book
	{
		string title;
		int length;
		string genre;
		string author;
		int cost;
		Book *next;
	};
	Book* bookinventory[max_size];
};


#endif /* BOOKHASH_H_ */
