#ifndef USER_H_
#define USER_H_

#include <iostream>
#include <string>

using namespace std;

class User
{
public:

	User();
	
	void set_username(string username);
	
	void set_password(string password);
	
	void set_state(string state);
	

	string get_username();
	
	string get_password();
	
	string get_state();
	

private:
	string Username;
	string State;
	string Password;
};



#endif /* USER_H_ */