#include <iostream>

int addEveryOffDigit(int number);

using namespace std;

int main ()
{
	int number; 
	int result = 0;

	cout << "Hello, please enter an integer:" << endl;
	cin >> number; 
//	cout << "number = " <<  number << endl;

	result = addEveryOffDigit(number);

	cout << "The result of adding all odd numbers in " << number << " is " << result << endl;
//	cout << number << endl;

	return 0;
}

int addEveryOffDigit(int number)
{
	int currentDig, currentNum, result = 0; 

	currentNum = number;
//	cout << "currentNum = " << currentNum << endl;

	do
	{
		currentDig = currentNum % 10;
//		cout << "currentDig = " << currentDig << endl;
		currentNum = currentNum / 10;
//		cout << "currentNum = " << currentNum << endl;
		if (currentDig % 2 != 0) 
//		{
//			cout << "Odd" << endl;
			result += currentDig;
//			cout << "result = " << result << endl;
//			cout << "=====" << endl;
//		}
//		else if (currentDig % 2 == 0)
//			cout << "Even" << endl;
//			result == currentDig;
//			cout << "result = " << result << endl;
//			currentNum = currentNum / 10;
//			cout << "currentNum = " << currentNum << endl;
//			return result;
//		cout << result << endl;
//		cout << number << endl;
	}
	while (currentNum > 0);

	return result;
}
