/*
 * userhash.h
 *
 *  Created on: Nov 24, 2019
 *      Author: Brandon Neep
 */

#ifndef userhash_H_
#define userhash_H_

using namespace std;

#include <string>
const int userhash_size = 1000;


class userhash
{
public:
	userhash()
{
		for(int i = 0; i< userhash_size; i++)
		{
			inventory[i] = NULL;
		}
}
	int hash(string username);
	void find(string username);
	bool checkusername(string username);
	bool checkpassword(string username, string password);
	void insert(string username, string password, string state);
	string returnstate(string username);

private:
	struct User
	{
		string username;
		string password;
		string state;
		User* next;
	};

	User* inventory[userhash_size];
};





#endif /* userhash_H_ */
