/*
 * printDetails.h
 *
 *  Created on: Nov 14, 2019
 *      Author: Brandon Neep
 */


#ifndef PRINTDETAILS_H_
#define PRINTDETAILS_H_


#include <string>
#include <iostream>

using namespace std;

class printDetails
{
public:
	string getDetails();
	void setDetails();
private:
	string Title;
	string Length;
	string Genre;
	string Author;
	string Cost;

};



#endif /* PRINTDETAILS_H_ */
