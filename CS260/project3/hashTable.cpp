#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>
#include "data.h"
#include "hashTable.h"

using namespace std;

hashTable::hashTable ():capacity(DEFAULT_CAPACITY), size(0)
{
	initialize();  
}

hashTable::hashTable (char * fileName):capacity(DEFAULT_CAPACITY), size(0)
{
	char charEat = '\0';
	char tempString[100] = {'\0'};
	float tempFloat = 0.0;

	data newData; 

	initialize();

	ifstream inFile;
	inFile.open(fileName);
	inFile.peek();	

	while(!inFile.eof() && !inFile.fail())
	{
		inFile.getline(tempString, 100, ';');
		newData.setTicker(tempString);  

		inFile.getline(tempString, 100, ';');
		newData.setName(tempString);  

		inFile >> tempFloat;
		inFile >> charEat;
		newData.setValue(tempFloat);

		inFile.getline(tempString, 100, ';');
		newData.setDate(tempString);  

		inFile >> tempFloat;
		if(inFile.get() != '\n') 
			inFile >> charEat;
		newData.setReturn(tempFloat);

		insert(newData);

		inFile.peek();	
	}

	inFile.close();
}

hashTable::hashTable (const hashTable& tableIn):capacity(tableIn.capacity), size(tableIn.size)
{
	table = new node*[capacity];

	for (int i = 0; i < capacity; i++)
	{
		if (tableIn.table[i] == NULL)
		{
			table[i] = NULL;
		}
		else
		{
			table[i] = new node(tableIn.table[i]->stockData);
			node * srcNode = tableIn.table[i]->next;
			node * destNode = table[i];
			while (srcNode)
			{
				destNode->next = new node(srcNode->stockData);
				destNode = destNode->next;
				srcNode = srcNode->next;		
			}

			destNode->next = NULL;
		}
	}
}

const hashTable& hashTable::operator= (const hashTable& tableIn)
{
	if (this == &tableIn)
	{
		return *this;
	}
	else
	{
		destroy();

		table = new node*[capacity];
		capacity = tableIn.capacity;
		size = tableIn.size;

		for (int i = 0; i < capacity; i++)
		{
			if (tableIn.table[i] == NULL)
			{
				table[i] = NULL;
			}
			else
			{
				table[i] = new node(tableIn.table[i]->stockData);
				node * srcNode = tableIn.table[i]->next;
				node * destNode = table[i];
				while (srcNode)
				{
					destNode->next = new node(srcNode->stockData);
					destNode = destNode->next;
					srcNode = srcNode->next;
				}

				destNode->next = NULL;
			}
		}

		return * this;
	}
}

hashTable::~hashTable ()
{
	destroy();
}

int hashTable::calculate(char * key) const
{
	char * temp = key;
	int total = 0;

	while(*temp)
	{
		total = total + *temp;
		temp++;
	}

	return total%capacity;
}

void hashTable::destroy ()
{
	for (int i = 0; i < capacity; i++)
	{
		node * head = table[i];
		node * currNode;

		while(head)
		{
			currNode = head->next;
			head->next = NULL;
			delete head;
			head = currNode;
		}
	}

	delete [] table;
}

void hashTable::display (void) const
{
	node * currNode;// = table[0]; 

	cout << "Stock data in the table: " << endl;
	cout << "\n======================================================================= " << endl;
	cout << "Ticker: \t" << "Name: \t\t\t" << "Value: \t" << "Date: \t\t" << "Return: \t" << endl; 
	cout << "======================================================================= " << endl;

	for (int i = 0; i < capacity; i++)
	{
		for (currNode = table[i]; currNode; currNode = currNode->next)
		{
			cout  << currNode->stockData << endl;
		}
	}

	return;
}

int hashTable::getSize(void) const
{
	return size;
}

void hashTable::initialize()
{
	table = new node*[capacity];

	for (int i = 0; i < capacity; i++)
	{
		table[i] = NULL;
	}
}

void hashTable::insert (const data& dataIn)
{
	char key[100] = {'\0'};
	char compKey[100] = {'\0'};
	dataIn.getTicker(key);
	int index = calculate(key);

	node * currNode = NULL;
	node * newNode = new node(dataIn);
	node * prevNode = NULL;

	if (table[index] == nullptr)
	{
		table[index] = newNode;
		newNode->next = NULL;
	}
	else
	{
		currNode = table[index];

		while (currNode != NULL)
		{
			currNode->stockData.getTicker(compKey);

			if (strcmp(compKey,key) > 0 )
			{
				newNode->next = currNode;

				if (prevNode != NULL)
				{
					prevNode->next = newNode;
					break;
				}
				else
				{
					table[index] = newNode;
					break;
				}
			}
			else if (currNode->next = table[index])
			{
				currNode->next = newNode;
				newNode->next = NULL;
				break;
			}
			else
			{
				prevNode = currNode;
				currNode = currNode->next;
			}
		}
	}

	size++;

	return;
}

bool hashTable::modify (char * key, float newValue, char * newDate, float newReturn)
{
	char ticker [100] = {'\0'};

	int index = calculate(key);

	node * currNode = table[index];

	while (currNode) 
	{
		currNode->stockData.getTicker(ticker);

		if (strcmp(ticker,key) != 0) 
		{
			currNode = currNode->next;
		}
		else
		{
			currNode->stockData.setValue(newValue);
			currNode->stockData.setDate(newDate);
			currNode->stockData.setReturn(newReturn);

			return true;
		}
	}

	return false;
}

void hashTable::monitor ()
{
	node * currNode = NULL;
	int items = 0;
	int collisions = 0;

	for (int i = 0; i < capacity; i++)	
	{
		for (currNode = table[i]; currNode; currNode = currNode->next)
		{
			items++;
		}

		if (items > 1) 
		{
			cout << "Collisions in index " << i << ":  " << items - 1 << endl;

			collisions++;
		}

		items = 0;
	}

	cout << "\nThe total number of collisions in the table: " << collisions << endl;

	return;
}

bool hashTable::remove (char * key)
{
	int index = calculate(key);

	node * currNode = table[index];
	node * prevNode = NULL;
	char ticker[100];
	while(currNode)
	{
		currNode->stockData.getTicker (ticker);
		if (strcmp(key, ticker) == 0)
		{
			if(!prevNode)
			{
				table[index] = currNode->next;
			}
			else
			{
				prevNode->next = currNode->next;
			}

			currNode->next = NULL;
			delete currNode;
			size--;
			return true;
		}
		else
		{
			prevNode = currNode;
			currNode = currNode->next;
		}
	}

	return false;
}

bool hashTable::retrieve (char * key, data& dataIn) const
{
	int index = calculate(key);

	node * currNode = table[index]; 

	dataIn = currNode->stockData;

	return 0;
}

void hashTable::writeOut (char * fileName)
{ 
	char writeName[100] = {'\0'};
	char writeDate[100] = {'\0'};
	char writeTicker[100] = {'\0'};
	float writeReturn = 0.0;
	float writeValue = 0.0;

	node * currNode;

	ofstream outFile;
	outFile.open(fileName);

	for (int i = 0; i < capacity; i++)
	{
		for(currNode = table[i]; currNode; currNode = currNode->next)
		{
			currNode->stockData.getName(writeName);
			currNode->stockData.getDate(writeDate);
			currNode->stockData.getTicker(writeTicker);
			writeReturn = currNode->stockData.getReturn();
			writeValue = currNode->stockData.getValue();

			outFile << writeTicker << ";";
			outFile << writeName << ";";
			outFile << writeValue << ";";
			outFile << writeDate << ";";
			outFile << writeReturn << endl;
		}
	}

	outFile.close();
}
