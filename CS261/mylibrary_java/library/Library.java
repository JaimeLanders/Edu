package library;

import java.io.PrintStream;
import java.util.Collection;
import java.util.*;

public class Library
{
    Map<String, TreeMap<String, Item>> albumsByBand = new TreeMap<>();
    Map<String, TreeMap<String, Item>> albumsByMember = new TreeMap<>();
    Map<String, Item> albumsByTitle = new TreeMap<>();
    Map<String, TreeMap<String, Item>> booksByAuthor = new TreeMap<>();
    Map<String, Item> booksByTitle = new TreeMap<>();
    Map<String, TreeMap<String, Item>> itemsByKeyword = new TreeMap<>();
    Map<String, TreeMap<String, Item>> moviesByActor = new TreeMap<>();
    Map<String, TreeMap<String, Item>> moviesByDirector = new TreeMap<>();
    Map<String, Item> moviesByTitle = new TreeMap<>();

	// general methods
	
	// returns all of the items which have the specified keyword
	public Collection<Item> itemsForKeyword(String keyword)
	{
        boolean debug = false;

        TreeMap<String, Item> tempMap = new TreeMap<>();
	
        if (debug == true)
        {
            System.out.println("itemsForKeyword ");
            System.out.println("keyword = " + keyword);
        }

        if (itemsByKeyword.containsKey(keyword))
        {
            if (debug == true)
                System.out.println(keyword + " found\n");

            tempMap = itemsByKeyword.get(keyword);
        }
        else 
        {
            if (debug == true)
                System.out.println(keyword + " not found\n");
        }

		return tempMap.values();
	}
	
	// print an item from this library to the output stream provided
	public void printItem(PrintStream out, Item item)
	{
        boolean debug = false;

        if (debug == true)
        {
            System.out.println("printItem ");
        }

        System.out.println(item.toString());
	}
	
	// book-related methods
	
	// adds a book to the library
	public Item addBook(String title, String author, int nPages, String... keywords)
	{
        boolean debug = false;

        if (debug == true)
        {
            System.out.println("addBook ");
            System.out.println("title = " + title);
            System.out.println("author = " + author);
            System.out.println("nPages = " + nPages);
            for(String n : keywords)
                System.out.println("keyword = " + n);
        }

        Item nBook = new Book(); 
        nBook.setTitle(title);
        nBook.setPerson(author);
        nBook.setNumberItems(nPages);
        nBook.setKeywords(keywords);

        for(String n : keywords)
        {
            if (!itemsByKeyword.containsKey(n))
            {
                TreeMap<String, Item> nMap = new TreeMap<>();
                nMap.put(title, nBook);

                itemsByKeyword.put(n, nMap);
            }
            else
            {
                TreeMap<String, Item> nMap = itemsByKeyword.get(n);
                nMap.put(title, nBook);

                itemsByKeyword.put(n, nMap);
            }
        }

        if (!booksByAuthor.containsKey(author))
        {
            TreeMap<String, Item> nMap = new TreeMap<>();
            nMap.put(title, nBook);

            booksByAuthor.put(author, nMap);
        }
        else
        {
            TreeMap<String, Item> nMap = booksByAuthor.get(author);
            nMap.put(title, nBook);

            booksByAuthor.put(author, nMap);
 
        }

        booksByTitle.put(title, nBook);
           
        if (debug == true)
        {
            System.out.println(nBook.toString());
        }

		return nBook;
	}
	
	// removes a book from the library
	public boolean removeBook(String title)
	{
        boolean debug = false;

        if (debug == true)
        {
            System.out.println("removeBook ");
            System.out.println("title = " + title + "\n");
        }

        if (booksByTitle.containsKey(title))
        {
            if (debug == true)
                System.out.println(title + " found");
            
            Item tempBook = booksByTitle.get(title);
            String[] keywords = tempBook.getKeywords();
            String author = tempBook.getPerson();

            if (debug == true)
            {
                System.out.println("title = " + tempBook.getTitle());
                for(String keyword : keywords )
                    System.out.println("keyword = " + keyword);
                System.out.println("author = " + author);
            }
           
            for(String keyword : keywords)
            {
                if(itemsByKeyword.containsKey(keyword))
                {
                    if (debug == true)
                        System.out.println(keyword + " found");

                    TreeMap<String, Item> tempTree = itemsByKeyword.get(keyword);

                    Item tempItem = tempTree.get(title);
                    tempTree.remove(title);
                }
                else
                {
                    if (debug == true)
                        System.out.println(keyword + " not found");
                }
            }

            if(booksByAuthor.containsKey(author))
            {
                if (debug == true)
                    System.out.println(author + " found");

                TreeMap<String, Item> tempTree = booksByAuthor.get(author);

                tempTree.clear();

            }
            else
            {
                if (debug == true)
                    System.out.println(author + " not found");
            }

            booksByTitle.remove(title);

            return true;
        }
        else
        {
            if (debug == true)
                System.out.println(title + " not found");

		    return false;
        }
	}
	
	// returns all of the books by the specified author
	public Collection<Item> booksByAuthor(String author)
	{
        TreeMap<String, Item> tempMap = new TreeMap<>();

        boolean debug = false;

        if (debug == true)
        {
            System.out.println("booksByAuthor ");
            System.out.println("author = " + author);
        }

        if (booksByAuthor.containsKey(author))
        {
            if (debug == true)
                System.out.println(author + " found\n");

            tempMap = booksByAuthor.get(author);
        }
        else 
        {
            if (debug == true)
                System.out.println(author + " not found\n");
        }

		return tempMap.values();
	}
	
	// returns all of the books in the library
	public Collection<Item> books()
	{
        boolean debug = false;

        if (debug == true)
        {
            System.out.println("books ");
        }

		return booksByTitle.values();
	}
	
	// music-related methods
	
	// adds a music album to the library
	public Item addMusicAlbum(String title, String band, int nSongs, String... keywords)
	{
        boolean debug = false;

        if (debug == true)
        {
            System.out.println("addMusicAlbum ");
            System.out.println("title = " + title);
            System.out.println("band = " + band);
            System.out.println("nSongs = " + nSongs);
            for(String n : keywords)
                System.out.println("keyword = " + n);
        }

        Item nAlbum = new MusicAlbum(); 
        nAlbum.setTitle(title);
        nAlbum.setPerson(band);
        nAlbum.setNumberItems(nSongs);
        nAlbum.setKeywords(keywords);

        for(String n : keywords)
        {
            if (!itemsByKeyword.containsKey(n))
            {
                TreeMap<String, Item> nMap = new TreeMap<>();
                nMap.put(title, nAlbum);

                itemsByKeyword.put(n, nMap);
            }
            else
            {
                TreeMap<String, Item> nMap = itemsByKeyword.get(n);
                nMap.put(title, nAlbum);

                itemsByKeyword.put(n, nMap);
            }
        }

        if (!albumsByBand.containsKey(band))
        {
            TreeMap<String, Item> nMap = new TreeMap<>();
            nMap.put(title, nAlbum);

            albumsByBand.put(band, nMap);
        }
        else
        {
            TreeMap<String, Item> nMap = albumsByBand.get(band);
            nMap.put(title, nAlbum);

            albumsByBand.put(band, nMap);
        }

        albumsByTitle.put(title, nAlbum);

        if (debug == true)
        {
            System.out.println(nAlbum.toString());
        }

		return nAlbum;
	}

	// adds the specified band members to a music album
	public void addBandMembers(Item album, String... members)
	{
        boolean debug = false;

        if (debug == true)
        {
            System.out.println("addBandMembers ");
            System.out.println("album = " + album.getTitle());
            for(String n : members)
                System.out.println("member = " + n);
            System.out.println("");
        }

        MusicAlbum nAlbum = (MusicAlbum) album;
        nAlbum.setMembers(members);
            
        for (String member : members) 
        {
            if (!albumsByMember.containsKey(member))
            {
                TreeMap<String, Item> nMap = new TreeMap<>();
                nMap.put(nAlbum.getTitle(), nAlbum);

                albumsByMember.put(member, nMap);
            }
            else
            {
                TreeMap<String, Item> nMap = albumsByMember.get(member);
                nMap.put(nAlbum.getTitle(), nAlbum);

                albumsByMember.put(member, nMap);
            }
        }
	}
	
	// removes a music album from the library
	public boolean removeMusicAlbum(String title)
	{
        boolean debug = false;

        if (debug == true)
        {
            System.out.println("removeMusicAlbum ");
            System.out.println("title = " + title);
        }

        if (albumsByTitle.containsKey(title))
        {
            if (debug == true)
                System.out.println(title + " found");
            
            MusicAlbum tempAlbum = (MusicAlbum) albumsByTitle.get(title);
            String band = tempAlbum.getPerson();
            String[] keywords = tempAlbum.getKeywords();
            String[] members = tempAlbum.getMembers();

            if (debug == true)
            {
                System.out.println("title = " + tempAlbum.getTitle());
                for(String keyword : keywords)
                    System.out.println("keyword = " + keyword);
                System.out.println("band = " + band);
                
            }
           
            for(String keyword : keywords)
            {
                if(itemsByKeyword.containsKey(keyword))
                {
                    if (debug == true)
                        System.out.println(keyword + " found");

                    TreeMap<String, Item> tempTree = itemsByKeyword.get(keyword);

                    Item tempItem = tempTree.get(title);
                    tempTree.remove(title);
                }
                else
                {
                    if (debug == true)
                        System.out.println(keyword + " not found");
                }
            }

            if(albumsByBand.containsKey(band))
            {
                if (debug == true)
                    System.out.println(band + " found");

                TreeMap<String, Item> tempTree = albumsByBand.get(band);

                Item tempItem = tempTree.get(title);
                tempTree.remove(title);

            }
            else
            {
                if (debug == true)
                    System.out.println(band + " not found");
            }

            for(String member : members)
            {
                if(albumsByMember.containsKey(member))
                {
                    if (debug == true)
                        System.out.println(member + " found");

                    TreeMap<String, Item> tempTree = albumsByMember.get(member);

                    Item tempItem = tempTree.get(title);
                    tempTree.remove(title);
                }
                else
                {
                    if (debug == true)
                        System.out.println(member + " not found");
                }
            }

            albumsByTitle.remove(title);

            return true;
        }
        else
        {
            if (debug == true)
                System.out.println(title + " not found");

		    return false;
        }
	}

	// returns all of the music albums by the specified band
	public Collection<Item> musicByBand(String band)
	{
        TreeMap<String, Item> tempMap = new TreeMap<>();

        boolean debug = false;

        if (debug == true)
        {
            System.out.println("musicByBand ");
            System.out.println("band = " + band);
        }

        if (albumsByBand.containsKey(band))
        {
            if (debug == true)
                System.out.println(band + " found\n");

            tempMap = albumsByBand.get(band);
        }
        else 
        {
            if (debug == true)
                System.out.println(band + " not found\n");
        }

		return tempMap.values();
	}
	
	// returns all of the music albums by the specified musician
	public Collection<Item> musicByMusician(String musician)
	{
        TreeMap<String, Item> tempMap = new TreeMap<>();

        boolean debug = false;

        if (debug == true)
        {
            System.out.println("musicByMusician ");
            System.out.println("musician = " + musician);
        }

        if (albumsByMember.containsKey(musician))
        {
            if (debug == true)
                System.out.println(musician + " found\n");

            tempMap = albumsByMember.get(musician);
        }
        else 
        {
            if (debug == true)
                System.out.println(musician + " not found\n");
        }

		return tempMap.values();

	}
	
	// returns all of the music albums in the library
	public Collection<Item> musicAlbums()
	{
        boolean debug = false;

        if (debug == true)
        {
            System.out.println("musicAlbums ");
        }

		return albumsByTitle.values();
	}
	
	// movie-related methods
	
	// adds a movie to the library
	public Item addMovie(String title, String director, int nScenes, String... keywords)
	{
        boolean debug = false;

        if (debug == true)
        {
            System.out.println("addMovie ");
            System.out.println("title = " + title);
            System.out.println("director = " + director);
            System.out.println("nScenes = " + nScenes);
            for(String n : keywords)
                System.out.println("keyword = " + n);
        }

        Item nMovie = new Movie(); 
        nMovie.setTitle(title);
        nMovie.setPerson(director);
        nMovie.setNumberItems(nScenes);
        nMovie.setKeywords(keywords);

        for(String n : keywords)
        {
            if (!itemsByKeyword.containsKey(n))
            {
                TreeMap<String, Item> nMap = new TreeMap<>();
                nMap.put(title, nMovie);

                itemsByKeyword.put(n, nMap);
            }
            else
            {
                TreeMap<String, Item> nMap = itemsByKeyword.get(n);
                nMap.put(title, nMovie);

                itemsByKeyword.put(n, nMap);
            }
        }

        if (!moviesByDirector.containsKey(director))
        {
            TreeMap<String, Item> nMap = new TreeMap<>();
            nMap.put(title, nMovie);

            moviesByDirector.put(director, nMap);
        }
        else
        {
            TreeMap<String, Item> nMap = moviesByDirector.get(director);
            nMap.put(title, nMovie);

            moviesByDirector.put(director, nMap);
        }
        moviesByTitle.put(title, nMovie);

        if (debug == true)
        {
            System.out.println(nMovie.toString());
        }

		return nMovie;
	}

	// adds the specified actors to a movie
	public void addCast(Item movie, String... members)
	{
        boolean debug = false;

        if (debug == true)
        {
            System.out.println("addCast ");
            System.out.println("movie = " + movie.getTitle());
            for(String n : members)
                System.out.println("member = " + n);
            System.out.println("");
        }

        Movie nMovie = (Movie) movie;
        nMovie.setCast(members);

        for (String member : members) 
        {
            if (!moviesByActor.containsKey(member))
            {
                TreeMap<String, Item> nMap = new TreeMap<>();
                nMap.put(nMovie.getTitle(), nMovie);

                moviesByActor.put(member, nMap);
            }
            else
            {
                TreeMap<String, Item> nMap = moviesByActor.get(member);
                nMap.put(nMovie.getTitle(), nMovie);

                moviesByActor.put(member, nMap);
            }
        }
	}

	// removes a movie from the library
	public boolean removeMovie(String title)
	{
        boolean debug = false;

        if (debug == true)
        {
            System.out.println("removeMovie ");
            System.out.println("title = " + title);
        }

        if (moviesByTitle.containsKey(title))
        {
            if (debug == true)
                System.out.println(title + " found");
            
            Movie tempMovie = (Movie) moviesByTitle.get(title);
            String[] cast = tempMovie.getCast();
            String director  = tempMovie.getPerson();
            String[] keywords = tempMovie.getKeywords();

            if (debug == true)
            {
                System.out.println("title = " + tempMovie.getTitle());
                for(String keyword : keywords)
                    System.out.println("keyword = " + keyword);
                System.out.println("director = " + director);
                
            }
           
            for(String keyword : keywords)
            {
                if(itemsByKeyword.containsKey(keyword))
                {
                    if (debug == true)
                        System.out.println(keyword + " found");

                    TreeMap<String, Item> tempTree = itemsByKeyword.get(keyword);

                    Item tempItem = tempTree.get(title);
                    tempTree.remove(title);
                }
                else
                {
                    if (debug == true)
                        System.out.println(keyword + " not found");
                }
            }

            if(moviesByDirector.containsKey(director))
            {
                if (debug == true)
                    System.out.println(director + " found");

                TreeMap<String, Item> tempTree = moviesByDirector.get(director);

                Item tempItem = tempTree.get(title);
                tempTree.remove(title);

            }
            else
            {
                if (debug == true)
                    System.out.println(director + " not found");
            }

            for(String actor : cast)
            {
                if(moviesByActor.containsKey(actor))
                {
                    if (debug == true)
                        System.out.println(actor + " found");

                    TreeMap<String, Item> tempTree = moviesByActor.get(actor);

                    Item tempItem = tempTree.get(title);
                    tempTree.remove(title);
                }
                else
                {
                    if (debug == true)
                        System.out.println(actor + " not found");
                }
            }

            moviesByTitle.remove(title);

            return true;
        }
        else
        {
            if (debug == true)
                System.out.println(title + " not found");

		    return false;
        }
	}
	
	// returns all of the movies by the specified director
	public Collection<Item> moviesByDirector(String director)
	{
        TreeMap<String, Item> tempMap = new TreeMap<>();

        boolean debug = false;

        if (debug == true)
        {
            System.out.println("moviesByDirector ");
            System.out.println("director = " + director);
        }

        if (moviesByDirector.containsKey(director))
        {
            if (debug == true)
                System.out.println(director + " found\n");

            tempMap = moviesByDirector.get(director);
        }
        else 
        {
            if (debug == true)
                System.out.println(director + " not found\n");
        }

		return tempMap.values();
	}
	
	// returns all of the movies by the specified actor
	public Collection<Item> moviesByActor(String actor)
	{
        TreeMap<String, Item> tempMap = new TreeMap<>();

        boolean debug = false;

        if (debug == true)
        {
            System.out.println("moviesByActor ");
            System.out.println("actor = " + actor);
        }

        if (moviesByActor.containsKey(actor))
        {
            if (debug == true)
                System.out.println(actor + " found\n");

            tempMap = moviesByActor.get(actor);
        }
        else 
        {
            if (debug == true)
                System.out.println(actor + " not found\n");
        }

		return tempMap.values();
	}
	
	// returns all of the movies in the library
	public Collection<Item> movies()
	{
        boolean debug = false;

        if (debug == true)
        {
            System.out.println("movies ");
        }

		return moviesByTitle.values();
	}	
}
