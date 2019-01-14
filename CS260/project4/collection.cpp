/*******************
Privte data members:
treeNode * root;
hashNode ** table;
int treeSize;
int tableSize;

******************/

#include <iostream>
#include <cstring>
#include <fstream>
#include "collection.h"
#include "data.h"

using namespace std;

collection::collection() : capacity(DEFAULT_CAPACITY), root(NULL), treeSize(0), tableSize(0)
{
	initializeTable();
}

collection::collection(char * fileName) : capacity(DEFAULT_CAPACITY), root(NULL), treeSize(0), tableSize(0)
{
	initializeTable();

	char name[100] = {'\0'};
	char events[100] = {'\0'};
	char number[100] = {'\0'};
	char products[100] = {'\0'};
	char tempString[100] = {'\0'};

	ifstream inFile;
	inFile.open(fileName);
	inFile.peek();

	while (!inFile.eof() && !inFile.fail())
	{
		inFile.getline(name, 100, ';');
		inFile.getline(number, 100, ';');
		inFile.getline(products, 100, ';');
		inFile.getline(events, 100, ';');
		inFile.ignore(100, '\n');

		data currData(name, number, products, events);
		insert(currData);

		inFile.peek();
	}

	inFile.close();
}

collection::collection(const collection& collectionIn) : root(collectionIn.root), table(collectionIn.table), capacity(collectionIn.capacity), treeSize(collectionIn.treeSize), tableSize(collectionIn.tableSize)
{
	copyTable(table, collectionIn.table);
	copyTree(root, collectionIn.root);

	*this = collectionIn; //Issues with addTree
}

collection::~collection()
{
	destroyTree(root);
	destroyTable();
}

const collection& collection::operator= (const collection& collectionIn)
{
	if (this != &collectionIn)
	{
		destroyTable();
		copyTable(table, collectionIn.table);
		
		destroyTree(root);
		copyTree(root, collectionIn.root);
	}

	return *this;
}


void collection::addTable(data * dataIn)
{
	char key[100] = {'\0'};
	char compKey[100] = {'\0'};
	dataIn->getProduct(key);
	int index = calculateHash(key);

	hashNode * currNode = NULL;
	hashNode * newNode = new hashNode(dataIn); 
	newNode->next = NULL; // Fix?
	hashNode * prevNode = NULL;

	if (table[index] == NULL)
	{
		table[index] = newNode;
		newNode->next = NULL;	
	}
	else
	{
	       	currNode = table[index];

		while (currNode != NULL)
		{
			currNode->vendorData->getProduct(compKey);

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
			else if (!currNode->next)
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

	tableSize++;

	return;
}

void collection::addTree(data * dataIn)
{
	if (dataIn)
	{
		root = addTreeHelper(dataIn,root);
	}
	else
		return;
}

treeNode* collection::addTreeHelper(data * dataIn, treeNode*& treeIn)
{
	treeNode * currTree = NULL;

	char compStringA[100] = {'\0'};
	char compStringB[100] = {'\0'};

	if (!root)
	{
		root = new treeNode(dataIn);
		root->left = NULL;
		root->right = NULL;
		treeSize++;
		return root;
	}
	else
	{
		currTree = treeIn;

		if (!currTree)
		{
			currTree = new treeNode(dataIn);
			currTree->left = NULL;
			currTree->right = NULL;
			treeSize++;
			return currTree;
		}
		else
		{
			data * currData = currTree->vendorData;

			dataIn->getName(compStringA);
			currData->getName(compStringB);

			if (strcmp(compStringA,compStringB) < 0)
			{
				currTree->left = addTreeHelper(dataIn,currTree->left);

			}	
			else
			{
				currTree->right = addTreeHelper(dataIn,currTree->right);
			}

		}
	}
}

int collection::calculateHash(char * key) const
{
	char * temp = key;
	int total = 0;

	while (*temp)
	{
		total = total + *temp;
		temp++;
	}

	return total%capacity;
}

void collection::copyTable(hashNode ** newTable, hashNode ** tableIn)
{ 
	newTable = new hashNode*[capacity];

	for (int i = 0; i < capacity; i++)
	{
		if (tableIn[i] == NULL)
		{
			newTable[i] = NULL;
		}
		else
		{
			newTable[i] = new hashNode(tableIn[i]->vendorData);
			hashNode * srcNode = tableIn[i]->next;
			hashNode * destNode = newTable[i];

			while (srcNode)
			{
				destNode->next = new hashNode(srcNode->vendorData);
				destNode = destNode->next;
				srcNode = srcNode->next;
			}

			destNode->next = NULL;
		}
	}
}

void collection::copyTree(treeNode *& newRoot, treeNode * treeIn)
{
	if (treeIn)
	{
		newRoot = new treeNode(treeIn->vendorData);

		if (treeIn->left)
		{
			copyTree(newRoot->left, treeIn->left);
		}
		if (treeIn->right)
		{
			copyTree(newRoot->right, treeIn->right);
		}
	}
	else
	{
		newRoot = NULL;
	}
}

treeNode* collection::deleteNode(treeNode *& treeIn)
{
	treeNode * currNode = treeIn;
	treeNode * prevNode = NULL;

	data * currData;

	if (!treeIn)
	{
		return NULL;
	}
	else if (!treeIn->right && !treeIn->left)
	{
//		delete treeIn->vendorData; // Errors 
		delete treeIn;
		treeIn = NULL;
		return treeIn; 
	}
	else if (!treeIn->right)
	{
		currNode = treeIn->left;
//		delete treeIn->vendorData;
		delete treeIn;
		treeIn = NULL;
		return currNode; 
	}
	else if (!treeIn->left)
	{
		currNode = treeIn->right;
//		delete treeIn->vendorData;
		delete treeIn;
		treeIn = NULL;
		return currNode; 
	}
	else
	{
		currNode = treeIn->right;
		prevNode = NULL;
		while (currNode->left)
		{
			prevNode = currNode;
			currNode = currNode->left;
		}

		treeIn->vendorData = currNode->vendorData;

		if (!prevNode)
		{
			treeIn->right = currNode->right;
                }
                else
                {
                        prevNode->left = currNode->right;
                }

		currNode->right = NULL;

// 	 	delete currNode->vendorData;
	    	delete currNode;
		return treeIn;
	}

	treeSize--;
}
	
void collection::destroyTable()
{

	for (int i = 0; i < capacity; i++)
	{
		hashNode * head = table[i];
		hashNode * currNode = NULL; 

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

void collection::destroyTree(treeNode *& root)
{
	if (root)
	{
		destroyTree(root->left);
		destroyTree(root->right);
		delete root->vendorData;
		delete root;
		root = NULL;
	}
}

void collection::displayName() 
{
	displayNameHelper(root);
}

void collection::displayNameHelper(treeNode * treeIn)
{
	if (treeIn)
	{
		if (treeIn->left)
		{
			displayNameHelper(treeIn->left);
		}

		data * tempData = treeIn->vendorData;
		cout << *tempData << endl;

		if (treeIn->right)
		{
			displayNameHelper(treeIn->right);
		}
	}
}

void collection::displayProduct(void) const
{
	hashNode * currNode = NULL;

	for(int i = 0; i < capacity; i++)
	{
		for(currNode = table[i]; currNode; currNode = currNode->next)
		{
			data * tempData = currNode->vendorData;
			cout << *tempData << endl;
		}
	}
}

int collection::getTreeSize()
{
	return treeSize;
}

int collection::getTableSize()
{
	return tableSize;
}

void collection::initializeTable()
{
	table = new hashNode*[capacity];

	for (int i = 0; i < capacity; i++)
	{
		table[i] = NULL;
	}
}

void collection::insert(const data& dataIn)
{
	char tempChar[100] = {'\0'};

	data * newData = new data(dataIn);

	addTree(newData);
	addTable(newData);
}

bool collection::remove(char * nameIn)
{
	bool delStatus = false;

	root = removeTree(root,nameIn,delStatus);

	if (delStatus)
	{
		return true;
	}
	else
		return false;
}

bool collection::removeTable(char * productIn, char * nameIn)
{
	int index = calculateHash(productIn);

	hashNode * currNode = table[index];
	hashNode * prevNode = NULL;
	char name[100] = {'\0'};
	char product[100] = {'\0'};

	while(currNode)
	{
		currNode->vendorData->getProduct(product);
		currNode->vendorData->getName(name);

		if (strcmp(productIn, product) == 0 && strcmp(nameIn, name) == 0)
		{
			if (!prevNode)
			{
				table[index] = currNode->next;
			}
			else
			{
				prevNode->next = currNode->next;
			}

			currNode->next = NULL;
			delete currNode->vendorData;
			delete currNode;

			tableSize--;

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

treeNode* collection::removeTree(treeNode*& treeIn, char * nameIn, bool& delStatusIn)
{
	char name[100] = {'\0'};
	char product[100] = {'\0'};

	if(!treeIn)
	{
		delStatusIn = false;
		return NULL;
	}
	else
	{
		treeIn->vendorData->getName(name);

		int temp = strcmp(name, nameIn);

		if(temp == 0)
		{
			treeIn->vendorData->getProduct(product);
			removeTable(product, name);

			if (treeIn == root)
			{
				root = deleteNode(treeIn);
			}
			else
				treeIn = deleteNode(treeIn);

			delStatusIn = true;
			return treeIn;
		}
		else if(temp < 0)
		{

			treeIn->right = removeTree(treeIn->right, nameIn, delStatusIn);
			return treeIn;
		}
		else
		{
			treeIn->left = removeTree(treeIn->left, nameIn, delStatusIn);
			return treeIn;
		}
	}
}

int collection::retrieveProduct(data dataRtn[], char * productIn, int dataItemsRtn) const
{
	int dataItems = 0;

	int strCmp = 0;
	char compString[100] = {'0'};

	int index = calculateHash(productIn);
	int i = 0;

	hashNode * currNode = table[index];

	if (currNode)
	{
		while (currNode)
		{
			data * tempData = NULL;
		       	tempData = currNode->vendorData;
			dataRtn[dataItems] = *tempData; 
			dataItems++;
			currNode = currNode->next;
		}

		dataItemsRtn = dataItems;

		return dataItems;
	}
	else
		return 0;
}

bool collection::retrieveName(data& dataRtn, char * nameIn) const
{
	return retrieveNameHelper(root, dataRtn, nameIn);
}

bool collection::retrieveNameHelper(treeNode * treeIn, data& dataRtn, char * nameIn) const
{
	char name[100] = {'\0'};

	if(!treeIn)
	{
		return false;
	}
	else
	{
		treeIn->vendorData->getName(name);

		int temp = strcmp(name, nameIn);

		if(temp == 0)
		{
			data * tempData = treeIn->vendorData;
			dataRtn = *tempData;
			return true;
		}
		else if(temp < 0)
		{
			return retrieveNameHelper(treeIn->right, dataRtn, nameIn);
		}
		else
		{
			return retrieveNameHelper(treeIn->left, dataRtn, nameIn);
		}
	}

}

void collection::writeOut (char * fileName)
{
	ofstream outFile;
	outFile.open(fileName);

	writeOutHelper(root, outFile);

	outFile.close();
}

void collection::writeOutHelper (treeNode * treeIn, ofstream& outFile)
{
	char events[100] = {'\0'};
	char name[100] = {'\0'};
	char number[100] = {'\0'};
	char products[100] = {'\0'};

	if (treeIn)
	{
		if(treeIn->left)
		{
			writeOutHelper(treeIn->left, outFile);
		}

			treeIn->vendorData->getName(name);
			treeIn->vendorData->getNumber(number);
			treeIn->vendorData->getProduct(products);
			treeIn->vendorData->getEvents(events);

			outFile << name << ";";
			outFile << number << ";";
			outFile << products << ";";
			outFile << events << ";";
			outFile << '\n';

		if (treeIn->right)
		{
			writeOutHelper(treeIn->right, outFile);
		}
	}
}
