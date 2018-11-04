import java.io.PrintStream;
import java.util.*;

public class Menu
{
    public static void main(String[] args)
    {
        Scanner sc = new Scanner(System.in);
        int oid;
        int menuNum;

        System.out.println("Welcome to ChocAn Data Processing Software");

        // Operator Login  
        System.out.print("\nLogin to ChocAn Using Provider/Manager ID:");

        oid = sc.nextInt();
        System.out.println("Provider " + oid + " Verified...");


        // Provide menu functionns here:
        System.out.println("\nProvider Operations;");
            // Member Check-In (first verification)
            System.out.println("\t1. Member Check-In");
                // Member Check-Out (second verification)
                System.out.println("\t2. Member Check-Out");
                    // Add Service Provided
                    System.out.println("\t3. New Service Provided ");
            // List Provider Directory        
            System.out.println("\t4. Display Provider Directory ");
            // Generate Provider Directory File 
            System.out.println("\t5. Save Provider Directory ");
            // Weekly Member Report
            System.out.println("\t6. Generate Member's Report ");
            // Weekly Provider Report
            System.out.println("\t7. Generate Provider's Report ");
            // EFT Report
            System.out.println("\t8. Generate EFT Report ");

            System.out.print("\nEnter Selection: ");
            menuNum = sc.nextInt();
            
               
        // Manager menu functions:  
            // Weekly Accoounting  Report
            
        // Operator menu functions:
            // Add New Member
            // Remove Member
            // Update Member Records
            // Add New Provider
            // Remove Provider
            // Update Provider Records
    }
}
