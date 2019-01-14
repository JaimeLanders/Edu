#include <iostream>
using namespace std;
#include "data.h"
#include "linkedstack.h"
#include "linkedqueue.h"

int main()
{
	cout << "Welcome to Real Estate Tracker 1.0 " << endl;

	char fileName[] = "data.dat";
	queue housesOnList(fileName);
	data house;
	stack houseInterested;
	char response;

	cout << "\nThe houses we will visit today:" << endl << endl;
	housesOnList.displayAll ();
	queue queue2 = housesOnList; // test
	while(housesOnList.dequeue (house))
	{
		cout << "\nnext house to be visited: " << house << endl;
		cout << "\nWould you like to revisit this house on our way back? (y, n): ";
		cin >> response;
		cin.ignore(100, '\n');
		
		if(response == 'y' || response == 'Y')
		{
			cout << "\nThe house is saved for revisiting" << endl;
			houseInterested.push (house);
		}
	}

	cout << "\nWe have finished the first round of screening" << endl << endl;
	cout << "\nOn the way back to the office: " << endl << endl;

	stack stack2 = houseInterested; // test

	while(houseInterested.pop (house))
	{
		cout << "\nnext house to be revisited: " << house << endl;
	}

	cout << "\nWe've finished the second round. ready to make an offer? (y, n):";
	cin >> response;
	cin.ignore (100, '\n');
	cout << "\nLet's talk about that in my office. " << endl << endl;

	return 0;
}
