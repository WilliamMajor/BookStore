#include <iostream>
#include <string>
#include "prints.h"

class Book : public Prints
{
    string getDetails()
    {
        return "";
    }

    double cost()
    {
        return 30.00;
    }
};

// class Journal : public Prints
// {
//     string getDetails()
//     {
//         return "Journal";
//     }

//     double cost()
//     {
//         return 30.00;
//     }
// };

// class Magazine : public Prints
// {
//     string getDetails()
//     {
//         return "Magazine";
//     }

//     double cost()
//     {
//         return 30.00;
//     }
// };