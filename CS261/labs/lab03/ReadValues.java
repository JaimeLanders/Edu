import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;
import java.util.Random;

public class ReadValues
{
    private List<Integer> mArrayList;
    private List<Integer> mLinkedList;
    private int mNumValues;

    public ReadValues() {
	mNumValues = 50000;

	// TODO: Complete this initialization. Don't forget to "import"
    mArrayList = new ArrayList<Integer>(); 
	mLinkedList = new LinkedList<Integer>(); 
    }

    private void FillList(List<Integer> list) {
	Random rand = new Random();

	for (int i=0;i<mNumValues;i++) {
	    int randNum = rand.nextInt(1000);
	    
	    // TODO: Add the random number to the list
        list.add(randNum);
	}
    }

    private void ProcessList(List<Integer> list) {

	long startTime;
	long endTime;
	long duration;

	System.out.println("Processing the list...");
	startTime = System.nanoTime();

	// TODO: write a loop to iterate through all of the elements and then replace 
	// that value with its square (x^2). Use get() to get the elements
	// and set() to set the new value.
    
   for (int i = 0; i < mNumValues; i++)
   {
       int temp = 0;
       temp = list.get(i);
       temp = temp * temp;  
       list.set(i, temp);
   }

	endTime = System.nanoTime();
	duration = endTime - startTime;
	System.out.println("This took " + duration + " nanoseconds");
	System.out.println("done.");
    }

    public void SetNumValues(int nv) {
	if (nv > 0)
	    mNumValues = nv;
    }

    public void UseArrayList() {
	
	FillList(mArrayList);
	ProcessList(mArrayList);
    }

    public void UseLinkedList() {
	
	FillList(mLinkedList);
	ProcessList(mLinkedList);
    }

    public static void main(String[] args) {

	ReadValues rv = new ReadValues();

	int[] experimentValues = {1000, 5000, 10000, 20000, 50000, 100000};

	for (int experimentValue : experimentValues) {

	    // TODO: (optional) -- if you don't like the format of this output you can change it.
	    // You don't have to change it but if it makes it more convenient for your graphing
	    // tool, that is fine.

	    System.out.println("Using " + experimentValue + " values");
	    rv.SetNumValues(experimentValue);

	    System.out.println("Using an ArrayList");
	    rv.UseArrayList();
	    System.out.println();

	    System.out.println("Using a LinkedList");
	    rv.UseLinkedList();
	    System.out.println();
	}
    }
}
