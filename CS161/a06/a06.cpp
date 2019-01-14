#include <cstring>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

const int CITTOL = 10;
const int CHARLEN = 30;

struct citizenInfo 
	{
		char civName[CHARLEN];
		char starSys[CHARLEN];
		char solDis [CHARLEN];
//		double solDis;
	};

int addData(citizenInfo *, int, int&);
void displayData(citizenInfo *, int, int&);
int loadData(citizenInfo *, int, int&);
void saveData(citizenInfo *, int, int&);
void searchData(citizenInfo *, int, int&);

int main ()
{
	int citTtl, i = 0;
	char userIn;
	char civName[CHARLEN], starSys[CHARLEN];
	char solDis [CHARLEN];
	
	citizenInfo citizenNum[CITTOL];

//	ifstream inFile;
//	ofstream outFile;

//	inFile.open("CitizenData");
//	outFile.open("CitizenData");

	cout << "Hello, welcome to Star Trek Citizen Database 1.0" << endl;
	cout << "\nImporting and analyzing data...\n" << endl;

	citTtl = loadData(citizenNum,/* inFile, */i, citTtl);
	cout << "citTtl = " << citTtl << endl;	

	do
	{
/*
		cout << citizenNum[i].civName << endl;
		cout << citizenNum[i].starSys << endl;
		cout << citizenNum[i].solDis << endl;
*/
		cout << "What would you like to do? " << endl;
		cout << "1: Display data " << endl;
		cout << "2: Search data " << endl;
		cout << "3: Add data " << endl;
		cout << "9: Exit saving changes " << endl;
		cout << "0: Exit discarding changes " << endl;
		
		cin >> userIn;
		
		if (userIn == '1')	
		{
			displayData(citizenNum, i, citTtl);
			cout << "citTtl = " << citTtl << endl;
		} // closes if loop

		else if (userIn == '2')	
		{
			searchData(citizenNum, i, citTtl);
		} // closes if loop
		else if (userIn == '3')	
		{
			citTtl = addData(citizenNum, i, citTtl);
			cout << "addData returned" << endl;
			cout << "citTtl = " << citTtl << endl;
		}
		else if (userIn == '9')
		{
			saveData(citizenNum, i, citTtl);
			cout << "saveData returned" << endl;
			cout << "Data saved, goodbye! " << endl;
			return 0;
		}

		else if (userIn == '0')	
		{
			cout << "Goodbye! " << endl;
			return 0;
		}
		else
			cout << "You did not enter a valid choice, try again... " << endl;

	} // Closes do while loop
	while ( userIn != '0');

//	inFile.close();
//	outFile.close();

	return 0;

}
int addData(citizenInfo *citizenNum, int i, int& citTtl)
{
	cout << "citTtl = " << citTtl  << endl;
	i = citTtl;
	cout << "i = " << i << endl;

	cout << "addData working" << endl;
	cout << "Adding citizen data... " << endl;

	cout << "Civilization Name: " ;
	cin.getline (citizenNum[i].civName, CHARLEN);
	cin.getline (citizenNum[i].civName, CHARLEN);

	cout << "Star System: " ;
	cin.getline (citizenNum[i].starSys, CHARLEN);

	cout << "Distance from Sol: " ;
	cin.getline (citizenNum[i].solDis, CHARLEN);

	cout << citizenNum[i].civName << endl;
	cout << citizenNum[i].starSys << endl;  
	cout << citizenNum[i].solDis << endl;
	
	citTtl++;
	cout << "citTtl = " << citTtl << endl;	

	return citTtl;
}

void displayData(citizenInfo *citizenNum, int i, int& citTtl)
{
	cout << "displayData working " << endl;

	while (i < citTtl )
	{
		cout << citizenNum[i].civName << endl;
		cout << citizenNum[i].starSys << endl;
		cout << citizenNum[i].solDis << endl;
		i++;
	} // Closed while loop 
	return;
}

int loadData(citizenInfo *citizenNum, int i, int& citTtl)
{
	cout << "loadData working" << endl;
	cout << "i = " << i << endl;
	ifstream inFile;
	inFile.open("CitizenData");
	while (!inFile.eof() && i < CITTOL)
	{
		inFile.getline (citizenNum[i].civName, CHARLEN);
		inFile.getline (citizenNum[i].starSys, CHARLEN);
		inFile.getline (citizenNum[i].solDis, CHARLEN);
/*
		cout << citizenNum[i].civName << endl;
		cout << citizenNum[i].starSys << endl;
		cout << citizenNum[i].solDis << endl;
*/
		i++;
	cout << "i = " << i << endl;
	} // Closed while loop 
	i--;
	citTtl = i;
	inFile.close();
	return citTtl;
}

void saveData(citizenInfo *citizenNum, int i, int& citTtl)
{
 	cout << "saveData working" << endl;
	ofstream outFile;
	outFile.open("CitizenData");
	while (i < citTtl)
	{
		outFile << citizenNum[i].civName << endl;
		outFile << citizenNum[i].starSys << endl;  
		outFile << citizenNum[i].solDis << endl;
		i++;
	}
	outFile.close();
	return;
}

void searchData(citizenInfo *citizenNum, int i, int& citTtl)
{
	bool nameFound;
	char userCivName[CHARLEN];
	int nameLen = 0, userNameLen = 0;
	cout << "searchData working" << endl;
	cout << "Enter Civilization to Search: " << endl;
	cin.getline (userCivName, CHARLEN);
	cin.getline (userCivName, CHARLEN);
	cout << "userCivName = " << userCivName << endl;
	while (i < citTtl)
	{
		cout << "civName1 = " << citizenNum[i].civName << endl;
		nameLen = strlen(citizenNum[i].civName);
		cout << "nameLen  " << nameLen << endl;
		userNameLen = strlen(userCivName);
		cout << "userNameLen = " << userNameLen << endl;
		if (strcmp (citizenNum[i].civName, userCivName) == 0) 
		{	
			cout << userCivName << " found" << endl;
			nameFound = true;
			cout << "Here is data on " << userCivName << ":" << endl;
			cout << citizenNum[i].civName << endl;
			cout << citizenNum[i].starSys << endl;
			cout << citizenNum[i].solDis << endl;
			break;
		}
		else if (strcmp (citizenNum[i].civName, userCivName) != 0)
		{
			cout << "No Match..." << endl;
			nameFound = false;
		}
		i++;
//		cout << "civName2 = " << citizenNum[i].civName << endl;
	} // Closed while loop 
	return;
}


