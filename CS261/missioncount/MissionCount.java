import java.io.File;
import java.io.FileInputStream;
import java.io.InputStream;
import java.io.FileNotFoundException;
import java.util.Map;
import java.util.SortedMap;
import java.util.TreeMap;
import java.util.Scanner;
import java.util.regex.Pattern;

public class MissionCount
{
    private static SortedMap<String, SortedMap<String, Integer>> mMap = new TreeMap<String, SortedMap<String, Integer>>(); 
    private static SortedMap<String, Integer> nMap;

    // returns an InputStream that gets data from the named file
    private static InputStream getFileInputStream(String fileName) throws Exception
    {
	InputStream inputStream;

	try {
	    inputStream = new FileInputStream(new File(fileName));
	}
	catch (FileNotFoundException e) {		// no file with this name exists
	    inputStream = null;
	    throw new Exception("unable to open the file -- " + e.getMessage());
	}
	return inputStream;
    }
    

    public static void main(String[] args) {
	
	if (args.length != 1) {
	    System.out.println("USage: MissionCount <datafile>");
	    System.exit(1);
	}

	try {
	    System.out.printf("CS261 - MissionCount - Ensign Jaime Landers%n%n");

	    InputStream log = getFileInputStream(args[0]);
	    Scanner sc = new Scanner(log);
	    sc.useDelimiter(Pattern.compile(",|\n"));
	    while (sc.hasNext())
		{
            int missionCount = 1;
            SortedMap missionKey;
            String tempMember;
		    String crewMember = sc.next();
		    String mission = sc.next();
           
		    // Add code to read in the data and store it in a data structure here

            if (mMap.containsKey(mission))  // Case 1: Mission exists
            {
                nMap = mMap.get(mission);

                if (nMap.containsKey(crewMember)) // Ensign exists in mission
                {
                    missionCount = nMap.get(crewMember) + 1;
                    nMap.replace(crewMember, missionCount);
                }
                else // Ensign does not exist in mission
                {
                    nMap.put(crewMember, missionCount);
                }

                mMap.replace(mission, nMap); 

            }
            else    // Case 2: Mission does not exist
            {
                nMap = new TreeMap<String, Integer>(); 
                mMap.put(mission, nMap); 
            }
            
		} sc.close();

	    // Add code to print the report here

        for(Map.Entry<String, SortedMap<String, Integer>> missionEntry : mMap.entrySet())
        {
            String mission = missionEntry.getKey();
            System.out.println(mission + " \n:");
            nMap = mMap.get(mission);

            for (Map.Entry<String, Integer> ensignEntry : nMap.entrySet())
            {
                String ensign = ensignEntry.getKey();
                Integer missionNum = ensignEntry.getValue();
                int ensignLength = ensign.length();

                if (ensignLength < 6)
                    System.out.println("  " + ensign + "\t\t\t " + missionNum);
                else
                    System.out.println("  " + ensign + "\t\t " + missionNum);
            }
        }

	} catch (Exception e) {
	    System.out.println("Error: " + e.getMessage());
	}
    }
}
