#pragma once

#include <iostream> 
#include "item.h"

class MusicAlbum :
public Item
{
    set<string> members;
public:
    MusicAlbum(void); // Default constructor
    MusicAlbum(const string& title, const string& author, const int nPages) : Item(title, author, nPages){}; // Constructor
    MusicAlbum(const MusicAlbum&); // Copy constructor
    ~MusicAlbum(void); // Destructor
    virtual MusicAlbum& operator=(const Item&); // Assignment overload
    virtual Item *clone() const; // Copy constructor helper 
    virtual ostream& print(ostream& out) const; // << overload helper
    const set<string> getMembers(void) const;
    void setMembers(const string& memberIn);
};
