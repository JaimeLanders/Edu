#include <iostream>

using namespace std;

int main()
{
	int testScore = 0;

	cout << "Enter a test score: " << endl;
	cin >> testScore;

	if (90 <= testScore && testScore <=100) 
		cout << "Your grade is an A." << endl;
	else if (80 <= testScore && testScore <90) 
		cout << "Your grade is an B." << endl;
	else if (70 <= testScore && testScore <80) 
		cout << "Your grade is an C." << endl;
	else if (60 <= testScore && testScore <70) 
		cout << "Your grade is an D." << endl;
	else if (0 <= testScore && testScore <60) 
		cout << "Your grade is an F." << endl;
	else if (0 >  testScore || testScore >  100) 
		cout << "You did not enter a valid test score..."<< endl;

	return 0;
}
