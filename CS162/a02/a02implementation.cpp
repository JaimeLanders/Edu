#include "a02.h"

using namespace std;

order_tracker::order_tracker()
{
	int current_tab = 0;
	int tab_num = 0;
}

/*order_tracker::~order_tracker() // Deconstuctor, doesn't seem to be needed
{
//	cout << "order_tracker deconstructor" << endl;
	int current_tab = 0;
//	cout << "current_tab = " << *//*order_tracker.*//*current_tab << endl;
}
*/

void order_tracker::newtab()
{
	int user_qty = 0;

	if (current_tab < MAX_TAB)
	{
		cout << "Entering order #" << current_tab + 1 << endl;
		
		cout << "What is customer's name?: ";

		cin.ignore();
		cin.getline (tab_number[current_tab].order_name, STRING_SIZE); 	

		cout << fixed << showpoint << setprecision(2); 
		cout << "Famous burgers are $" << FAMOUS_COST << " each. How many would you like?: "; 
		while (!(cin >> user_qty) || user_qty < 0)
		{
			cout << "You did not enter a valid number, try again... \n" << endl;
			cin.clear();
			cin.ignore(200, '\n');
		}
 		tab_number[current_tab].famous_qty = user_qty;
		user_qty = 0;

		cout << fixed << showpoint << setprecision(2); 
		cout << "Big Kahuna burgers are $" << KAHUNA_COST << " each. How many would you like?: "; 
		while (!(cin >> user_qty) || user_qty < 0)
		{
			cout << "You did not enter a valid number, try again... \n" << endl;
			cin.clear();
			cin.ignore(200, '\n');
		}
 		tab_number[current_tab].kahuna_qty = user_qty;
		user_qty = 0;

		cout << fixed << showpoint << setprecision(2); 
		cout << "Royal burgers are $" << ROYAL_COST << " each. How many would you like?: "; 
		while (!(cin >> user_qty) || user_qty < 0)
		{
			cout << "You did not enter a valid number, try again... \n" << endl;
			cin.clear();
			cin.ignore(200, '\n');
		}
 		tab_number[current_tab].royal_qty = user_qty;
		user_qty = 0;

		cout << fixed << showpoint << setprecision(2); 
		cout << "Fries are $" << FRY_COST << " each. How many would you like?: "; 
		while (!(cin >> user_qty) || user_qty < 0)
		{
			cout << "You did not enter a valid number, try again... \n" << endl;
			cin.clear();
			cin.ignore(200, '\n');
		}
 		tab_number[current_tab].fry_qty = user_qty;
		user_qty = 0;

		cout << fixed << showpoint << setprecision(2); 
		cout << "Shakes are $" << SHAKE_COST << " each. How many would you like?: "; 
		while (!(cin >> user_qty) || user_qty < 0)
		{
			cout << "You did not enter a valid number, try again... \n" << endl;
			cin.clear();
			cin.ignore(200, '\n');
		}
 		tab_number[current_tab].shake_qty = user_qty;
		user_qty = 0;

		cout << fixed << showpoint << setprecision(2); 
		cout << "Sodas are $" << SODA_COST << " each. How many would you like?: "; 
		while (!(cin >> user_qty) || user_qty < 0)
		{
			cout << "You did not enter a valid number, try again... \n" << endl;
			cin.clear();
			cin.ignore(200, '\n');
		}
 		tab_number[current_tab].soda_qty = user_qty;
		user_qty = 0;

		cout << "Any special requests for the order?: ";
		cin.ignore();
		cin.getline (tab_number[current_tab].order_note, STRING_SIZE); 	

		tab_number[current_tab].tab_ttl = (tab_number[current_tab].famous_qty * FAMOUS_COST) + (tab_number[current_tab].kahuna_qty * KAHUNA_COST) + (tab_number[current_tab].royal_qty * ROYAL_COST) + (tab_number[current_tab].fry_qty * FRY_COST) + (tab_number[current_tab].shake_qty * SHAKE_COST) + (tab_number[current_tab].soda_qty * SODA_COST); 

		cout << "\nThank you for your order ";  
		cout << tab_number[current_tab].order_name << ". \n" << endl;

		viewtab(current_tab);

		current_tab++;
		return;

	} // closes do while

	else if (current_tab >= MAX_TAB)
	{
		cout << "You have entered the maximum amount of orders for the day, please exit the program to clear memory and start over... " << endl;

		return;
	}

	return;
} // closes newtab

void order_tracker::searchtab()
{
	int user_tab = 0;
	char search_name[STRING_SIZE];
	bool match_found = false;
	
	if (current_tab <= 0)
	{
		cout << "There are not any orders yet, enter an order before viewing...\n" << endl;
		return;
	}

	cout << "Searching orders by name, please enter the name: ";
	cin.ignore();
	cin.getline(search_name, STRING_SIZE);

	for (int i = 0; i < current_tab; i++)
	{
		while (strcmp (search_name, tab_number[i].order_name) == 0)
		{
			match_found = true;
			tab_num = i;
			break;
		}
	}

	if (match_found == true)
	{			
		match_found == false;
		cout << "\nHere is the order for " << search_name << "\n" << endl; 
		viewtab(tab_num);
	}
	else if (match_found != true)
	{
	cout << "\nNo match for " << search_name << endl;

	return;
	}

	return;
} // closes searchtab

void order_tracker::totaltab()
{
	int i = 0; 
	double sales_total = 0.0;
	char file_name[STRING_SIZE];
	char user_selection = 0;
	ofstream outFile; 

	for (i = 0; i < current_tab; i++)
	{
		sales_total += tab_number[i].tab_ttl; 
	}

	cout << "There were " << current_tab << " total customer(s) today and $" << fixed << showpoint << setprecision(2) << sales_total << " dollars made total. \n" << endl;  

	cout << "Would you like to save todays data to a file? (Y)es to save: " ;
	cin.ignore();
	cin.get(user_selection);

	if (user_selection == 'y' || user_selection == 'Y')
	{
		cout << "Enter the name of the file to save: ";
		cin.ignore();
		cin.getline(file_name, STRING_SIZE);
		outFile.open(file_name);

		for(int i = 0; i < current_tab; i++)
		{
			outFile << tab_number[i].famous_qty << "," << tab_number[i].kahuna_qty << "," << tab_number[i].royal_qty << ","; 
			outFile << tab_number[i].fry_qty << "," << tab_number[i].shake_qty << "," << tab_number[i].soda_qty << ","; 
			outFile << tab_number[i].order_name << "," << tab_number[i].order_note << endl;
		}
	}
	
	return;

} // closes totaltab

void order_tracker::viewtab(int tab_num)
{
	cout << "Customer Name: " << tab_number[tab_num].order_name << endl;

	if (tab_number[tab_num].famous_qty == 1)
	{
		cout << tab_number[tab_num].famous_qty << " Famous burger at $"; 
		cout << fixed << showpoint << setprecision(2); 
		cout << FAMOUS_COST << ", charge = $" << tab_number[tab_num].famous_qty * FAMOUS_COST << endl;

	}

	else if (tab_number[tab_num].famous_qty > 1)
	{
		cout << tab_number[tab_num].famous_qty << " Famous burgers at $"; 
		cout << fixed << showpoint << setprecision(2); 
		cout << FAMOUS_COST << ", charge = $" << tab_number[tab_num].famous_qty * FAMOUS_COST << endl;
	}

	if (tab_number[tab_num].kahuna_qty == 1)
	{
		cout << tab_number[tab_num].kahuna_qty << " Big Kahuna burger at $"; 
		cout << fixed << showpoint << setprecision(2); 
		cout << KAHUNA_COST << ", charge = $" << tab_number[tab_num].kahuna_qty * KAHUNA_COST << endl;
	}

   	else if (tab_number[tab_num].kahuna_qty > 1)
	{
		cout << tab_number[tab_num].kahuna_qty << " Big Kahuna burgers at $"; 
		cout << fixed << showpoint << setprecision(2); 
		cout << KAHUNA_COST << ", charge = $" << tab_number[tab_num].kahuna_qty * KAHUNA_COST << endl;
	}

	if (tab_number[tab_num].royal_qty == 1)
	{
		cout << tab_number[tab_num].royal_qty << " Royal burger at $"; 
		cout << fixed << showpoint << setprecision(2); 
		cout << ROYAL_COST << ", charge = $" << tab_number[tab_num].royal_qty * ROYAL_COST << endl;
	}

	else if (tab_number[tab_num].royal_qty > 1)
	{
		cout << tab_number[tab_num].royal_qty << " Royal burgers at $"; 
		cout << fixed << showpoint << setprecision(2); 
		cout << ROYAL_COST << ", charge = $" << tab_number[tab_num].royal_qty * ROYAL_COST << endl;
	}

	if (tab_number[tab_num].fry_qty == 1)
	{
		cout << tab_number[tab_num].fry_qty << " fry at $"; 
		cout << fixed << showpoint << setprecision(2);
		cout << FRY_COST << ", charge = $" << tab_number[tab_num].fry_qty * FRY_COST << endl;
	}

	else if (tab_number[tab_num].fry_qty > 1)
	{
		cout << tab_number[tab_num].fry_qty << " fries at $";
		cout << fixed << showpoint << setprecision(2);
		cout << FRY_COST << ", charge = $" << tab_number[tab_num].fry_qty * FRY_COST << endl;
	}

	if (tab_number[tab_num].shake_qty == 1)
	{
		cout << tab_number[tab_num].shake_qty << " shake at $"; 
		cout << fixed << showpoint << setprecision(2);
	       	cout << SHAKE_COST << ", charge = $" << tab_number[tab_num].shake_qty * SHAKE_COST << endl;
	}

	else if (tab_number[tab_num].shake_qty > 1)
	{
		cout << tab_number[tab_num].shake_qty << " shakes at $"; 
		cout << fixed << showpoint << setprecision(2); 
		cout << SHAKE_COST << ", charge = $" << tab_number[tab_num].shake_qty * SHAKE_COST << endl;
	}

	if (tab_number[tab_num].soda_qty == 1)
	{
		cout << tab_number[tab_num].soda_qty << " soda at $"; 
		cout << fixed << showpoint << setprecision(2); 
		cout << SODA_COST << ", charge = $" << tab_number[tab_num].soda_qty * SODA_COST << endl;
	}

	else if (tab_number[tab_num].soda_qty > 1)
	{
		cout << tab_number[tab_num].soda_qty << " sodas at $"; 
		cout << fixed << showpoint << setprecision(2); 
		cout << SODA_COST << ", charge = $" << tab_number[tab_num].soda_qty * SODA_COST << endl;
	}

	cout << fixed << showpoint << setprecision(2); 
	cout << "\nTotal charge = $" << tab_number[tab_num].tab_ttl << "\n" << endl;

	cout << "Order Notes: " <<  tab_number[tab_num].order_note << endl;

	return;

} // closes viewtab
