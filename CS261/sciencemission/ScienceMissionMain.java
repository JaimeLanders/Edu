import java.util.*;

public class ScienceMissionMain{

	public static void main(String[] args) {

        System.out.println("Welcome to Science Mission\n ");

        if (args.length != 1)
        {
		    System.out.println("You did not supply the correct number of arguments (1) ");
            System.exit(1);
        }

	    String dataFilename = args[0];
//	    System.out.println(dataFilename);
		
		Environment env = new Environment();
		ScienceMission scienceMission = new ScienceMission(dataFilename);
		
		ScienceMission.startMission(env);
	}

}
