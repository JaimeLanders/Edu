#include <iostream>

#include "project1.h"

using namespace std;


int main ()
{
	wineryOps currentOps; 	

	currentOps.loadFile();

	char userChoice = '\0';

	cout << "Welcome to Winery Tracker 1.0! " << endl;

	while (userChoice != 'x')
	{
		cout << "\nChoose from the following menu: " << endl;

		cout << "\na) Add a new winery " << endl;
		cout << "d) Delete a winery " << endl;
		cout << "n) Display wineries by name " << endl;
		cout << "r) Display wineries by rating " << endl;
		cout << "s) Search wineries by name " << endl;
		cout << "x) Exit program and save changes " << endl; 

		cout << "\nSelection: ";
		cin >> userChoice;

		if (userChoice == 'a')
		{
			wineryInfo * n;
			n = new wineryInfo;
			cout << "n = " << n << endl;

			char tempName[STRINGSIZE] = {'\0'};
			char tempLocale[STRINGSIZE] = {'\0'};
			int nameSize = 0;
			int townSize = 0;

			cout << "What is the name of the winery?: ";
			cin.ignore(200, '\n');
			cin.getline(tempName, STRINGSIZE); 
			nameSize = strlen(tempName);
			n->wineryName = new char[nameSize + 1];
			strncpy(n->wineryName, tempName, nameSize);
			n->wineryName[nameSize] = '\0';

			cout << "Where is the winery located (city)?: ";
			cin.getline(tempLocale, STRINGSIZE);
			townSize = strlen(tempLocale);
			n->wineryLocale = new char[townSize + 1];
			strncpy(n->wineryLocale, tempLocale, townSize);
			n->wineryLocale[townSize] = '\0';

			cout << "What is the year the winery started?: ";
			cin >> n->wineryYear; 
			cin.ignore(200, '\n');

			cout << "How many acres is the winery ?: ";
			cin >> n->wineryAcres;
			cin.ignore(200, '\n');

			cout << "What is the overall success rating of the winery?: ";
			cin >> n->wineryRating;
			cin.ignore(200, '\n');

			currentOps.addWinery(n);
		}
		else if (userChoice == 'd')
		{
			cout << "Name of winery to delete: " ;
			char delName[STRINGSIZE] = {'\0'};

			cin.ignore();
			cin.getline(delName, STRINGSIZE);

			currentOps.deleteWinery(delName);
		}
		else if (userChoice == 'n')
		{
			currentOps.viewByName();
		}
		else if (userChoice == 'r')
		{
			currentOps.viewByRating();
		}
		else if (userChoice == 's')
		{
			cout << "Name of winery to search: " ;
			char searchName[STRINGSIZE] = {'\0'};

			cin.ignore();
			cin.getline(searchName, STRINGSIZE);

			currentOps.searchName(searchName);
		}
		else if (userChoice == 'x')
		{
			cout << "\nGoodbye!" << endl;

			currentOps.saveFile();
		}
		else
		{
			cout << "\nYou did not enter a valid selection, try again... " << endl;
		}

	} // Closes while loop


	return 0;
}
