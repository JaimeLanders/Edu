#ifndef HASHTABLE_H 
#define HASHTABLE_H
#include <iostream>
#include "data.h"

using namespace std;

class hashTable 
{
	struct node
	{
		data stockData;
		node * next;
		node (const data& dataIn)
		{
			stockData = dataIn;
			next = NULL;
		}
	};
	node ** table;
	int capacity;
	const static int DEFAULT_CAPACITY = 11;
	int size;
	int calculate (char * key) const;
	void destroy ();
	void initialize ();
public:
	hashTable ();
	hashTable (char * fileName);
	hashTable (const hashTable& hashTableIn);
	const hashTable& operator= (const hashTable& tableIn);
	~hashTable ();
	void display (void) const;
	int getSize (void) const;
	void insert (const data& dataIn);
	bool modify (char * key, float newValue, char * newDate, float newReturn);
	void monitor ();
	bool remove (char * key);
	bool retrieve (char * key, data& dataIn) const;
	void writeOut (char * fileName);
};

#endif
