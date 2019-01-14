package library;
import java.util.*;

class MusicAlbum
	extends Item
{
    Set<String> members;// =  new TreeSet<>();

    public MusicAlbum()
    {
        super();

        boolean debug = false;

        if (debug == true)
            System.out.println("MusicAlbum constructor ");

        members = null;

    }

    public String toString()
    {
        String text;

        boolean debug = false;

        if (debug == true)
            System.out.println("MusicAlbum toString ");

        text = "-Music Album-\n";
        text += "band:     " + this.person + "\n";
        text += "# songs:  " + this.numberItems + "\n";
        text += "members:  ";
        Iterator<String> it = this.members.iterator(); 
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

    public String[] getKeywords()
    {
        boolean debug = false;

        if (debug == true)
            System.out.println("MusicAlbum getKeywords ");

        return super.getKeywords();
    }

    public String[] getMembers()
    {
        boolean debug = false;

        if (debug == true)
            System.out.println("MusicAlbum getMembers ");

        String[] temp = this.members.toArray(new String[this.members.size()]);
        return temp;
    }

    public int getNumberItems()
    {
        boolean debug = false;

        if (debug == true)
            System.out.println("MusicAlbum getNumberItems ");

        return super.getNumberItems();
    }

    public String getPerson()
    {
        boolean debug = false;

        if (debug == true)
            System.out.println("MusicAlbum getPerson ");

        return super.getPerson();
    }

    public String getTitle()
    {
        boolean debug = false;

        if (debug == true)
            System.out.println("MusicAlbum getTitle ");

        return super.getTitle();
    }

    public void setKeywords(String... keywordsIn)
    {
        boolean debug = false;

        if (debug == true)
        {
            System.out.println("MusicAlbum setKeywords ");
            for(String n : keywordsIn)
                System.out.println("keyword = " + n);
        }

        super.setKeywords(keywordsIn);
    }

    public void setMembers(String... membersIn)
    {
        boolean debug = false;

        if (debug == true)
        {
            System.out.println("MusicAlbum setMembers ");
            for(String n : membersIn)
                System.out.println("member = " + n);
            System.out.println("");
        }

        this.members = new TreeSet<String>();
        for (String n : membersIn)
            this.members.add(n); 

    }

    public void setNumberItems(int numItemsIn)
    {
        boolean debug = false;

        if (debug == true)
        {
            System.out.println("MusicAlbum setNumberItems ");
            System.out.println("numItemsIn = " + numItemsIn);
        }

        super.setNumberItems(numItemsIn);
    }

    public void setPerson(String personIn)
    {
        boolean debug = false;

        if (debug == true)
        {
            System.out.println("MusicAlbum setPerson ");
            System.out.println("personIn = " + personIn);
        }

        super.setPerson(personIn);
    }
  
    public void setTitle(String titleIn)
    {
        boolean debug = false;

        if (debug == true)
        {
            System.out.println("MusicAlbum setTitle ");
            System.out.println("titleIn = " + titleIn);
        }

        super.setTitle(titleIn);
    }
}
