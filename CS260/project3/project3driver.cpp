#include <cstring>
#include <iomanip>
#include <iostream>
#include "data.h"
#include "hashTable.h"

using namespace std;

int insert (hashTable& hashIn);
int menu (hashTable& hashIn);
int modify (hashTable& hashIn);
int remove (hashTable& hashIn);
int retrieve (hashTable& hashIn);

int insert (hashTable& stockHash)
{
	data n;

	char newDate [100] = {'\0'};
	char newName [100] = {'\0'};
	char newTicker [100] = {'\0'};
	float newReturn = 0.0;
	float newValue = 0.0;

	cout << "\nEntering new stock " << endl;

	cout << "\nTicker: ";
	cin.ignore();
	cin.getline(newTicker, 100, '\n');
	cin.clear();
	n.setTicker(newTicker);

	cout << "\nStock Name: ";
	cin.getline(newName, 100, '\n');
	cin.clear();
	n.setName(newName);

	cout << "\nValue of asset: ";
	cin >> newValue;
	n.setValue(newValue);
	cin.clear();

	cout << "\nDate of Value: ";
	cin.ignore();
	cin.getline(newDate, 100, '\n');
	cin.clear();
	n.setDate(newDate);

	cout << "\nYear to date return: ";
	cin >> newReturn;
	n.setReturn(newReturn);

	stockHash.insert(n);
}

int main ()
{
	char fileName[] = "data.dat";

	hashTable stockHash(fileName);

	cout << "\nWelcome to stock tracker 1.0 " << endl;
	menu(stockHash);

	return 0;
}

int menu (hashTable& stockHash)
{
	char userChoice = '\0';

	while (userChoice != 'X' || userChoice != 'x')
	{
		cout << "\nChoose from the following options: " << endl;
		cout << "A) Insert " << endl;
		cout << "B) Remove " << endl;
		cout << "C) Modify " << endl;
		cout << "D) Retrieve " << endl;
		cout << "E) Display " << endl;
		cout << "F) Monitor " << endl;
		cout << "X) Exit " << endl;
		cout <<  "\nSelection: "; 
		cin >> userChoice;
		cout << "\n";

		if (userChoice == 'A' || userChoice == 'a') 
		{
			insert(stockHash);
			userChoice = '\0';
		}
		else if (userChoice == 'B' || userChoice == 'b') 
		{
			remove(stockHash);
			userChoice = '\0';
		}
		else if (userChoice == 'C' || userChoice == 'c') 
		{
			modify(stockHash);
			userChoice = '\0';
		}
		else if (userChoice == 'D' || userChoice == 'd') 
		{
			retrieve(stockHash);
			userChoice = '\0';
		}
		else if (userChoice == 'E' || userChoice == 'e') 
		{
			stockHash.display();
			userChoice = '\0';
		}
		else if (userChoice == 'F' || userChoice == 'f') 
		{
			stockHash.monitor();
			userChoice = '\0';
		}
		else if (userChoice == 'X' || userChoice == 'x') 
		{
			cout << "Goodbye! " << endl;
			char filename [100] = "data.dat";

			stockHash.writeOut(filename);

			break;
		}
		else
		{
			cout << "You did not enter a valid choice, try again... " << endl; 
		}

		cout << "\n=====" << endl;
	}

	return 0;
}

int modify (hashTable& stockHash)
{
	char ticker[100] = {'\0'}; 
	char newDate[100] = {'\0'};
	float newValue = 0.0;
	float newReturn = 0.0;

	cout << "What ticker would you like to modify?: ";
	cin.ignore();
	cin.getline(ticker, 100, '\n');

	cout << "What is the new asset value?: ";
	cin >> newValue;

	cout << "What is the new date?: ";
	cin.ignore();
	cin.getline(newDate, 100, '\n');

	cout << "What is the new year to date return?: ";
	cin >> newReturn;

	stockHash.modify(ticker,newValue,newDate,newReturn);

	return 0;
}

int remove (hashTable& stockHash) 
{
	char ticker[100] = {'\0'}; 

	cout << "What ticker would you like to remove?: ";
	cin.ignore();
	cin.getline(ticker, 100, '\n');

	stockHash.remove(ticker);

	return 0;
}


int retrieve (hashTable& stockHash)
{
	char ticker[100] = {'\0'}; 
	data currData; 

	cout << "What ticker would you like to retrieve?: ";
	cin.ignore();
	cin.getline(ticker, 100,'\n');

	cout << "\n" << ticker << " information: " << endl;
	cout << "\n======================================================================= " << endl;
	cout << "Ticker: \t" << "Name: \t\t\t" << "Value: \t" << "Date: \t\t" << "Return: \t" << endl;
	cout << "======================================================================= " << endl;

	stockHash.retrieve(ticker, currData);

	cout << currData << endl;

	return 0;
}
