
#ifndef PRINTDETAILS_H_
#define PRINTDETAILS_H_


#include <string>
#include <iostream>
#include "Prints.h"

using namespace std;

class printDetails : public Prints
{
protected:
	Prints *m_Prints;
public:
	printDetails(Prints *basePrint) : m_Prints(basePrint){}

	string getDetails()
	{
		return m_Prints->getDetails();
	}
	double cost()
	{
		return m_Prints->cost();
	}
};



#endif /* PRINTDETAILS_H_ */
