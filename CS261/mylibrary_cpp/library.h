// do not remove any of the function prototypes from this class definition

#pragma once

#include <iostream>
#include <map>
#include <set>
#include <string>
#include "item.h"
#include "book.h" // Needed ?
#include "movie.h" // Needed ?
#include "musicalbum.h" // Needed ?

using namespace std;

// C++ Standard Library definitions for containers you may need
typedef set<string>	StringSet;
typedef set<ItemPtr> ItemSet;		// see comment in Item.h about use of ItemPtr
typedef map<string,ItemSet*> StringToItemSetMap;

class Library
{
private:
    ItemSet AlbumSet;
    ItemSet BookSet;
    ItemSet MovieSet;
    StringSet KeywordSet;
    StringToItemSetMap AlbumMapByBand;
    StringToItemSetMap AlbumMapByMember;
    StringToItemSetMap BookMapByAuthor;
    StringToItemSetMap ItemMapByKeyword;
    map<string, ItemPtr> ItemMapByTitle;
    StringToItemSetMap MovieMapByCast;
    StringToItemSetMap MovieMapByDirector;
public:
    // general functions
    void addKeywordsForItem(const Item* const item, int nKeywords, ...);
    const ItemSet* itemsForKeyword(const string& keyword) const;

    // book-related functions
    const Item* addBook(const string& title, const string& author, const int nPages);
    const ItemSet* booksByAuthor(const string& author) const;
    const ItemSet* books() const;			// returns set containing all the books

    // music-related functions
    const Item* addMusicAlbum(const string& title, const string& band, const int nSongs);
    void addBandMembers(const Item* const musicCD, int nBandMembers, ...);
    const ItemSet* musicByBand(const string& band) const;
    const ItemSet* musicByMusician(const string& musician) const;
    const ItemSet* musicAlbums() const;		// returns set containing all the music

    // movie-related functions
    const Item* addMovie(const string& title, const string& director, const int nScenes);
    void addCastMembers(const Item* const movie, const int nCastMembers, ...);
    const ItemSet* moviesByDirector(const string& director) const;
    const ItemSet* moviesByActor(const string& actor) const;
    const ItemSet* movies() const;			// returns set containing all the movies

//    virtual Library(); // Needed?
    virtual ~Library();
};

static void deleteMapContents(StringToItemSetMap& s2ism);
static void deleteItemSetContents(ItemSet& itemSet);
