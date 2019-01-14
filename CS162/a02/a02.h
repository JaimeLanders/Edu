/*
Name: Jaime Landers
Class: CS162
Assignement: 2 
Date Started: 7/10/16 
Sources: http://www.isocpp.org for input failure guard on newtab function.  

TODO
1) Get functions working inside classes X
2) Add additional burgers X  
3) Add names and  notes to orders X
4) Don't add 0 total items to bills X
5) Correct singular/plural wording X
6) Search order by name instead of number X  
7) Output CSV file on exit X
8) a01 fix setprecision X 
9) a01 fix cout in for statements X
10) Fix order of viewtab X
11) Fix getline statements X
*/

#pragma once

#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>

const double FAMOUS_COST = 11.75;
const double KAHUNA_COST = 12.50;
const double ROYAL_COST = 9.25;
const double FRY_COST = 3.49;
const double SHAKE_COST = 5.65;
const double SODA_COST = 2.99;
const int MAX_TAB = 100;
const int STRING_SIZE = 100;

struct menu_items
{
	int famous_qty;
	int kahuna_qty;
	int royal_qty;
	int fry_qty;
	int shake_qty; 
	int soda_qty;
	double tab_ttl;
	char order_name[STRING_SIZE];
	char order_note[STRING_SIZE];
};

class order_tracker
{
private:
	int current_tab; 
	int tab_num; 
	menu_items tab_number[MAX_TAB]; 
public:
	void newtab();
	void searchtab();
	void totaltab();
	void viewtab(int);
	order_tracker();
//	~Orders(); // Deconstructor, not sure if needed
};
