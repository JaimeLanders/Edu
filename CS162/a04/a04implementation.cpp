#include "a04.h"

using namespace std;

order_info::order_info() // Default Constructor
{
	famous_qty = 0;
	kahuna_qty = 0;
	royal_qty = 0;
	fry_qty = 0;
	shake_qty = 0;
	soda_qty = 0;
	tab_ttl = 0;
	order_name = NULL;
	order_note = NULL;
	next = NULL;
	prev = NULL;
}

order_tracker::order_tracker() // Default constructor
{
	file_name[STRING_SIZE] = '\0'; // Fix for valgrind errors  
       	order_num = 0;
       	tab_num = NULL;
       	head = NULL;
       	tail = NULL;
}

order_tracker::~order_tracker() // Deconstuctor
{
       	tab_num = tail;

     	order_info *temp = NULL;

       	for (int i = 0; tab_num != NULL && i < MAX_TAB; i++)
	{
		delete[] tab_num->order_name;
		delete[] tab_num->order_note;

		temp = tab_num;

		tab_num = tab_num->prev;

		delete temp; 
		temp = NULL;
	} // Closes for loop

} // Closes deconstructor

void order_tracker::deletetab()
{
	int string_size = 0;
	bool match_found = false; 
	char search_name[STRING_SIZE] = {'\0'};
	tab_num = head;

	order_info *temp; 
	temp = NULL;

	cout << "Please enter the name to delete: ";
	cin.ignore();
	cin.getline(search_name, STRING_SIZE);

	for (int i = 0; i < order_num && tab_num != NULL; i++) 
	{
		if (strcmp (search_name, tab_num->order_name) == 0)
		{
			match_found = true;
			break;
		}
		else
			tab_num = tab_num->next;
	} // closes for

	if (match_found == true)
	{
		if (tab_num == head) // First
		{
			temp = tab_num;
			head = tab_num->next;
			delete[] temp->order_name;
			delete[] temp->order_note;
			delete temp;
			temp = NULL;
		} // closes else if
		else if (tab_num == tail) // Last
		{
			temp = tab_num;
			tab_num = tab_num->prev;
			tab_num->next = NULL;
			tab_num = tail;
			tail = tab_num->prev;
			delete[] temp->order_name;
			delete[] temp->order_note;
			delete temp;
			temp = NULL;
		} // Closes else if
		else // Middle
		{
			temp = tab_num;
			tab_num = tab_num->prev;
			tab_num->next = tab_num->next->next;
			tab_num = tab_num->next;
			tab_num->prev = tab_num->prev->prev;			
			delete[] temp->order_name;
			delete[] temp->order_note;
			delete temp;
			temp = NULL;
		} // CLoses else
		
		cout << '\n' << search_name << " deleted..." << endl;

		order_num--;

	} // Closes if
	else
		cout << '\n' << search_name << " not found..." << endl;

	return;

} // Closes deletetab

void order_tracker::listtab()
{
	tab_num = head;
	
	cout << "Listing all orders entered so far: " << endl;
	cout << "\n=====\n" << endl;

	for (int i = 0; i < order_num && tab_num != NULL; i++)
	{

		cout << "Order #" << i + 1 << ":" << endl;
		viewtab();
		cout << "\n=====\n" << endl;
		tab_num = tab_num->next;
	}

	return;
}

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

	order_info *n = NULL; // Declares pointers of type order_info	

	cout << "What file would you like to read and write orders to?: "; 
	cin.getline(file_name, STRING_SIZE);

	inFile.open(file_name);
	inFile.peek(); // Fix for loading empty files

	while (!inFile.fail() && !inFile.eof() && i < MAX_TAB)
	{
		n = new order_info; // Creates new order_info 

		inFile >> n->famous_qty; 
		inFile >> charEat; // Fix for comma input
		inFile >> n->kahuna_qty; 
		inFile >> charEat; // Fix for comma input
		inFile >> n->royal_qty; 
		inFile >> charEat; // Fix for comma input
		inFile >> n->fry_qty; 
		inFile >> charEat; // Fix for comma input
		inFile >> n->shake_qty;
		inFile >> charEat; // Fix for comma input
		inFile >> n->soda_qty; 
		inFile >> charEat; // Fix for comma input

		inFile.getline(temp_string, STRING_SIZE, ',');
		string_size = strlen(temp_string);
		n->order_name = new char[string_size + 1];
		strncpy(n->order_name, temp_string, string_size);
		n->order_name[string_size] = '\0'; 
		string_size = 0;

		inFile.getline(temp_string, STRING_SIZE);
		string_size = strlen(temp_string);
		n->order_note = new char[string_size + 1];
		strncpy(n->order_note, temp_string, string_size);
		n->order_note[string_size] = '\0'; 
		string_size = 0;

		inFile.peek(); // Sets eof flag, fix for extra loop 

		n->tab_ttl = (n->famous_qty * FAMOUS_COST) + (n->kahuna_qty * KAHUNA_COST) + (n->royal_qty * ROYAL_COST) + (n->fry_qty * FRY_COST) + (n->shake_qty * SHAKE_COST) + (n->soda_qty * SODA_COST); 

//		**Sort Algorthim**
		if (head == NULL) // List hasn't been created yet 
		{
			head = n; // Initializes head to new pointer if not already initialized
			tail = n; // Initializes tail to new pointer if not already initialized
			n->prev = NULL;
			n->next = NULL;
		}
		else if (strcmp (n->order_name,head->order_name) < 0) // Insert n at beginning of list 	
		{
			tab_num = head;
			head = n;
			n->prev= NULL;
			n->next = tab_num;
			tab_num->prev = n;
		} // Closes if
		else  // Insert somewhere in list after head
		{
			tab_num = head;

			while (tab_num != NULL)
			{

				if ((strcmp (n->order_name,tab_num->order_name) < 0))
				{
					n->prev = tab_num->prev; 
					n->next = tab_num; 
					tab_num = tab_num->prev;
					tab_num->next = n;
					tab_num = n->next;
					tab_num->prev = n;
					break;
				} // Closes else
				else if (tab_num->next == NULL) // Insert at end of list
				{
					tab_num->next = n;
					n->prev = tab_num;
					n->next = NULL;				
					tail = n;
					break;
				} // Closes if
				else
				{
					tab_num = tab_num->next; 	
				} // Closes else
			} // Closes while	
		} // Closes else and sort by name algorithm

	 	order_num++;

		i++;

	} // Closes while loop

	inFile.close();

	cout << "\nSuccessfully loaded " << order_num  << " orders from " << file_name << ". \n" << endl;

	return;
} // Closes loadtab

void order_tracker::newtab()
{
	int user_qty = 0;
	int string_size = 0;
	char temp_string[] = {'\0'};

	order_info *n, *curNum, *nextNum; // Declares pointers of type order_info	
	n = new order_info; // Creates new order_info 
	curNum = NULL;
	nextNum =NULL;
	n->next = NULL;

	while (order_num < MAX_TAB)
	{
		cout << "Entering order #" << order_num + 1 << endl;
		
		cout << "What is customer's name?: ";

		cin.ignore();
		cin.getline (temp_string, STRING_SIZE); 	
		string_size = strlen(temp_string);

		n->order_name = new char[string_size + 1];
		strncpy(n->order_name, temp_string, string_size);
		n->order_name[string_size] = '\0'; 
		string_size = 0;

//		**Sort Algorthim**
		if (head == NULL) // List hasn't been created yet 
		{
			head = n; // Initializes head to new pointer if not already initialized
			tail = n; // Initializes tail to new pointer if not already initialized
			n->prev = NULL;
			n->next = NULL;
		}
		else if (strcmp (n->order_name,head->order_name) < 0) // Insert n at beginning of list 	
		{
			tab_num = head;
			head = n;
			n->prev= NULL;
			n->next = tab_num;
			tab_num->prev = n;
		} // Closes if
		else  // Insert somewhere in list after head
		{
			tab_num = head;

			while (tab_num != NULL)
			{

				if ((strcmp (n->order_name,tab_num->order_name) < 0))
				{
					n->prev = tab_num->prev; 
					n->next = tab_num; 
					tab_num = tab_num->prev;
					tab_num->next = n;
					tab_num = n->next;
					tab_num->prev = n;
					break;
				} // Closes else
				else if (tab_num->next == NULL) // Insert at end of list
				{
					tab_num->next = n;
					n->prev = tab_num;
					n->next = NULL;				
					tail = n;
					break;
				} // Closes if
				else
				{
					tab_num = tab_num->next; 	
				} // Closes else
			} // Closes while	
		} // Closes else and sort by name algorithm

		cout << fixed << showpoint << setprecision(2); 
		cout << "Famous burgers are $" << FAMOUS_COST << " each. How many would you like?: ";
		while (!(cin >> user_qty) || user_qty < 0)
		{
			cout << "You did not enter a valid number, try again... \n" << endl;
			cin.clear();
			cin.ignore(200, '\n');
		}
 		n->famous_qty = user_qty;
		user_qty = 0;

		cout << fixed << showpoint << setprecision(2); 
		cout << "Big Kahuna burgers are $" << KAHUNA_COST << " each. How many would you like?: ";
		while (!(cin >> user_qty) || user_qty < 0)
		{
			cout << "You did not enter a valid number, try again... \n" << endl;
			cin.clear();
			cin.ignore(200, '\n');
		}
 		n->kahuna_qty = user_qty;
		user_qty = 0;

		cout << fixed << showpoint << setprecision(2); 
		cout << "Royal burgers are $" << ROYAL_COST << " each. How many would you like?: ";
		while (!(cin >> user_qty) || user_qty < 0)
		{
			cout << "You did not enter a valid number, try again... \n" << endl;
			cin.clear();
			cin.ignore(200, '\n');
		}
 		n->royal_qty = user_qty;
		user_qty = 0;

		cout << fixed << showpoint << setprecision(2); 
		cout << "Fries are $" << FRY_COST << " each. How many would you like?: ";
		while (!(cin >> user_qty) || user_qty < 0)
		{
			cout << "You did not enter a valid number, try again... \n" << endl;
			cin.clear();
			cin.ignore(200, '\n');
		}
 		n->fry_qty = user_qty;
		user_qty = 0;

		cout << fixed << showpoint << setprecision(2); 
		cout << "Shakes are $" << SHAKE_COST << " each. How many would you like?: ";
		while (!(cin >> user_qty) || user_qty < 0)
		{
			cout << "You did not enter a valid number, try again... \n" << endl;
			cin.clear();
			cin.ignore(200, '\n');
		}
 		n->shake_qty = user_qty;
		user_qty = 0;

		cout << fixed << showpoint << setprecision(2); 
		cout << "Sodas are $" << SODA_COST << " each. How many would you like?: ";
		while (!(cin >> user_qty) || user_qty < 0)
		{
			cout << "You did not enter a valid number, try again... \n" << endl;
			cin.clear();
			cin.ignore(200, '\n');
		}
 		n->soda_qty = user_qty;
		user_qty = 0;

		cout << "Any special requests for the order?: ";
		cin.ignore();
		cin.getline (temp_string, STRING_SIZE); 	
		string_size = strlen(temp_string);
		n->order_note = new char[string_size +1];
		strncpy(n->order_note, temp_string, string_size);
		n->order_note[string_size] = '\0'; 
		string_size = 0;

		n->tab_ttl = (n->famous_qty * FAMOUS_COST) + (n->kahuna_qty * KAHUNA_COST) + (n->royal_qty * ROYAL_COST) + (n->fry_qty * FRY_COST) + (n->shake_qty * SHAKE_COST) + (n->soda_qty * SODA_COST); 
		cout << "\nThank you for your order ";  
		cout << n->order_name << ". \n" << endl;

		tab_num = n;
		viewtab();

		order_num++;

		return;

	} // closes else if

	if (order_num >= MAX_TAB)
	{
		cout << "You have entered the maximum amount of orders for the day, please exit the program to clear memory and start over... " << endl;

		return;
	} // Coses else if

	return;
} // closes newtab

void order_tracker::searchtab()
{
	int user_tab = 0;
	char search_name[STRING_SIZE];
	bool match_found = false;
	tab_num = head;
	
	if (order_num <= 0)
	{
		cout << "There are not any orders yet, enter an order before viewing...\n" << endl;
		return;
	}

	cout << "Searching orders by name, please enter the name: ";
	cin.ignore();
	cin.getline(search_name, STRING_SIZE);

	for (int i = 0; i < order_num && tab_num != NULL; i++)
	{
		if (strcmp (search_name, tab_num->order_name) == 0) // a03 fix
		{
			match_found = true;
			break;
		}
		else
			tab_num = tab_num->next; 
	}

	if (match_found == true)
	{			
		match_found = false;
		cout << "\nHere is the order for " << search_name << "\n" << endl; 
		viewtab();
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
	char user_selection = 0;
	ofstream outFile; 
	tab_num = head;

	cout << "Would you like to save todays data to " << file_name << "? (Y)es to save: " ;
	cin.ignore();
	cin.get(user_selection);

	if (user_selection == 'y' || user_selection == 'Y')
	{
		outFile.open(file_name);

		for(int i = 0; i < order_num; i++)
		{
			outFile << tab_num->famous_qty << "," << tab_num->kahuna_qty << "," << tab_num->royal_qty << ","; 
			outFile << tab_num->fry_qty << "," << tab_num->shake_qty << "," << tab_num->soda_qty << ","; 
			outFile << tab_num->order_name << "," << tab_num->order_note << endl;

			tab_num = tab_num-> next;
		}
	}

	return;

} // closes totaltab

void order_tracker::viewtab()
{
	cout << "Customer Name: " << tab_num->order_name << endl;

	if (tab_num->famous_qty == 1)
	{
		cout << tab_num->famous_qty << " Famous burger at $"; 
		cout << fixed << showpoint << setprecision(2); 
		cout << FAMOUS_COST << ", charge = $" << tab_num->famous_qty * FAMOUS_COST << endl;
	}
	else if (tab_num->famous_qty > 1)
	{
		cout << tab_num->famous_qty << " Famous burgers at $"; 
		cout << fixed << showpoint << setprecision(2); 
		cout << FAMOUS_COST << ", charge = $" << tab_num->famous_qty * FAMOUS_COST << endl;
	}

	if (tab_num->kahuna_qty == 1)
	{
		cout << tab_num->kahuna_qty << " Big Kahuna burger at $"; 
		cout << fixed << showpoint << setprecision(2); 
		cout << KAHUNA_COST << ", charge = $" << tab_num->kahuna_qty * KAHUNA_COST << endl;
	}

   	else if (tab_num->kahuna_qty > 1)
	{
		cout << tab_num->kahuna_qty << " Big Kahuna burgers at $"; 
		cout << fixed << showpoint << setprecision(2); 
		cout << KAHUNA_COST << ", charge = $" << tab_num->kahuna_qty * KAHUNA_COST << endl;
	}

	if (tab_num->royal_qty == 1)
	{
		cout << tab_num->royal_qty << " Royal burger at $"; 
		cout << fixed << showpoint << setprecision(2); 
		cout << ROYAL_COST << ", charge = $" << tab_num->royal_qty* ROYAL_COST << endl;
	}

	else if (tab_num->royal_qty > 1)
	{
		cout << tab_num->royal_qty << " Royal burgers at $"; 
		cout << fixed << showpoint << setprecision(2); 
		cout << ROYAL_COST << ", charge = $" << tab_num->royal_qty * ROYAL_COST << endl;
	}

	if (tab_num->fry_qty == 1)
	{
		cout << tab_num->fry_qty << " fry at $"; 
		cout << fixed << showpoint << setprecision(2);
		cout << FRY_COST << ", charge = $" << tab_num->fry_qty * FRY_COST << endl;
	}

	else if (tab_num->fry_qty > 1)
	{
		cout << tab_num->fry_qty << " fries at $";
		cout << fixed << showpoint << setprecision(2);
		cout << FRY_COST << ", charge = $" << tab_num->fry_qty * FRY_COST << endl;
	}

	if (tab_num->shake_qty == 1)
	{
		cout << tab_num->shake_qty << " shake at $"; 
		cout << fixed << showpoint << setprecision(2);
	       	cout << SHAKE_COST << ", charge = $" << tab_num->shake_qty * SHAKE_COST << endl;
	}

	else if (tab_num->shake_qty > 1)
	{
		cout << tab_num->shake_qty << " shakes at $"; 
		cout << fixed << showpoint << setprecision(2); 
		cout << SHAKE_COST << ", charge = $" << tab_num->shake_qty * SHAKE_COST << endl;
	}

	if (tab_num->soda_qty == 1)
	{
		cout << tab_num->soda_qty << " soda at $"; 
		cout << fixed << showpoint << setprecision(2); 
		cout << SODA_COST << ", charge = $" << tab_num->soda_qty * SODA_COST << endl;
	}

	else if (tab_num->soda_qty > 1)
	{
		cout << tab_num->soda_qty << " sodas at $"; 
		cout << fixed << showpoint << setprecision(2); 
		cout << SODA_COST << ", charge = $" << tab_num->soda_qty * SODA_COST << endl;
	}

	cout << fixed << showpoint << setprecision(2); 
	cout << "\nTotal charge = $" << tab_num->tab_ttl << "\n" << endl;

	cout << "Order Notes: " <<  tab_num->order_note << endl;

	return;

} // closes viewtab
