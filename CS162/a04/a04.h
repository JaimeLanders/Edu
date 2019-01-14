/*
Name: Jaime Landers
Class: CS162
Assignement: 4 
Date Started: 8/2/16 
Sources: http://www.isocpp.org for input failure guard on newtab function.  

TODO
1) Implement linked list instead of array of structs X
	a) newtab X
	b) viewtab X
	c) searchtab X
	d) loadtab X 
	e) totaltab X
2) Method (menu option) to list tabs in memory X
	a) fix segmentation fault X
3) Method (menu option) to delete item from linked list X
4) Sort linked list A-Z X
	a) newtab X 
	b) loadtab X 
	c) outfile X
5) Linked list destructor X 
6) Check for memory leaks X 
	a) fix memory leaks X
	b) fix Valgrind errors X
7) a03 fixes X
8) Fix variable names
9) Bug fixes X
	a) Menu reporting bad selection X
*/

#ifndef a04_h
#define a04_h

//#pragma once

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

struct order_info
{
	int famous_qty;
	int kahuna_qty;
	int royal_qty;
	int fry_qty;
	int shake_qty; 
	int soda_qty;
	double tab_ttl;
	char *order_name; // Pointer for dynamic char string
	char *order_note; // Pointer for dynamic char string
	order_info *next; // Stores address of next node in linked list
	order_info *prev; // Stores address of next node in linked list
	order_info(); // Constructor
};

class order_tracker
{
private:
//	char *file_name; // Stores the name of the input/output file
	char file_name[STRING_SIZE]; // Stores the name of the input/output file
	int order_num; // Tracks current number of orders
	order_info *tab_num;  // For viewtab function
	order_info *head;  // Initializes head of linked list
	order_info *tail;  // Initializes tail of linked list
public:
	void deletetab();
	void listtab();
	void loadtab();
	void newtab();
	void searchtab();
	void totaltab();
	void viewtab();
	order_tracker(); // Constructor
	~order_tracker(); // Deconstructor
};

#endif
