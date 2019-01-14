/*
Name:		Jaime Landers
Class:		CS161
Assignment:	1
Date:		3/28/2016
Purpose:	This is the first assignment for CS161, which is a simple program to get my feet wet in c++.
Sources:	None
*/

#include <iostream>
#include <string>

using namespace std;

int main()
{
	string myFirstName;
	string Age;
	cout << "Hello there, what is your name?" << endl;
	cin >> myFirstName;
	cout << "Hello " << myFirstName << ", nice to meet you." << endl;
	cout << "How old are you?";
	cin >> Age;
	cout << "So you are " << Age << " ?" << endl;
//	system("pause");
	return 0;
}
