#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main()
{
	ifstream dataFile;
	int i, inNum, reNum, sumNum = 0;

	dataFile.open("NumberFile");

	cout << "Welcome to the number program! " << endl;

	while (!dataFile.eof())	
	{
		i++;
		dataFile >> inNum;
//		cout << inNum << endl;
		reNum = inNum % 5;
//		cout << reNum << endl;
		if (reNum == 0)
		{	
//			cout << "Divisible " << endl;
			sumNum = sumNum + inNum;	
//			cout << sumNum << endl;
		}
		else if (reNum != 0) 
		{
//			cout << "Not Divisible" << endl;
			continue;
		}
	
//		cout << "=====" << endl;
	}

	sumNum = sumNum - inNum; // Temporary fix for adding last number twice.

	cout << "The sum of all numbers divisible by 5 is " << sumNum << endl;
	
//	cout << "The program ran " << i << " times. " << endl;

	dataFile.close();

	return 0;
}
