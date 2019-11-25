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
        return m_Prints->getDetails() + " test title";
    }

};

class Length : public printDetails
{
public:
    Length(Prints *basePrint) : printDetails(basePrint) {}

    string getDetails()
    {
        return m_Prints->getDetails() + " test length";
    }

};

class Genre : public printDetails
{
public:
    Genre(Prints *basePrint) : printDetails(basePrint) {}

    string getDetails()
    {
        return m_Prints->getDetails() + " test genre";
    }

};

class Author : public printDetails
{
public:
    Author(Prints *basePrint) : printDetails(basePrint) {}

    string getDetails()
    {
        return m_Prints->getDetails() + " test author";
    }

};


#endif /* BOOKDETAILS_H_ */