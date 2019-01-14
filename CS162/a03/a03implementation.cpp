#include "a03.h"

using namespace std;

order_tracker::order_tracker() // Default constructor
{
	current_tab = 0;
	tab_num = 0;

	for(int i = 0; i < MAX_TAB; i++)
	{
		tab_number[i].famous_qty = 0;
		tab_number[i].kahuna_qty = 0;
		tab_number[i].royal_qty = 0;
		tab_number[i].fry_qty = 0;
		tab_number[i].shake_qty = 0;
		tab_number[i].soda_qty = 0;
		tab_number[i].tab_ttl = 0.0;
		tab_number[i].order_name = NULL;
		tab_number[i].order_name = NULL;

	} // Closes for loop
} // Closes constructor

order_tracker::~order_tracker() // Deconstuctor
{
	for(int i = 0; i < current_tab; i++)
	{
		delete[] tab_number[i].order_name;
		delete[] tab_number[i].order_note;

	} // Closes for loop
} // Closes Deconstuctor

void order_tracker::loadtab()
{
	char charEat = '\0';
	char temp_string[STRING_SIZE] = {'\0'};
	char user_selection = 0;
	double sales_total = 0.0;
	ifstream inFile; 
	int i = 0; 
	int primer = 0;
	int string_size = 0;

	cout << "What file would you like to read and write orders to?: "; 

	cin.getline(file_name, STRING_SIZE);

	inFile.open(file_name);

	inFile.peek(); // Fix for loading empty files

	while (!inFile.fail() && !inFile.eof() && i < MAX_TAB)
	{
		if (inFile.eof())
			break;

		inFile >> tab_number[i].famous_qty; 
		inFile >> charEat; // Fix for comma input
		inFile >> tab_number[i].kahuna_qty; 
		inFile >> charEat; // Fix for comma input
		inFile >> tab_number[i].royal_qty; 
		inFile >> charEat; // Fix for comma input
		inFile >> tab_number[i].fry_qty; 
		inFile >> charEat; // Fix for comma input
		inFile >> tab_number[i].shake_qty;
		inFile >> charEat; // Fix for comma input
		inFile >> tab_number[i].soda_qty; 
		inFile >> charEat; // Fix for comma input

		inFile.getline(temp_string, STRING_SIZE, ',');
		string_size = strlen(temp_string);
		tab_number[i].order_name = new char[string_size + 1];
		strncpy(tab_number[i].order_name, temp_string, string_size);
		tab_number[i].order_name[string_size] = '\0'; 
		string_size = 0;

		inFile.getline(temp_string, STRING_SIZE);
		string_size = strlen(temp_string);
		tab_number[i].order_note = new char[string_size + 1];
		strncpy(tab_number[i].order_note, temp_string, string_size);
		tab_number[i].order_note[string_size] = '\0'; 
		string_size = 0;

		inFile.peek(); // Sets eof flag, fix for extra loop 

		tab_number[i].tab_ttl = (tab_number[i].famous_qty * FAMOUS_COST) + (tab_number[i].kahuna_qty * KAHUNA_COST) + (tab_number[i].royal_qty * ROYAL_COST) + (tab_number[i].fry_qty * FRY_COST) + (tab_number[i].shake_qty * SHAKE_COST) + (tab_number[i].soda_qty * SODA_COST); 

	 	current_tab++;

		i++;
	} // Closes while loop

	inFile.close();

	cout << "\nSuccessfully loaded " << current_tab << " orders from " << file_name << ". \n" << endl;

	return;
} // Closes loadtab

void order_tracker::newtab()
{
	int user_qty = 0;
	int string_size = 0;
	char temp_string[STRING_SIZE] = {'\0'};

	if (current_tab < MAX_TAB)
	{
		cout << "Entering order #" << current_tab + 1 << endl;
		
		cout << "What is customer's name?: ";

		cin.ignore();
		cin.getline (temp_string, STRING_SIZE); 	
		string_size = strlen(temp_string);
		tab_number[current_tab].order_name = new char[string_size +1];
		strncpy(tab_number[current_tab].order_name, temp_string, string_size);
		tab_number[current_tab].order_name[string_size] = '\0'; 
		string_size = 0;

		cout << fixed << showpoint << setprecision(2); 
		cout << "Famous burgers are $" << FAMOUS_COST << " each. How many would you like?: "; 
		while (!(cin >> user_qty) || user_qty < 0)
		{
			cout << "You did not enter a valid number, try again... \n" << endl;
			cin.clear();
			cin.ignore(200, '\n');
		}  // Closes while
 		tab_number[current_tab].famous_qty = user_qty;
		user_qty = 0;

		cout << fixed << showpoint << setprecision(2); 
		cout << "Big Kahuna burgers are $" << KAHUNA_COST << " each. How many would you like?: ";
		while (!(cin >> user_qty) || user_qty < 0)
		{
			cout << "You did not enter a valid number, try again... \n" << endl;
			cin.clear();
			cin.ignore(200, '\n');
		}  // Closes while
 		tab_number[current_tab].kahuna_qty = user_qty;
		user_qty = 0;

		cout << fixed << showpoint << setprecision(2); 
		cout << "Royal burgers are $" << ROYAL_COST << " each. How many would you like?: ";
		while (!(cin >> user_qty) || user_qty < 0)
		{
			cout << "You did not enter a valid number, try again... \n" << endl;
			cin.clear();
			cin.ignore(200, '\n');
		}  // Closes while
 		tab_number[current_tab].royal_qty = user_qty;
		user_qty = 0;

		cout << fixed << showpoint << setprecision(2); 
		cout << "Fries are $" << FRY_COST << " each. How many would you like?: ";
		while (!(cin >> user_qty) || user_qty < 0)
		{
			cout << "You did not enter a valid number, try again... \n" << endl;
			cin.clear();
			cin.ignore(200, '\n');
		}  // Closes while
 		tab_number[current_tab].fry_qty = user_qty;
		user_qty = 0;

		cout << fixed << showpoint << setprecision(2); 
		cout << "Shakes are $" << SHAKE_COST << " each. How many would you like?: "; 
		while (!(cin >> user_qty) || user_qty < 0)
		{
			cout << "You did not enter a valid number, try again... \n" << endl;
			cin.clear();
			cin.ignore(200, '\n');
		}  // Closes while
 		tab_number[current_tab].shake_qty = user_qty;
		user_qty = 0;

		cout << fixed << showpoint << setprecision(2); 
		cout << "Sodas are $" << SODA_COST << " each. How many would you like?: "; 
		while (!(cin >> user_qty) || user_qty < 0)
		{
			cout << "You did not enter a valid number, try again... \n" << endl;
			cin.clear();
			cin.ignore(200, '\n');
		}  // Closes while
 		tab_number[current_tab].soda_qty = user_qty;
		user_qty = 0;

		cout << "Any special requests for the order?: ";
		cin.ignore();
		cin.getline (temp_string, STRING_SIZE); 	
		string_size = strlen(temp_string);
		tab_number[current_tab].order_note = new char[string_size +1];
		strncpy(tab_number[current_tab].order_note, temp_string, string_size);
		tab_number[current_tab].order_note[string_size] = '\0'; 
		string_size = 0;

		tab_number[current_tab].tab_ttl = (tab_number[current_tab].famous_qty * FAMOUS_COST) + (tab_number[current_tab].kahuna_qty * KAHUNA_COST) + (tab_number[current_tab].royal_qty * ROYAL_COST) + (tab_number[current_tab].fry_qty * FRY_COST) + (tab_number[current_tab].shake_qty * SHAKE_COST) + (tab_number[current_tab].soda_qty * SODA_COST); 

		cout << "\nThank you for your order ";  
		cout << tab_number[current_tab].order_name << ". \n" << endl;

		viewtab(current_tab);

		current_tab++;
		return;

	} // Closes do while

	else if (current_tab >= MAX_TAB)
	{
		cout << "You have entered the maximum amount of orders for the day, please exit the program to clear memory and start over... " << endl;

		return;
	} // Cloes else if

	return;
} // Closes newtab

void order_tracker::searchtab()
{
	int user_tab = 0;
	char search_name[STRING_SIZE];
	bool match_found = false;
	
	if (current_tab <= 0)
	{
		cout << "There are not any orders yet, enter an order before viewing...\n" << endl;
		return;
	} // Closes if

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
		} // Closesw while 
	} // Closes for

	if (match_found == true)
	{			
		match_found = false;
		cout << "\nHere is the order for " << search_name << "\n" << endl; 
		viewtab(tab_num);
	} // Closes if
	else if (match_found != true)
	{
		cout << "\nNo match for " << search_name << endl;

		return;
	} // Closes else if

	return;
} // Closes searchtab

void order_tracker::totaltab()
{
	int i = 0; 
	double sales_total = 0.0;
	char user_selection = 0;
	ofstream outFile; 

	cout << "Would you like to save todays data to " << file_name << "? (Y)es to save: " ;
	cin.ignore();
	cin.get(user_selection);

	if (user_selection == 'y' || user_selection == 'Y')
	{
	cout << "file_name = " << file_name << endl;
		outFile.open(file_name);

		for(int i = 0; i < current_tab; i++)
		{
			outFile << tab_number[i].famous_qty << "," << tab_number[i].kahuna_qty << "," << tab_number[i].royal_qty << ","; 
			outFile << tab_number[i].fry_qty << "," << tab_number[i].shake_qty << "," << tab_number[i].soda_qty << ","; 
			outFile << tab_number[i].order_name << "," << tab_number[i].order_note << endl;
		} // Closes for
	} // Closes if
	
	outFile.close();

	return;

} // Closes totaltab

void order_tracker::viewtab(int tab_num)
{
	cout << "Customer Name: " << tab_number[tab_num].order_name << endl;

	if (tab_number[tab_num].famous_qty == 1)
	{
		cout << tab_number[tab_num].famous_qty << " Famous burger at $"; 
		cout << fixed << showpoint << setprecision(2); 
		cout << FAMOUS_COST << ", charge = $" << tab_number[tab_num].famous_qty * FAMOUS_COST << endl;

	} // Closes if

	else if (tab_number[tab_num].famous_qty > 1)
	{
		cout << tab_number[tab_num].famous_qty << " Famous burgers at $"; 
		cout << fixed << showpoint << setprecision(2); 
		cout << FAMOUS_COST << ", charge = $" << tab_number[tab_num].famous_qty * FAMOUS_COST << endl;
	} // Closes if

	if (tab_number[tab_num].kahuna_qty == 1)
	{
		cout << tab_number[tab_num].kahuna_qty << " Big Kahuna burger at $"; 
		cout << fixed << showpoint << setprecision(2); 
		cout << KAHUNA_COST << ", charge = $" << tab_number[tab_num].kahuna_qty * KAHUNA_COST << endl;
	} // Closes if

   	else if (tab_number[tab_num].kahuna_qty > 1)
	{
		cout << tab_number[tab_num].kahuna_qty << " Big Kahuna burgers at $"; 
		cout << fixed << showpoint << setprecision(2); 
		cout << KAHUNA_COST << ", charge = $" << tab_number[tab_num].kahuna_qty * KAHUNA_COST << endl;
	} // Closes else if

	if (tab_number[tab_num].royal_qty == 1)
	{
		cout << tab_number[tab_num].royal_qty << " Royal burger at $"; 
		cout << fixed << showpoint << setprecision(2); 
		cout << ROYAL_COST << ", charge = $" << tab_number[tab_num].royal_qty * ROYAL_COST << endl;
	} // Closes if

	else if (tab_number[tab_num].royal_qty > 1)
	{
		cout << tab_number[tab_num].royal_qty << " Royal burgers at $"; 
		cout << fixed << showpoint << setprecision(2); 
		cout << ROYAL_COST << ", charge = $" << tab_number[tab_num].royal_qty * ROYAL_COST << endl;
	} // Closes else if

	if (tab_number[tab_num].fry_qty == 1)
	{
		cout << tab_number[tab_num].fry_qty << " fry at $"; 
		cout << fixed << showpoint << setprecision(2);
		cout << FRY_COST << ", charge = $" << tab_number[tab_num].fry_qty * FRY_COST << endl;
	} // Closes if

	else if (tab_number[tab_num].fry_qty > 1)
	{
		cout << tab_number[tab_num].fry_qty << " fries at $";
		cout << fixed << showpoint << setprecision(2);
		cout << FRY_COST << ", charge = $" << tab_number[tab_num].fry_qty * FRY_COST << endl;
	} // Closes if

	if (tab_number[tab_num].shake_qty == 1)
	{
		cout << tab_number[tab_num].shake_qty << " shake at $"; 
		cout << fixed << showpoint << setprecision(2);
	       	cout << SHAKE_COST << ", charge = $" << tab_number[tab_num].shake_qty * SHAKE_COST << endl;
	} // Closes if

	else if (tab_number[tab_num].shake_qty > 1)
	{
		cout << tab_number[tab_num].shake_qty << " shakes at $"; 
		cout << fixed << showpoint << setprecision(2); 
		cout << SHAKE_COST << ", charge = $" << tab_number[tab_num].shake_qty * SHAKE_COST << endl;
	} // Closes else if

	if (tab_number[tab_num].soda_qty == 1)
	{
		cout << tab_number[tab_num].soda_qty << " soda at $"; 
		cout << fixed << showpoint << setprecision(2); 
		cout << SODA_COST << ", charge = $" << tab_number[tab_num].soda_qty * SODA_COST << endl;
	} // Closes if

	else if (tab_number[tab_num].soda_qty > 1)
	{
		cout << tab_number[tab_num].soda_qty << " sodas at $"; 
		cout << fixed << showpoint << setprecision(2); 
		cout << SODA_COST << ", charge = $" << tab_number[tab_num].soda_qty * SODA_COST << endl;
	} // Closes else if

	cout << fixed << showpoint << setprecision(2); 
	cout << "\nTotal charge = $" << tab_number[tab_num].tab_ttl << "\n" << endl;

	cout << "Order Notes: " <<  tab_number[tab_num].order_note << endl;

	return;

} // Closes viewtab
