#include <iostream>
//#include "a02.h"

using namespace std;

class order_tracker // Class definition inside a02.h
{
public:
	static int current_tab; // Member variable declaration, public until I fix issue
        int newtab(); // Method declaration for newtab function
	order_tracker(); // Default constructor
};

int order_tracker::current_tab = 0;

order_tracker::order_tracker()  // Default constructor definition inside implementation.cpp
{
	current_tab = 0;  // Initializes current_tab to 0
}

int order_tracker::newtab() // newtab function definition inside implementation.cpp

{
	cout << "current_tab = " << current_tab << endl;  // Test statement that is giving me undefined reference errors

	return 0;
}

int main() // Main function inside main.cpp

{
	order_tracker todays_orders;  // Declares todays_orders to be an object of class order_tracker

	todays_orders.newtab(); // Calls newtab function

	return 0;
}
