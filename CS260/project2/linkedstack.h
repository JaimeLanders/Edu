#ifndef linkedstack_h
#define linkedstack_h

using namespace std;

#include "data.h"

class stack
{
private:
	struct node
	{
		data stackHouse;
		node * next; // Stores next item in stack 
	};	
	node * top; // Stores top of stack
	int stackNum; // Stores number of itmes in stack
public:
	stack(); // Default constructor
	stack(const stack& stackIn); // Copy constructor
	const stack& operator= (const stack& stackIn); // Assignment overload
	~stack(); // Deconstructor
	void display(data * houseIn) const; // Display item in stack
	bool isEmpty() const; // Checks if stack is empty
	bool peek(data& houseIn) const; // Return top of stack  
	bool pop(data& houseIn); // Store new item on stack
	bool push(const data& houseIn); // Store new item on stack
};

#endif
