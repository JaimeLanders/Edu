#include "a04.h"

using namespace std;

int main ()
{
	order_tracker todays_orders;
	char user_choice = 0;

	cout << "Welcome to Jackrabbit Slims' Burgers and Fries! \n" << endl;

	todays_orders.loadtab(); // Loads data file for reading and writing orders to

	while (user_choice != 'q')
	{	
		cout << "What would you like to do: (d)elete a tab, (e)nter a new tab, (l)ist all tabs, (v)iew previous tab, or (q)uit?: ";
		cin >> user_choice; 
		cout << "\n";

		if (user_choice == 'd')
		{
			todays_orders.deletetab(); // Deletes an order 
		}
		else if (user_choice == 'e')
		{
			todays_orders.newtab(); // Creates a new order 
		}
		else if (user_choice == 'l')
		{
			todays_orders.listtab(); // List all orders 
		}
		else if (user_choice == 'v')
		{
			todays_orders.searchtab(); // Searches previous orders by name
		}
		else if (user_choice == 'q')
		{
			todays_orders.totaltab(); // Totals all orders and outputs to data file before exiting program
		}
		else 
		{
			cout << "You did not enter a valid selection, try again... \n" << endl;
		}

		cout << "\n========== \n" << endl;

	} // closes menu

	return 0;

} // closes main
