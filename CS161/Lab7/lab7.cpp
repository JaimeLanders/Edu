#include <cctype>
#include <cstring>
#include <iostream>

using namespace std;

int main ()
{
	bool wordAlt = 0;
	char currentChar, convChar;
	char userString[30];
	int i,  len = 0;

	cout << "Enter string: " << endl; 
	cin.get(userString, 30);

	len = strlen(userString);

	do
	{
		currentChar = userString[i];

		if (currentChar == ' ')
		       wordAlt = !wordAlt;  	

		if (wordAlt == 0)
		{
			convChar = toupper(currentChar);
			cout << convChar << endl;
			userString[i] = convChar;
			i++;
		}
		
		else if (wordAlt != 0)
		{	
			convChar = tolower (currentChar);
			cout << convChar << endl;
			userString[i] = convChar;
			i++;
		}
	}
	while ( i < len );	 

	cout << userString << endl;

	return 0;

}
