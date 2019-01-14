import java.util.ArrayList; 
import java.util.Scanner; 

public class BarChart
{
    private static ArrayList<Integer> data = new ArrayList<Integer>();

    private static void PrintRow(ArrayList dataIn, int numColIn)
    {
        int maxVal = 0;

        for (int h = 0; h < numColIn; h++)
        {
            int tempMax = (int)dataIn.get(h);

            if (maxVal < tempMax) 
                maxVal = tempMax;
        }

        for (int i = 0; i < maxVal; i++)
        {
            for (int j = 0; j < numColIn; j++)
            {
                int currVal = (int)dataIn.get(j);

                if (currVal >= maxVal - i) 
                    System.out.print("*");
                else
                    System.out.print(" ");
            }
                System.out.println("");
        }
    }

    public static void main(String[] args)
    {
        Scanner sc = new Scanner(System.in); 
        System.out.println("Welcome to BarChart ");

        boolean loop = true;
        int numCol = 0;
        int numRow = 0;

        while (loop == true)
        {
            System.out.print("Please enter number of columns (0-20): ");
            numCol = sc.nextInt();

            if (numCol < 0 || numCol > 20)
                System.out.println("  You did not enter a number between 0-20, try again. ");
            else
                loop = false;
        }

        loop = true;

        for (int i = 1; i <= numCol; i++)
        {
            while (loop == true)
            {
                System.out.print("Please enter size of column " + i + ": (0-10) ");
                numRow = sc.nextInt();

                if (numRow < 0 || numRow > 10)
                    System.out.println("  You did not enter a number between 0-10, try again. ");
                else
                    loop = false;
            }

            loop = true;
            
            data.add(numRow);
        }

        PrintRow(data, numCol);
    }
}
