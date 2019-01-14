/*
Name:		Jaime Landers
Class:		CS161
Assignment:	Lab 2 Part 1	
Date:		4/8/16	
Purpose:	This program calcualtes the average price of 5 stocks. 	
Sources:	None
*/

#include <iostream>
#include <string>

using namespace std;

int main()
{
	double stock1, stock2, stock3, stock4, stock5, stockTtl = 0.0;
	cout << "Welcome to Stock Analyzer 1.0!" << endl;
	cout << "" << endl;

	cout << "Please enter the price of stock 1 in dollars & cents ($12.34): " << endl;
	cout << "$";
	cin >> stock1;

	cout << "Please enter the price of stock 2 in dollars & cents ($12.34): " << endl;
	cout << "$";
	cin >> stock2;

	cout << "Please enter the price of stock 3 in dollars & cents ($12.34): " << endl;
	cout << "$";
	cin >> stock3;

	cout << "Please enter the price of stock 4 in dollars & cents ($12.34): " << endl;
	cout << "$";
	cin >> stock4;

	cout << "Please enter the price of stock 5 in dollars & cents ($12.34): " << endl;
	cout << "$";
	cin >> stock5;

	stockTtl = (stock1 + stock2 + stock3 + stock4 + stock5)/5;

	cout << "The average price of the stocks are $" << stockTtl << "." << endl;    
	return 0;
}
