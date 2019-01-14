#include <iostream>
#include "dlist.h"

using namespace std;

//put the implmenetation of the required functions here
node::node()
{
//	cout << "constructor " << endl;
	next = NULL;
	previous = NULL;
	data = 0;
}

node::~node()
{
	cout << "deconstructor " << endl;
}


int count(node * nodeIn)
{
	if (nodeIn != NULL)
		return count (nodeIn, 0);
	else
	       	return 0;
}

int count(node * nodeIn, int nodeNum)
{
//	cout << "count " << endl;
//	cout << "nodeIn = " << nodeIn << endl;
//	cout << "nodeNum = " << nodeNum << endl;

	if (nodeIn != NULL)
		(count(nodeIn->next, nodeNum+1));
	else
		return nodeNum; 
}

void insert(node * nodeIn, int newInt, int position)
{
/*	cout << "insert " << endl;
	cout << "nodeIn = " << nodeIn << endl;
	cout << "newInt = " << newInt << endl;
	cout << "position = " << position << endl;
*/
	if (nodeIn != NULL)// && nodeIn->position == position) 
		insert(nodeIn, newInt, position, 0);
	return;
		
}

void insert(node * nodeIn, int newInt, int position, int currNodeNum)
{
/*	cout << "insert " << endl;
	cout << "nodeIn = " << nodeIn << endl;
	cout << "newInt = " << newInt << endl;
	cout << "position = " << position << endl;
	cout << "currNode = " << currNodeNum << endl;
*/
	int currNum = currNodeNum;
//	cout << "currNum = " << currNum << endl;

	if (position == 0)
	{
//		cout << "new head " << endl;
		node * n = new node;
		n->data = newInt;
		n->next = nodeIn;
		n->previous = NULL;

		nodeIn->previous = n;
	}
	else if (nodeIn != NULL && position != 0 && position == currNodeNum) 
	{
//		cout << "added" << endl;

		node * currNode = nodeIn;
		node * prevNode = nodeIn->previous;
		node * n  = new node;

		n->data = newInt;
		n->next = currNode;
		n->previous = prevNode;

		prevNode->next = n;
		currNode->previous = n;
	}
/*	else if (currNodeNum == count(head))
	{
		cout << "end " << endl;

		node * prev = nodeIn 

		node * currNode = nodeIn;
		node * prevNode = nodeIn->previous;
		node * n  = new node;
		n->data = newInt;
		n->previous = 
		n->next = NULL;

	}
*/	else if (nodeIn->next != NULL)
	{
//		cout << "next " << endl;
		currNum++;
//		cout << "currNum = " << currNum << endl;
		insert (nodeIn->next, newInt, position, currNum);
//		insert (nodeIn->next, newInt, position, currNode++);
	}
	else
	{
//		cout << "end " << endl;
		
		node * currNode = nodeIn;

		node * n = new node;
		n->data = newInt;
		n->previous = currNode;
		n->next = NULL;

		currNode->next = n;

	}

//	cout << "check " << endl;
	return;
}

int remove(node * nodeIn, int position)
{ 
/*	cout << "remove " << endl;
	cout << "position = " << position << endl;
*/
	if (nodeIn != NULL)
		return remove(nodeIn, position, 0);
	else
		return 0;
}

int remove(node * nodeIn, int position, int currNodeNum)
{ 
/*	cout << "remove " << endl;
	cout << "nodeIn = " << nodeIn << endl;
	cout << "position = " << position << endl;
	cout << "currNodeNum = " << currNodeNum << endl;
*/
	int currNum = currNodeNum;

	if (position == 0 && nodeIn != NULL)
	{
//		cout << "head removed " << endl;

		node * currNode = nodeIn;
		node * prevNode = currNode->previous;

		delete prevNode;
		currNode->previous = NULL;
	}
	else if (nodeIn != NULL && position == currNodeNum)
	{
//		cout << "removed " << endl;

		node * currNode = nodeIn;
		node * prevNode  = currNode->previous;
		node * nextNode  = currNode->next;

		if (currNode->next != NULL)
		{
			prevNode->next = nextNode;
			nextNode->previous = prevNode;
		}
		else
			prevNode->next = NULL;
		delete currNode;
	}
	else
	{
//		cout << "next " << endl;
		currNum++;
		remove(nodeIn->next, position, currNum);
	}

	return currNum;
}
