#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

int main()
{
	double principle;
	double rate;
	double result;
	double term;

	cout << "Welcome to the compound interest calculator." << endl;	
	cout << "What is the principle? ";
	cin >> principle;
	cout << "What is the interest rate? ";
	cin >> rate;
	cout << "What is the term? ";
	cin >> term;

	result = principle * pow((rate + 1.0), term);

	cout << fixed << showpoint << setprecision(2);
	cout << "Future value: $" << result << endl;
return 0;
}
