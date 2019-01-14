#include "item.h"
#include <iostream> 

Item::Item() // Default constructor
{
    // your code here
    this->title = {'\0'};
    this->artist = {'\0'};
    this->nItems = 0;
}

Item::Item(const string& title, const string& artist, const int nItems)
{
    // your code here

    this->title = title;
    this->artist = artist;
    this->nItems = nItems;
}

Item::Item(const Item& item) // Copy constructor
{
    Item * nItem;
    nItem = item.clone();
}

Item& Item::operator=(const Item& item) // Assignment overload needed?
{
//    *this = item;

//    return *this;
}

Item::~Item()
{
    // your code here
}

bool operator<(const Item& i1, const Item& i2)
{
    // your code here

    if (i1.getTitle() < i2.getTitle()) 
        return true;
    else
        return false;
}

bool operator<(const ItemPtr& ip1, const ItemPtr& ip2)
{
    // your code here

    if (ip1.getPtr()->getTitle() < ip2.getPtr()->getTitle()) 
        return true;
    else
        return false;
}

ostream& operator<<(ostream& out, const Item* const item)
{
    return item->print(out);
}

const string Item::getArtist() const
{
    return this->artist;
}

const set<string> Item::getKeywords(void) const
{
    return this->keywords;
}

const string Item::getTitle() const
{
    return this->title;
}

int Item::getNItems() const       
{
    return this->nItems;
}

ostream& Item::print(ostream& out) const
{
    out << "-Item- " << std::endl;
    out << "artist:   " << this->getArtist() << "\n";// std::endl; 
    out << "# items:  " << this->getNItems() << "\n";// std::endl; 
    out << "title:    " << this->getTitle() << "\n";//  std::endl; 
    out << "keywords: ";
    set<string> tempSet = this->getKeywords();
    for(set<string>::iterator it=tempSet.begin(); it != tempSet.end(); ++it)
    {
        out << *it;
        set<string>::iterator it2 = it;
        ++it2;

        if (it2 != tempSet.end())
            out << ", ";
        else
            out << "\n";
    }
    out << "\n"; // Temp

    return out;
}

void Item::setArtist(const string& artistIn)
{
    this->artist = artistIn;
}

void Item::setKeywords(const string& keywordIn)
{
    this->keywords.insert(keywordIn);
}

void Item::setNItems(const int nItemsIn)
{
    this->nItems = nItemsIn;
}

void Item::setTitle(const string& titleIn) 
{
    this->title = titleIn;
}
