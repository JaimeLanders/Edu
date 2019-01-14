#include <fstream>
#include <iostream>
#include <iomanip>
#include <iomanip>
#include "collection.h"
#include "data.h"

using namespace std;

int addVendor(collection& vendorCollection)
{
	char eventType[100] = {'\0'};
	char phoneNumber[100] = {'\0'};
	char productType[100] = {'\0'};
	char vendorName[100] = {'\0'};

	cout << "\nName of vendor: ";
	cin.ignore();
	cin.getline(vendorName, 100);
	cin.clear();

	cout << "\nVendor phone number: ";
	cin.getline(phoneNumber, 100);
	cin.clear();

	cout << "\nVendor product types: ";
	cin.getline(productType, 100);

	cout << "\nVendor event types: ";
	cin.getline(eventType, 100);

	data tempData(vendorName, phoneNumber, productType, eventType);

	vendorCollection.insert(tempData);

	return 0;

}

int displayName(collection& vendorCollection)
{
	vendorCollection.displayName();

	return 0;
}

int displayProduct(collection& vendorCollection)
{
	vendorCollection.displayProduct();

	return 0;
}

int searchName(collection& vendorCollection)
{
	char searchName[100] = {'\0'};
	data dataRtn;
	bool searchRtn = false;

	cout << "Name to search: ";
	cin.ignore();
	cin.getline(searchName, 100, '\n');

	searchRtn = vendorCollection.retrieveName(dataRtn, searchName);

	if (searchRtn == true) 
	{
		cout << "Vendor data: " << endl; 
		cout << dataRtn << endl;
	}
	else
	{
		cout << searchName << " not found... " << endl;
	}

	return 0;
}

int searchProduct(collection& vendorCollection)
{
	char searchProduct[100] = {'\0'};
	int dataItems = 10;
	data dataRtn[dataItems];

	cout << "Product to search: ";
	cin.ignore();
	cin.getline(searchProduct, 100, '\n');

	dataItems = vendorCollection.retrieveProduct(dataRtn, searchProduct, dataItems);
	if (dataItems > 0)
	{
		cout << "\nVendor Data: " << endl;

		for (int i = 0; i < dataItems; i++)  
		{

			cout << dataRtn[i] << endl;
		}
	}
	else
		cout << searchProduct << " not found... " << endl;

	return 0;
}

int removeVendor(collection& vendorCollection)
{
	char removeName[100];
	bool removeRtn = false;
	
	cout << "Vendor name to remove: ";
	cin.ignore();
	cin.getline(removeName, 100, '\n');

	removeRtn = vendorCollection.remove(removeName);

	if (removeRtn == true) 
		cout << removeName << " removed " << endl; 
	else
		cout << removeName << " not found... " << endl;

	return 0;
}

int menu(collection& vendorCollection)
{
	char userChoice = '\0';

	while (userChoice != 'x' || userChoice != 'X')
	{
		cout << "\nMain Menu: " << endl;
		cout << "A: Add Vendor " << endl;
		cout << "B: Display Vendors By Name " << endl;
		cout << "C: Display Vendors By Product " << endl;
		cout << "D: Search Vendor By Name " << endl;
		cout << "E: Search Vendor By Product" << endl;
		cout << "F: Remove Vendor " << endl;
		cout << "X: Exit " << endl;

		cout << "\nSelection: ";
		cin >> userChoice;  

		if (userChoice == 'A' || userChoice == 'a')
		{
			addVendor(vendorCollection);	
		}
		else if (userChoice == 'B' || userChoice == 'b')
		{
			displayName(vendorCollection);	
		}
		else if (userChoice == 'C' || userChoice == 'c')
		{
			displayProduct(vendorCollection);	
		}
		else if (userChoice == 'D' || userChoice == 'd')
		{
			searchName(vendorCollection);	
		}
		else if (userChoice == 'E' || userChoice == 'e')
		{
			searchProduct(vendorCollection);	
		}
		else if (userChoice == 'F' || userChoice == 'f')
		{
			removeVendor(vendorCollection);	
		}
		else if (userChoice == 'X' || userChoice == 'x')
		{
			cout << "\nGoodbye! " << endl;
			char fileName[] = "data.dat";
			vendorCollection.writeOut(fileName);
			break;
		}
		else
		{
			cout << "\nYou did not enter a valid choice, try again... " << endl;
		}

		cout << "\n===== " << endl;
	}

	return 0;
}

int main ()
{
	cout << "Welcome to project 4! " << endl;
	char fileName[] = "data.dat";

	collection vendorCollection(fileName);

	menu(vendorCollection);

	return 0;
}
