import com.sun.security.auth.module.UnixSystem;

public class Lab01
{
    private static int specialSauce(String str)	{

	int val = 0;
	int i=0;
	while(i < str.length()) {
	    val = (val * i) + str.codePointAt(i);
	    i++;
	}
	return(val);
    }


    public static void main(String [] args) {

	UnixSystem us = new UnixSystem();
	String username = us.getUsername();

	System.out.println("Username: " + username);
	System.out.println("Class ID: " + specialSauce(username));
    }
}
