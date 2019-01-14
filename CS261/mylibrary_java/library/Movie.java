package library;
import java.util.*;

class Movie
	extends Item
{
    Set<String> cast;

    public Movie()
    {
        super();

        boolean debug = false;

        if (debug == true)
            System.out.println("Movie constructor ");

    }

    public String toString()
    {
        String text;

        boolean debug = false;

        if (debug == true)
            System.out.println("Movie toString ");

        text = "-Movie-\n";
        text += "director: " + this.person + "\n";
        text += "# scenes: " + this.numberItems + "\n";
        text += "cast:     ";
        Iterator<String> it = this.cast.iterator(); 
        while (it.hasNext())
        {
            String n = it.next();
            text += n;
            if (it.hasNext())
                text += ", " ;
        }
        text += "\n";
        text += super.toString(); 

        return text; 
    }

    public String[] getCast()
    {
        boolean debug = false;

        if (debug == true)
            System.out.println("Movie getCast ");

        String[] temp = this.cast.toArray(new String[this.cast.size()]);
        return temp;
    }

    public String[] getKeywords()
    {
        boolean debug = false;

        if (debug == true)
            System.out.println("Movie getKeywords "); 
        return super.getKeywords();
    }

    public int getNumberItems()
    {
        boolean debug = false;

        if (debug == true)
            System.out.println("Movie getNumberItems ");

        return super.getNumberItems();
    }

    public String getPerson()
    {
        boolean debug = false;

        if (debug == true)
            System.out.println("Movie getPerson ");

        return super.getPerson();
    }

    public String getTitle()
    {
        boolean debug = false;

        if (debug == true)
            System.out.println("Movie getTitle ");

        return super.getTitle();
    }

    public void setCast(String... castIn)
    {
        boolean debug = false;

        if (debug == true)
        {
            System.out.println("Movie setCast ");
            for(String n : castIn)
                System.out.println("cast = " + n);
            System.out.println("");
        }

        this.cast = new TreeSet<String>();
        for (String n : castIn)
            this.cast.add(n);
    }

    public void setKeywords(String... keywordsIn)
    {
        boolean debug = false;

        if (debug == true)
        {
            System.out.println("Movie setKeywords ");
            for(String n : keywordsIn)
                System.out.println("keyword = " + n);
        }

        super.setKeywords(keywordsIn);
    }

    public void setNumberItems(int numItemsIn)
    {
        boolean debug = false;

        if (debug == true)
        {
            System.out.println("Movie setNumberItems ");
            System.out.println("numItemsIn = " + numItemsIn);
        }

        super.setNumberItems(numItemsIn);
    }

    public void setPerson(String personIn)
    {
        boolean debug = false;

        if (debug == true)
        {
            System.out.println("Movie setPerson ");
            System.out.println("personIn = " + personIn);
        }

        super.setPerson(personIn);
    }
  
    public void setTitle(String titleIn)
    {
        boolean debug = false;

        if (debug == true)
        {
            System.out.println("Movie setTitle ");
            System.out.println("titleIn = " + titleIn);
        }

        super.setTitle(titleIn);
    }
}
