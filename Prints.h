#include <iostream>
#include <string>

#ifndef PRINTS_H_
#define PRINTS_H_

using namespace std;

class Prints
{
public:
    virtual string getDetails() = 0;
    virtual double cost() = 0;

};



#endif /* PRINTS_H_ */
