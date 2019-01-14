#include <iostream>

using namespace std;

bool isPrime = 1 ;
int main ()

{
	int i, reNum, userNum = 0;

	cout << "Please enter a positive integer: " << endl;
	cin >> userNum;
		
	for (i = 2; i < userNum; i++)
	{		
		reNum = userNum % i;
		if (reNum == 0)
		{	
			isPrime = 0;
			break;
		}
		else if (reNum != 0 || isPrime != 0)
		{	
			isPrime = 1;
			continue;
		}
	}

	if (userNum <= 0)
		cout << "You did not enter a positive integer... " << endl; 
	else if (isPrime == 0)
		cout << userNum << " is not a prime number. " << endl;	
	else if (isPrime != 0 || (userNum <= 2 && userNum > 0)) 
		cout << userNum << " is a prime number. " << endl;

	return 0;
}
