/*
Name:		Jaime Landers
Class:		CS161
Assignment:	Project 2
Date:		4/8/16	
Purpose:	This program calcualates the time in years and days to get to another star system in Star Trek. 	
Sources:	None
*/

#include <iostream>
#include <string>

//using namespace std;

int main()
{
	double lightDis = 0.0;
	int warpFac, lightDay, lightYear = 0;
	string starSys;

	cout << "Welcome to Voyage Time Calculator 1.0!" << endl;
	cout << "" << endl;

	cout << "Please enter the mame of the star system: " << endl;
	cin >> starSys;

	cout << "Please enter the distance in light years to: " << starSys << endl;
	cin >> lightDis;

	cout << "Please enter the Warp Factor set by the captain: " << endl;
	cin >> warpFac;

	lightYear = lightDis / (warpFac * warpFac * warpFac); 

	lightDay = (lightDis / (double) (warpFac * warpFac * warpFac) * 365) - (lightYear * 365);

	cout << "The time to travel to the " << starSys << " system is " << lightYear << " years and " << lightDay << " days. " << endl;    

	return 0;
}
