#include "a02.h"

using namespace std;

int main ()
{
	order_tracker todays_orders;
	char user_choice = 0;

	cout << "Welcome to Jackrabbit Slims' Burgers and Fries! \n" << endl;
	
	while (user_choice != 'q')
	{	
		cout << "What would you like to do: (e)nter a new tab, (v)iew previous tab, or (q)uit?: ";
		cin >> user_choice; 
		cout << "\n";

		if (user_choice == 'e')
		{
			todays_orders.newtab();
		}
		else if (user_choice == 'v')
		{
			todays_orders.searchtab();
		}
		else if (user_choice == 'q')
		{
			todays_orders.totaltab();
		}
		else 
		{
			cout << "You did not enter a valid selection, try again... \n" << endl;
		}

		cout << "\n========== \n" << endl;

	} // closes menu

	return 0;

} // closes main
