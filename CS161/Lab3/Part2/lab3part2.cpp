#include <cmath>
#include <fstream> 
#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

int main()
{
	double test1, test2, test3, test4, test5, avgScore = 0.0;
	ifstream dataFile;
	ofstream outFile;

	cout << "Welcome to Average Test Score 1.0" << endl << endl;

	dataFile.open("lab3scoredata");
	outFile.open("lab3avgoutput");
	dataFile >> test1 >> test2 >> test3 >> test4 >> test5;

	avgScore = (test1 + test2 + test3 + test4 + test5) / 5;


	cout << "The average of the scores is " << avgScore << " percent. " << endl;

	outFile << "The average of the scores is " << avgScore << " percent. " << endl;
	dataFile.close();
	outFile.close();

	return 0;	
}
