#include "movie.h"

Movie::Movie(void)
{
}

Movie::Movie(const Movie& movie) // Copy constructor needed?
{
    this->title = movie.getTitle();
    this->artist = movie.getArtist();
    this->nItems = movie.getNItems();
    this->keywords = movie.getKeywords();
}

Movie& Movie::operator=(const Item& movie) // Assignment overload needed?
{
    delete this;

    this->title = movie.getTitle();
    this->artist = movie.getArtist();
    this->nItems = movie.getNItems();
    this->keywords = movie.getKeywords();

    return *this;
}

Item * Movie::clone() const
{
    Movie *nMovie = new Movie();

    nMovie->title = this->title;
    nMovie->artist = this->artist;
    nMovie->nItems = this->nItems;
    nMovie->keywords = this->keywords;

    return nMovie;

}

Movie::~Movie(void)
{
}

ostream& Movie::print(ostream& out) const
{
    out << "-Movie- \n";
    out << "director: " << this->getArtist() << "\n";
    out << "# scenes: " << this->getNItems() << "\n";
    out << "cast:     ";
    set<string> tempSet = this->getCast();
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
    out << "title:    " << this->getTitle() << "\n";//  std::endl; 
    out << "keywords: ";
    tempSet = this->getKeywords();
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
const set<string> Movie::getCast(void) const
{
    return this->cast;
}

void Movie::setCast(const string& castIn)
{
    this->cast.insert(castIn);
}
