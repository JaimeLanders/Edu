#include <cstring>
#include <iomanip>
#include <iostream>
#include <fstream>

using namespace std;

#include "linkedstack.h"

stack::stack() // Stack default constructor
{
	top = NULL;
	stackNum = 0;
}  

stack::stack(const stack& stackIn)
{ 
	if (stackIn.top == NULL)
	{
		top = NULL;
	}
	else
	{
		top = new node;
		top->stackHouse = stackIn.top->stackHouse;

		node * dest = top;
		node * source = stackIn.top->next;
		while (source != NULL)
		{
			dest->next = new node;
			dest = dest->next;
			dest->stackHouse = source->stackHouse;
			source = source->next;
		}
		dest->next = NULL;
	}
}

const stack& stack::operator= (const stack& stackIn)
{
	if (this == &stackIn)
	{
		return *this;
	}
	else
	{
		node * current = top;

		while(top)
		{
			current = top->next;
			delete top;
			top = current;
		}

		if (stackIn.top == NULL)
		{
			top = NULL;
		}
		else
		{
			top = new node;
			top->stackHouse = stackIn.top->stackHouse;

			node * dest = top;
			node * source = stackIn.top->next;
			while(source != NULL)
			{
				dest->next = new node;
				dest = dest->next;
				dest->stackHouse = source->stackHouse;

				source = source->next;
			}
			dest->next = NULL;
		}

		return *this;
	}
}

stack::~stack() // Stack deconstructor
{
	node * current = top;

	while (current != NULL)
	{
		current = current->next;
		top->next = NULL;
		delete top;
		top = current;
	}
}

void stack::display(data * houseIn) const
{
	if (!isEmpty())
	{
		cout << "\nAddress: \t" << houseIn->getAddress() << endl;
		cout << "Square Feet: \t" << houseIn->getSquareFeet() << endl;
		cout << "Bedrooms: \t" << houseIn->getRoomCount() << endl;
		cout << "Bathrooms: \t" << houseIn->getBathCount() << endl;
		cout << "Notes: \t\t" << houseIn->getNotes() << endl;
		cout << "\n===== " << endl;
	}
} // Closes stack display

bool stack::isEmpty() const
{
	if (top == NULL)
		return true; 
	else
		return false;
}

bool stack::peek(data& houseIn) const
{
 	if (!isEmpty())
	{
		houseIn = top->stackHouse;
		return true;
	}
	else
		return NULL;
}

bool stack::pop(data& houseIn)
{
	node * temp = top;// = new node;

	if (isEmpty())
		return false;
	else
	{
		top = top->next;
	}

	if (temp != NULL)
	{
		temp->next = NULL;
		houseIn = temp->stackHouse;
		delete temp;


		stackNum--;

		return true;
	}
}

bool stack::push(const data& houseIn)
{
	node * n = new node;//(houseIn); 
	n->stackHouse = houseIn;
	n->next = NULL;

	if (isEmpty())
	{
		top = n;//ew node(houseIn);
		top->next = NULL;

		stackNum++;

		return true;
	}
	else 
	{
		n->next = top;
		top = n;

		stackNum++;

		return true;

	}

	return false;
}


