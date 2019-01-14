#ifndef linkedqueue_h
#define linkedqueue_h

using namespace std;

#include "data.h"

class queue 
{
private:
	struct node
	{
		data queueHouse; // Stores house object
		node * next; // Stores next pointer
	};
	node * front;  // Stores front of queue 
	node * end;  // Stores end of queue 
	int queueNum; // Stores number of items in queue; 
public:
	queue(char * fileName); // Default constructor
	~queue(); // Deconstructor
	queue(const queue& queueIn); // Copy constructor
	const queue& operator =(const queue& queueIn); // Assignment Overload
	bool dequeue(data& houseIn); // Remove item from front of queue 
	void display(data& houseIn) const; // Display item in queue  
	void displayAll() const; // Display entire queue 
	void enqueue(const data& houseIn); // Store new item at end of queue 
	bool isEmpty() const; // Checks if queue is empty
	bool peek(data& houseIn) const; // Returns pointer to front of queue  
};

#endif
