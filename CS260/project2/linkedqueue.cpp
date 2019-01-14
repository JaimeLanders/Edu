#include <cstring>
#include <iomanip>
#include <iostream>
#include <fstream>

using namespace std;

#include "linkedqueue.h"

queue::queue(char * fileName) // Queue default constructor
{
	front = NULL;
	end = NULL;
	queueNum = 0;

	char charEat = '\0';
	char tempString[100] = {'\0'};
	char * passString = {'\0'};
	float tempFloat = 0.0;
	int tempInt = 0;
	int stringSize = 0;

	ifstream inFile;	
	inFile.open(fileName);
	inFile.peek();

	while(!inFile.eof() && !inFile.fail())
	{
		data n;
		inFile.getline(tempString,100,';');
		n.setAddress(tempString);

		inFile >> tempInt;
		n.setSquareFeet(tempInt);
		inFile >> charEat; 
		inFile >> tempInt;
		n.setRoomCount(tempInt);
		inFile >> charEat; 
		inFile >> tempFloat;
		n.setBathCount(tempFloat);
		inFile >> charEat; 

		inFile.getline(tempString,100);

		n.setNotes(tempString);
		passString = '\0';

		inFile.peek();

		enqueue (n);

	} // Closes while

} // Closes data constructor 

queue::queue(const queue& queueIn)
{
	if (queueIn.front == NULL)
	{
		front = NULL;
		end = NULL;
	}
	else
	{
		front = new node;
		front->queueHouse = queueIn.front->queueHouse;

		node * dest = front;
		node * source = queueIn.front->next;

		while (source != NULL)
		{
			dest->next = new node;
			dest = dest->next;
			dest->queueHouse = source->queueHouse;

			source = source->next;
		}

		dest->next = NULL;

		end = dest;
	}
}

const queue& queue::operator =(const queue& queueIn)
{
	if (this != &queueIn)
	{
		return *this;
	}
	else
	{
		node * current = front;

		while(front)
		{
			current = front->next;
			delete front;
			front = current;
		}

		if (queueIn.front == NULL)
		{
			front = NULL;
			end = NULL;
		}
		else
		{
			front = new node;
			front->queueHouse = queueIn.front->queueHouse;

			node * dest = front;
			node * source = queueIn.front->next;
			while(source != NULL)
			{
				dest->next = new node;
				dest = dest->next;
				dest->queueHouse = source->queueHouse;

				source = source->next;
			}
			dest->next = NULL;

			end = dest;
		}

		return * this;
	}
}


queue::~queue() // Queue deconstructor
{
	node * current = front;

	while (front)
	{
		current = front->next;
		delete front;	
		front = current;
	}

	front = end = NULL;
}  

bool queue::dequeue(data& houseIn)
{
	if (!isEmpty())
	{
		node * temp = front;
		front = front->next;
		houseIn = temp->queueHouse;
		delete temp; //Valgrind errors

		queueNum--;

		return true;
	}
	else
	{

		return false;
	}

} // Closes queue dequeue

void queue::display(data& houseIn) const
{
	if (!isEmpty())
	{
		cout << "Address: \t" << houseIn.getAddress() << endl;
		cout << "Square Feet: \t" << houseIn.getSquareFeet() << endl;
		cout << "Bedrooms: \t" << houseIn.getRoomCount() << endl;
		cout << "Bathrooms: \t" << houseIn.getBathCount() << endl;
		cout << "Notes: \t\t" << houseIn.getNotes() << endl;
		cout << "\n===== " << endl;
	}
	
	return;
} // Closes queue display all

void queue::displayAll() const
{
	node *  current = front; 

	while(current != NULL) 
	{
		cout << current->queueHouse << endl;
		current = current->next;
	}

	return;

} // Closes queue display all

void queue::enqueue(const data& houseIn)
{

	node * n = new node();
	n->queueHouse = houseIn;
	n->next = NULL;

	if (isEmpty()) // Queue empty
		{
			front = n;
			end = n;
			queueNum++;
		}
		else // End of queue
		{
			end->next = n; 
			end = n;
			queueNum++;
		}

	return;
}

bool queue::isEmpty() const
{

	if (front == NULL)
		return true; 
	else
		return false;
}

bool queue::peek (data& houseIn) const
{

	if (!isEmpty())
	{
		houseIn = front->queueHouse; 
		return true;
	}
}
