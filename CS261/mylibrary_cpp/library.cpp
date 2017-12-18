#include <cstdarg>		// support macros for vararg
#include <iostream>
#include "library.h"

/* TODO:
 * xAdd book
 * xAdd keywords
 * xAdd music album
 * xAdd band members
 * xAdd movie
 * xAdd cast
 * xPrint items by title
 * xPrint items by keyword
 * xPrint books by author
 * xPrint albums by band
 * xPrint albums by member
 * xPrint movies by director
 * xPrint movies by cast 
 * xDelete set contents 
 * xDelete map contents
 * xFix dependence on casting in keywords
 * Fix dependence on casting in addBandMembers and addCast
 *
 *  Bugs:
 * xItems sorted by title
 * xExtra comma on keywords output
 *  Missing/extra newline when printing items
*/

// general functions
/*Library::Library() // Needed ?
{
    // your code here
}
*/

Library::~Library()
{
    // your code here

    deleteItemSetContents(AlbumSet);
    deleteItemSetContents(BookSet);
    deleteItemSetContents(MovieSet);
    deleteMapContents(ItemMapByKeyword);
//    deleteMapContents(ItemMapByTitle);
    deleteMapContents(AlbumMapByBand);
    deleteMapContents(AlbumMapByMember);
    deleteMapContents(BookMapByAuthor);
    deleteMapContents(MovieMapByCast);
    deleteMapContents(MovieMapByDirector);
}

void Library::addKeywordsForItem(const Item* const item, int nKeywords, ...)
{
    // the code in this function demonstrates how to handle a vararg in C++

    va_list		keywords;
    char		*keyword;

    va_start(keywords, nKeywords);

    // Check AllItemSet for item
    
    Item * nItem;
//    Item * nItem = const_cast<Item*>(item); // Temp fix;

    map<string, ItemPtr>::iterator it;
    it = ItemMapByTitle.find(item->getTitle());
    nItem = it->second.getPtr();

    for (int i = 0; i < nKeywords; i++)
    {
	    keyword = va_arg(keywords, char*);

	    // do something with each keyword
        
        nItem->setKeywords(keyword);

        if (ItemMapByKeyword.find(keyword) == ItemMapByKeyword.end()) // Case 1 - keyword not mapped
        {
            ItemSet * tempSet = new ItemSet();

            tempSet->insert(nItem);
            ItemMapByKeyword.insert(std::make_pair(keyword, tempSet));
        }
        else // Case 2 - keyword already mapped
        {
            ItemSet * tempSet = ItemMapByKeyword[keyword];

            tempSet->insert(nItem);
            ItemMapByKeyword.insert(std::make_pair(keyword, tempSet));
        }
    }

    va_end(keywords);
}

const ItemSet* Library::itemsForKeyword(const string& keyword) const
{
    // your code here
    
    const ItemSet * tempSet;

    if (ItemMapByKeyword.find(keyword) != ItemMapByKeyword.end())
    {
        tempSet = ItemMapByKeyword.at(keyword);

        return tempSet;
    }
    else
    {
        return NULL;
    }
}

// book-related functions

const Item* Library::addBook(const string& title, const string& author, const int nPages)
{
    // your code here

    Book *nBook = new Book(title, author, nPages);

    BookSet.insert(nBook);
    
    if (BookMapByAuthor.find(author) == BookMapByAuthor.end()) // Case 1 - author not mapped
        {

            ItemSet * tempSet = new ItemSet();
            tempSet->insert(nBook);
            BookMapByAuthor.insert(std::make_pair(author, tempSet));
            ItemMapByTitle.insert(std::make_pair(title, nBook));
        }
        else // Case 2 -  already mapped
        {

            ItemSet * tempSet;
            tempSet = BookMapByAuthor[author];
            tempSet->insert(nBook);
            BookMapByAuthor.insert(std::make_pair(author, tempSet));
            ItemMapByTitle.insert(std::make_pair(title, nBook));
        }

    return nBook;
}

const ItemSet* Library::booksByAuthor(const string& author) const
{
    // your code here

    const ItemSet * tempSet;

    if (BookMapByAuthor.find(author) != BookMapByAuthor.end())
    {
        tempSet = BookMapByAuthor.at(author);

        return tempSet;
    }
    else
    {
        return NULL;
    }
}

const ItemSet* Library::books() const
{
    // your code here

    return &BookSet;
}

// music-related functions

const Item* Library::addMusicAlbum(const string& title, const string& band, const int nSongs)
{
    // your code here

    Item *nAlbum = new MusicAlbum(title, band, nSongs);
    AlbumSet.insert(nAlbum);
    
    if (AlbumMapByBand.find(band) == AlbumMapByBand.end()) // Case 1 - band not mapped
        {
            ItemSet * tempSet = new ItemSet();
            tempSet->insert(nAlbum);
            AlbumMapByBand.insert(std::make_pair(band, tempSet));
            ItemMapByTitle.insert(std::make_pair(title, nAlbum));
        }
        else // Case 2 -  already mapped
        {
            ItemSet * tempSet;
            tempSet = AlbumMapByBand[band];
            tempSet->insert(nAlbum);
            AlbumMapByBand.insert(std::make_pair(band, tempSet));
            ItemMapByTitle.insert(std::make_pair(title, nAlbum));
        }

    return nAlbum;
}

void Library::addBandMembers(const Item* const musicAlbum, const int nBandMembers, ...)
{
    // your code here

    va_list members;
    char *member;

    va_start(members, nBandMembers);

    for (int i = 0; i < nBandMembers; i++)
    {
	    member = va_arg(members, char*);

	    // do something with each keyword
        
        MusicAlbum * nMusicAlbum;

        map<string, ItemPtr>::iterator it;
        it = ItemMapByTitle.find(musicAlbum->getTitle());
        nMusicAlbum = (MusicAlbum*)it->second.getPtr(); // Temp fix

        nMusicAlbum->setMembers(member);

        if (AlbumMapByMember.find(member) == AlbumMapByMember.end()) // Case 1 - keyword not mapped
        {
            ItemSet * tempSet = new ItemSet();
            
            tempSet->insert(nMusicAlbum);
            AlbumMapByMember.insert(std::make_pair(member, tempSet));
        }
        else // Case 2 - keyword already mapped
        {
            ItemSet * tempSet = AlbumMapByMember[member];

            tempSet->insert(nMusicAlbum);
            AlbumMapByMember.insert(std::make_pair(member, tempSet));
        }
    }

    va_end(members);
}

const ItemSet* Library::musicByBand(const string& band) const
{
    // your code here
    
    const ItemSet * tempSet;

    if (AlbumMapByBand.find(band) != AlbumMapByBand.end())
    {
        tempSet = AlbumMapByBand.at(band);

        return tempSet;
    }
    else
    {
        return NULL;
    }
}

const ItemSet* Library::musicByMusician(const string& musician) const
{
    // your code here

    const ItemSet * tempSet;

    if (AlbumMapByMember.find(musician) != AlbumMapByMember.end())
    {
        tempSet = AlbumMapByMember.at(musician);

        return tempSet;
    }
    else
    {
        return NULL;
    }
}

const ItemSet* Library::musicAlbums() const
{
    // your code here

    return &AlbumSet;
}

// movie-related functions

const Item* Library::addMovie(const string& title, const string& director, const int nScenes)
{
    // your code here

    Item *nMovie = new Movie(title, director, nScenes);
    MovieSet.insert(nMovie);
    
    if (MovieMapByDirector.find(director) == MovieMapByDirector.end()) // Case 1 - director not mapped
        {
            ItemSet * tempSet = new ItemSet();
            tempSet->insert(nMovie);
            MovieMapByDirector.insert(std::make_pair(director, tempSet));
            ItemMapByTitle.insert(std::make_pair(title, nMovie));
        }
        else // Case 2 -  already mapped
        {
            ItemSet * tempSet;
            tempSet = MovieMapByDirector[director];
            tempSet->insert(nMovie);
            MovieMapByDirector.insert(std::make_pair(director, tempSet));
            ItemMapByTitle.insert(std::make_pair(title, nMovie));
        }

    return nMovie;
}

void Library::addCastMembers(const Item* const movie, const int nCastMembers, ...)
{
    // your code here

    va_list cast;
    char *castMember;

    va_start(cast, nCastMembers);

    for (int i = 0; i < nCastMembers; i++)
    {
	    castMember = va_arg(cast, char*);

	    // do something with each keyword
        
        Movie * nMovie;

        map<string, ItemPtr>::iterator it;
        it = ItemMapByTitle.find(movie->getTitle());
        nMovie = (Movie*)it->second.getPtr(); // Temp fix

        nMovie->setCast(castMember);

        if (MovieMapByCast.find(castMember) == MovieMapByCast.end()) // Case 1 - keyword not mapped
        {
            ItemSet * tempSet = new ItemSet();
            
            tempSet->insert(nMovie);
            MovieMapByCast.insert(std::make_pair(castMember, tempSet));
        }
        else // Case 2 - keyword already mapped
        {
            ItemSet * tempSet = MovieMapByCast[castMember];

            tempSet->insert(nMovie);

            MovieMapByCast.insert(std::make_pair(castMember, tempSet));
        }

    }

    va_end(cast);
}

const ItemSet* Library::moviesByDirector(const string& director) const
{
    // your code here
    const ItemSet * tempSet;

    if (MovieMapByDirector.find(director) != MovieMapByDirector.end())
    {
        tempSet = MovieMapByDirector.at(director);

        return tempSet;
    }
    else
    {
        return NULL;
    }
}

const ItemSet* Library::moviesByActor(const string& actor) const
{
    const ItemSet * tempSet;

    if (MovieMapByCast.find(actor) != MovieMapByCast.end())
    {
        tempSet = MovieMapByCast.at(actor);

        return tempSet;
    }
    else
    {
        return NULL;
    }
    return NULL;
}

const ItemSet* Library::movies() const
{
    // your code here

    return &MovieSet;
}

static void deleteMapContents(StringToItemSetMap& s2ism)
{
    // your code here

    // Iterate through map
    for(std::map<string, ItemSet*>::iterator it = s2ism.begin(); it != s2ism.end(); )
    {
        // Iterate through set
        ItemSet *tempSet = it->second;

        for(std::set<ItemPtr>::iterator it2 = tempSet->begin(); it2 != tempSet->end(); )
        {
          
            if (next((it2),1) != tempSet->end())        
                it2 = tempSet->erase(it2);
            else
                ++it2;
        }

//        tempSet->clear();
          delete tempSet; // Test, put in item constructor?

        if (next((it),1) != s2ism.end())        
            it = s2ism.erase(it);
        else
            ++it;
    }
     
//    s2ism.clear();

}

static void deleteItemSetContents(ItemSet& itemSet)
{
    // your code here

    for(std::set<ItemPtr>::iterator it = itemSet.begin(); it != itemSet.end(); )
    {
        delete it->getPtr();

        if (next((it),1) != itemSet.end())        
            it = itemSet.erase(it);
        else
            ++it;
    }

//    itemSet.clear();
}
