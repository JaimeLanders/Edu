#include <iostream>
#include <iomanip>

using namespace std;

int main()
{
	char ascVal = 'A' ;
	int usrNum = 0, ascCapOff = 55, ascLowOff = 61;

	cout << "Enter a number from 1-61" << endl;
	cin >> usrNum; 

	if (1 <= usrNum && usrNum <= 9)
		cout << "The number value is " << usrNum << endl; 
	else if (10 <= usrNum && usrNum <= 35)
	{
		ascVal = (static_cast<char>(usrNum) + ascCapOff);
		cout <<  "The ascii value is " << ascVal << endl;
	}
	else if (35 < usrNum && usrNum <= 61)
	{
		ascVal = (static_cast<char>(usrNum) + ascLowOff);
		cout <<  "The ascii value is " << ascVal << endl;
	}	
	else if (0 >=  usrNum ||  usrNum > 61)
	       cout << "You did not enter an integer from 1-61..." << endl;	

	return 0;
}
