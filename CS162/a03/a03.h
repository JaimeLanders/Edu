/*
Name: Jaime Landers
Class: CS162
Assignement: 3 
Date Started: 7/20/16 
Sources: http://www.isocpp.org for input failure guard on newtab function.  

TODO
1) File input X  
-Fix loadtab eof extra loop X
2) Dynamic memory allocation X 
3) Destructor X 
4) Open & Close same file X 
5) a02 fixes X 
6) Check valgrind for memory leak X
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
	char *order_name;
	char *order_note;
};

class order_tracker
{
private:
	char file_name[STRING_SIZE];
	int current_tab; 
	int tab_num; 
	menu_items tab_number[MAX_TAB]; 
public:
	void loadtab();
	void newtab();
	void searchtab();
	void totaltab();
	void viewtab(int);
	order_tracker();
	~order_tracker();
};
