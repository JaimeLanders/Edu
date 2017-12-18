#include "book.h"

Book::Book(void)
{
}


Book::Book(const Book& book) // Copy constructor needed?
{
    this->title = book.title;
    this->artist = book.artist;
    this->nItems = book.nItems;
    this->keywords = book.keywords;
}

Book& Book::operator=(const Item& book) // Assignment overload needed?
{
    delete this;

    this->title = book.getTitle();
    this->artist = book.getArtist();
    this->nItems = book.getNItems();
    this->keywords = book.getKeywords();

    return *this;
}

Item * Book::clone() const
{
    Book *nBook = new Book();

    nBook->title = this->getTitle();
    nBook->artist = this->artist;
    nBook->nItems = this->nItems;
    nBook->keywords = this->keywords;

    return nBook; // Returns new book
}

Book::~Book(void)
{
}

ostream& Book::print(ostream& out) const
{
    out << "-Book- \n";
    out << "author:   " << this->getArtist() << "\n";
    out << "# pages:  " << this->getNItems() << "\n";
    out << "title:    " << this->getTitle() << "\n";
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
