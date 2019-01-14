#pragma once

#include <iostream> 
#include "item.h"

class Book : public Item
{
public:
    Book(void); // Default constructor
    Book(const string& title, const string& author, const int nPages) : Item(title, author, nPages){}; // Constructor
    Book(const Book&); // Copy constructor
    ~Book(void); // Destructor
    virtual Book& operator=(const Item&); // Assignment overload
    virtual Item *clone() const; // Copy constructor helper 
    virtual ostream& print(ostream& out) const; // << overload helper
};
