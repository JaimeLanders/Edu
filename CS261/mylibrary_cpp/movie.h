#pragma once

#include "item.h"
#include <iostream> 

class Movie :
public Item
{
    set<string> cast;
public:
    Movie(void); // Default constructor
    ~Movie(void); // Destructor
    Movie(const string& title, const string& director, const int nScenes) : Item(title, director, nScenes){}; // Constructor
    Movie(const Movie&); // Copy constructor
    virtual Movie& operator=(const Item&); // Assignment overload
    virtual Item *clone() const; // Copy constructor helper 
    virtual ostream& print(ostream& out) const; // << overload helper
    const set<string> getCast(void) const;
    void setCast(const string& castIn);
};
