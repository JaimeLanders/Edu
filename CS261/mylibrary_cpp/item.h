#pragma once

#include <ostream>
#include <set>
#include <string>

using namespace std;

class Item
{
protected:
//private:
    string       artist;
    set<string>  keywords;
    int          nItems;
    string       title;
public:
    Item(const string& title, const string& artist, const int nItems); // Added nItems
    Item();
    Item(const Item&); // Copy constructor needed?    
    virtual Item& operator=(const Item&); // Assignment overload needed?
    virtual ~Item();
    virtual Item *clone() const {return new Item(*this);} // Copy constructor helper 
    const set<string> getKeywords(void) const;
    const string getArtist(void) const;
    const string getTitle(void) const;
    int getNItems(void) const;
    virtual ostream& print(ostream& out) const;
    void setArtist(const string&);
    void setTitle(const string&);
    void setKeywords(const string&);
    void setNItems(const int);
};

// You can't store Item* in an ItemSet, because that would disable the automatic
// sorting that set does. Containers in the C++ STL are designed to store
// INSTANCES, not POINTERS to instances.
//
// Instead we store instances of ItemPtr in the ItemSet defined in Library.h.
// Each instance of ItemPtr contains a pointer to an instance of Item. In this way,
// the container can call operator< for ItemPtr (which can then call operator<
// for Item) to determine the order in which to store the items it's given.
//
// When you add a Book instance to an ItemSet, you can do things like this:
//
//		ItemSet		books;					// defined in Library.h
//		Item		*book = new Book(...);
//
//		books.insert(book);
//
// The STL's set class will internally generate an instance of ItemPtr
// which will contain the pointer to the instance of Book.

class ItemPtr
{
private:
    Item	*ptr;
public:
    ItemPtr(Item *ptr) : ptr(ptr) { }
    Item* getPtr() const { return ptr; }
};

// compare two instances of Item
bool operator<(const Item& i1, const Item& i2);

// compare two instances of ItemPtr
bool operator<(const ItemPtr& ip1, const ItemPtr& ip2);

ostream& operator<<(ostream& out, const Item* const item);
