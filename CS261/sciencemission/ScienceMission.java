import java.io.File;
import java.io.FileInputStream;
import java.io.InputStream;
import java.io.FileNotFoundException;
import java.util.*;
import java.util.regex.Pattern;

public class ScienceMission
{
    private static List<Probe> probeList = new LinkedList<>();

    private static InputStream getFileInputStream(String fileName) throws Exception
    {
	    InputStream inputStream;

	    try
        {
	        inputStream = new FileInputStream(new File(fileName));
	    }
	    catch (FileNotFoundException e)
        {
	        inputStream = null;
	        throw new Exception("unable to open the file -- " + e.getMessage());
	    }
	    return inputStream;
    }

    ScienceMission(String filename)
    {
	    try
        {
	        InputStream log = getFileInputStream(filename);
	        Scanner sc = new Scanner(log);
	        sc.useDelimiter(Pattern.compile("\n"));
	        while (sc.hasNext())
		    {
		       String temp = sc.next(); 
               Probe nProbe = new Probe(sc);
               nProbe.setName(temp);
               probeList.add(nProbe);
            }
            sc.close();
        }
        
        catch (Exception e)
        {
            System.out.println("Error: " + e.getMessage());
        }

    }

    public static void startMission(Environment envIn)
    {
        for (Probe n : probeList)
        {
            n.launchProbe();
            n.activateProbe(envIn);
            n.recallProbe();
        }
    }
   
}
