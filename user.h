#ifndef USER_H_
#define USER_H_

#include <iostream>
#include <string>
#include <map>

using namespace std;

class User
{
public:

	User();
	
	void set_username(string username);
	
	void set_password(string password);
	
	void set_state(string state);

	void updateUser(map<string, map<int, map<string, string> > > bookList);

	void addToWatch(string title);
	
	void removeWatch(string book);

	string get_username();
	
	string get_password();
	
	string get_state();
	

private:
	string Username;
	string State;
	string Password;
	map <string, string> watchList;
	int watchListCount = 0;
	
};



#endif /* USER_H_ */