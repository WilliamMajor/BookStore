#ifndef BOOKDETAILS_H_
#define BOOKDETAILS_H_


#include <string>
#include <iostream>
#include "printDetails.h"

using namespace std;

class Title : public printDetails
{
public:
    Title(Prints *basePrint) : printDetails(basePrint) {}

    string getDetails()
    {
        string title;
        cout << "Title: ";
        cin >> title;
        return m_Prints->getDetails() + title;
    }
};

class Length : public printDetails
{
public:
    Length(Prints *basePrint) : printDetails(basePrint) {}

    string getDetails()
    {
        string length;
        cout << "Length: ";
        cin >> length;
        return m_Prints->getDetails() + "," + length;
    }
    

};

class Genre : public printDetails
{
public:
    Genre(Prints *basePrint) : printDetails(basePrint) {}

    string getDetails()
    {
        string genre;
        cout << "Genre: ";
        cin >> genre;
        return m_Prints->getDetails() + "," + genre;
    }

};

class Author : public printDetails
{
public:
    Author(Prints *basePrint) : printDetails(basePrint) {}

    string getDetails()
    {
        string author;
        cout << "Author: ";
        cin >> author;
        return m_Prints->getDetails() + "," + author;
    }

};

class State : public printDetails
{
public:
    State(Prints *basePrint) : printDetails(basePrint) {}

    string getDetails()
    {
        string state;
        cout << "State: ";
        cin >> state;
        return m_Prints->getDetails() + "," + state;
    }
};

class StoreNumber : public printDetails
{
public:
    StoreNumber(Prints *basePrint) : printDetails(basePrint) {}

    string getDetails()
    {
        string storeNumber;
        cout << "Store Number: ";
        cin >> storeNumber;
        return m_Prints->getDetails() + "," + storeNumber;
    }
};

class Quantity : public printDetails
{
public:
	string quantity;
	Quantity(Prints *basePrint) : printDetails(basePrint) {}

	string getDetails()
	{
		cout << endl << "Quantity: ";
		cin >> quantity;
		return m_Prints->getDetails() + "," + quantity;
	}
};


#endif /* BOOKDETAILS_H_ */