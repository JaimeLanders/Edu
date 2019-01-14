/*
Name: 		Jaime Landers
Class:		CS260
Assignment:	Project1
Purpose:	Keep track of winery information and sort by rating.
Date Started: 	10/2/16
Sources: 	None

TODO:

1. Setup menu X
2. Setup winery class X
3. Setup doubly linked list X
4. Operations X
	a. Add winery X
	b. Remove winery X
	c. Display sorted list of wineries by rating X
	d. Display sorted list of winderies by name X
	e. Search for winery by name X
5. Constructors X
6. Deconstructor X
7. Overload for deep copy X
8. Save/load data from file X
9. Format Output X
10. Errors/memory leaks X
11. Extras
	a. data input checking

*/

#ifndef project1_h
#define project_h

#include <cstring>
#include <fstream>
#include <iostream>
#include <iomanip>

using namespace std;

const int STRINGSIZE = 100;
const char FILENAME[] = "data.dat";

struct wineryInfo
{
	int wineryYear;
	int wineryAcres;
	int wineryRating;
	char * wineryLocale;
	char * wineryName;
       	wineryInfo * nextName;
	wineryInfo * nextRating;
	wineryInfo(); // Default constuctor
	wineryInfo(const wineryInfo& source); // Copy constuctor
	wineryInfo& operator=(const wineryInfo& source);
};

class wineryOps
{
private:
	wineryInfo * nameHead = NULL; // Temp fix for constructor
	wineryInfo * rateHead = NULL; // Temp fix for constructor
public:
	void addWinery(wineryInfo * n);
	void deleteWinery(char delName[STRINGSIZE]);
	void loadFile();
	void saveFile();
	void searchName(char searchName[STRINGSIZE]);
	void viewByName();
	void viewByRating();
	wineryOps(); // Default constructor
	wineryOps(const wineryOps& source); // Default constructor
	~wineryOps();
	wineryOps& operator=(const wineryOps& source);
};

#endif
