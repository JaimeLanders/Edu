// Each book, music album, or movie will be an instance of a subclass of this class.
// Instances of this class should not be created. Specifying it as 'abstract' ensures
// that they cannot.

package library;
import java.util.*; 

public abstract class Item
{
    protected Set<String> keywords;// = new TreeSet<>();
//    protected Set<String> keywords = new TreeSet<>();
    protected int numberItems;
    protected String person;
    protected String title;

    public Item()
    {
        keywords = null;
        numberItems = 0;
        person = null;
        title = null;
    }

/*    public abstract String[] getKeywords();
    public abstract int getNumberItems();
    public abstract String getPerson();
    public abstract String getTitle();

    public abstract void setKeywords(String... keywordsIn);
    public abstract void setNumberItems(int numItemsIn);
    public abstract void setPerson(String personIn);
    public abstract void setTitle(String titleIn);
*/
    public String toString()
    {
        String text;

        text = "title:    " + this.title + "\n";
        text += "keywords: ";
        Iterator<String> it = this.keywords.iterator(); 
        while (it.hasNext())
        {
            String n = it.next();
            text += n;
            if (it.hasNext())
                text += ", " ;
        }
        text += "\n";

        return text; 
    }

    public String[] getKeywords()
    {
        String[] temp = this.keywords.toArray(new String[this.keywords.size()]);
        return temp;
    }

    public int getNumberItems()
    {
        return this.numberItems;
    }

    public String getPerson()
    {
        return this.person;
    }

    public String getTitle()
    {
        return this.title;
    }

    public void setKeywords(String... keywordsIn)
    {
        this.keywords = new TreeSet<String>();
        for (String n : keywordsIn)
            this.keywords.add(n); 

    }
    public void setNumberItems(int numItemsIn)
    {
        this.numberItems = numItemsIn;
    }

    public void setPerson(String personIn)
    {
        this.person = personIn;
    }
  
    public void setTitle(String titleIn)
    {
        this.title = titleIn;
    }
}
