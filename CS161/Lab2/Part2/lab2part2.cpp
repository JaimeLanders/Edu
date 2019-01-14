/*
Name:		Jaime Landers
Class:		CS161
Assignment:	Lab 2 - Part 2 	
Date:		4/8/16	
Purpose:	Converts kilometers to miles.
Sources:	None
*/

#include <iostream>
#include <string>

using namespace std;

int main()
{
	double kiloIn, mileOut = 0.0;

	cout << " Welcome to Kilometer to Mile Converter 1.0!" << endl;
	cout << "" << endl;

	cout << "Please enter the distance in kilometers:" << endl;
	cin >> kiloIn;

	mileOut = kiloIn * 0.62;
	
	cout << kiloIn << " kilometers is " << mileOut << " miles." << endl;

	return 0;
}
