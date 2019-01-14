package library;
import java.util.*;

class Book
	extends Item
{

    public Book()
    {
        super();

        boolean debug = false;

        if (debug == true)
            System.out.println("Book constructor ");

    }

    public String toString()
    {
        String text;

        boolean debug = false;

        if (debug == true)
            System.out.println("Book toString ");

        text = "-Book-\n";
        text += "author:   " + this.person + "\n";
        text += "# pages:  " + this.numberItems + "\n";
        text += super.toString();

        return text; 
    }

    public String[] getKeywords()
    {
        boolean debug = false;

        if (debug == true)
            System.out.println("Book getKeywords ");

        return super.getKeywords();
    }

    public int getNumberItems()
    {
        boolean debug = false;

        if (debug == true)
            System.out.println("Book getNumberItems ");

        return super.getNumberItems();
    }

    public String getPerson()
    {
        boolean debug = false;

        if (debug == true)
            System.out.println("Book getPerson ");

        return super.getPerson();
    }

    public String getTitle()
    {
        boolean debug = false;

        if (debug == true)
            System.out.println("Book getTitle ");

        return super.getPerson();
    }

    public void setKeywords(String... keywordsIn)
    {
        boolean debug = false;

        if (debug == true)
        {
            System.out.println("Book setKeywords ");
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
            System.out.println("Book setNumberItems ");
            System.out.println("numItemsIn = " + numItemsIn);
        }

        super.setNumberItems(numItemsIn);
    }

    public void setPerson(String personIn)
    {
        boolean debug = false;

        if (debug == true)
        {
            System.out.println("Book setPerson ");
            System.out.println("personIn = " + personIn);
        }

        super.setPerson(personIn);
    }
  
    public void setTitle(String titleIn)
    {
        boolean debug = false;

        if (debug == true)
        {
            System.out.println("Book setTitle ");
            System.out.println("titleIn = " + titleIn);
        }
    
        super.setTitle(titleIn);
    }
}
