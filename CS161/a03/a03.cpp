/*
Name:		Jaime Landers
Class:		CS161
Assignment:	Project 3 
Date:		4/23/16	
Purpose:	This program calcualates the time in days to get to another star system in Star Trek using an import file, and then exports results to a text file. 	
Sources:	None
*/

#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

int main()
{
	double lightDis1, lightDis2, lightDis3 = 0.0;
	ifstream dataFile;
	int colWidth = 15; 
	int sys1LightDay4, sys1LightDay5, sys1LightDay6 = 0;
	int sys2LightDay4, sys2LightDay5, sys2LightDay6 = 0;
	int sys3LightDay4, sys3LightDay5, sys3LightDay6 = 0;
	ofstream outFile;
	string starSys1, starSys2, starSys3;

	cout << "Welcome to the Voyage Time Caluclator 1.0 " << endl << endl;
	cout << "Importing Star System data for analyzing... " << endl << endl;

	dataFile.open("systemDistances");
	outFile.open("systemTimes");

	dataFile >> starSys1 >> lightDis1;
	dataFile >> starSys2 >> lightDis2;
	dataFile >> starSys3 >> lightDis3;

	sys1LightDay4 = (lightDis1 / (double) 64 * 365);
	sys1LightDay5 = (lightDis1 / (double) 125 * 365);
	sys1LightDay6 = (lightDis1 / (double) 216 * 365);

	sys2LightDay4 = (lightDis2 / (double) 64 * 365);
	sys2LightDay5 = (lightDis2 / (double) 125 * 365);
	sys2LightDay6 = (lightDis2 / (double) 216 * 365);

	sys3LightDay4 = (lightDis3 / (double) 64 * 365);
	sys3LightDay5 = (lightDis3 / (double) 125 * 365);
	sys3LightDay6 = (lightDis3 / (double) 216 * 365);

	cout << fixed << showpoint << setprecision(2);

	cout << setw (colWidth) << left << "Destination"; 
	cout << setw (colWidth) << right << "Distance"; 
	cout << setw (colWidth) << right << "Warp 4 Time"; 
	cout << setw (colWidth) << right << "Warp 5 Time"; 
	cout << setw (colWidth) << right << "Warp 6 Time" << endl;    

	cout << setw (colWidth) << left << starSys1;
       	cout << fixed << showpoint << setprecision(2) << setw (colWidth) << right << lightDis1;
	cout << setw (colWidth) << right << sys1LightDay4;    
	cout << setw (colWidth) << right << sys1LightDay5;    
	cout << setw (colWidth) << right << sys1LightDay6 <<endl;    

	cout << setw (colWidth) << left << starSys2;
       	cout << fixed << showpoint << setprecision(2) << setw (colWidth) << right << lightDis2;
	cout << setw (colWidth) << right << sys2LightDay4;    
	cout << setw (colWidth) << right << sys2LightDay5;    
	cout << setw (colWidth) << right << sys2LightDay6 << endl;    

	cout << setw (colWidth) << left << starSys3;
       	cout << fixed << showpoint << setprecision(2) << setw (colWidth) << right << lightDis3;
	cout << setw (colWidth) << right << sys3LightDay4;    
	cout << setw (colWidth) << right << sys3LightDay5;    
	cout << setw (colWidth) << right << sys3LightDay6 << endl;    
	
	outFile << setw (colWidth) << left << "Destination"; 
	outFile << setw (colWidth) << right << "Distance"; 
	outFile << setw (colWidth) << right << "Warp 4 Time"; 
	outFile << setw (colWidth) << right << "Warp 5 Time"; 
	outFile << setw (colWidth) << right << "Warp 6 Time" << endl;    

	outFile << setw (colWidth) << left << starSys1;
       	outFile << fixed << showpoint << setprecision(2) << setw (colWidth) << right << lightDis1;
	outFile << setw (colWidth) << right << sys1LightDay4;    
	outFile << setw (colWidth) << right << sys1LightDay5;    
	outFile << setw (colWidth) << right << sys1LightDay6 <<endl;    

	outFile << setw (colWidth) << left << starSys2;
       	outFile << fixed << showpoint << setprecision(2) << setw (colWidth) << right << lightDis2;
	outFile << setw (colWidth) << right << sys2LightDay4;    
	outFile << setw (colWidth) << right << sys2LightDay5;    
	outFile << setw (colWidth) << right << sys2LightDay6 << endl;    

	outFile << setw (colWidth) << left << starSys3;
       	outFile << fixed << showpoint << setprecision(2) << setw (colWidth) << right << lightDis3;
	outFile << setw (colWidth) << right << sys3LightDay4;    
	outFile << setw (colWidth) << right << sys3LightDay5;    
	outFile << setw (colWidth) << right << sys3LightDay6 << endl;    

	dataFile.close();
	outFile.close();

	return 0;
}
