#include "musicalbum.h"

MusicAlbum::MusicAlbum(void)
{
}

MusicAlbum::MusicAlbum(const MusicAlbum& album) // Copy constructor needed?
{
    this->title = album.getTitle();
    this->artist = album.getArtist();
    this->nItems = album.getNItems();
    this->keywords = album.getKeywords();
}

MusicAlbum& MusicAlbum::operator=(const Item& album) // Assignment overload needed?
{
    delete this;

    this->title = album.getTitle();
    this->artist = album.getArtist();
    this->nItems = album.getNItems();
    this->keywords = album.getKeywords();

    return *this;
}

Item * MusicAlbum::clone() const
{
    MusicAlbum *nMusicAlbum = new MusicAlbum();

    nMusicAlbum->title = this->title;
    nMusicAlbum->artist = this->artist;
    nMusicAlbum->nItems = this->nItems;
    nMusicAlbum->keywords = this->keywords;

    return nMusicAlbum;
}

MusicAlbum::~MusicAlbum(void)
{
}

ostream& MusicAlbum::print(ostream& out) const
{
    out << "-Music Album- \n";
    out << "band:     " << this->getArtist() << "\n";
    out << "# songs:  " << this->getNItems() << "\n";
    out << "members:  ";
    set<string> tempSet = this->getMembers();
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
    out << "title:    " << this->getTitle() << "\n";
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
    out << "\n";
    return out;

}
const set<string> MusicAlbum::getMembers(void) const
{
    return this->members;
}

void MusicAlbum::setMembers(const string& memberIn)
{
    this->members.insert(memberIn);
}
