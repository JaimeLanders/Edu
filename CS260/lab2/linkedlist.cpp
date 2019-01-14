#include "linkedlist.h"

node::node()
{
	linkedChar = '\0';

	return;
}
LinkedList::LinkedList()
{
//	cout << "LinkedList constructor " << endl;

	head = NULL;

	return;
}

LinkedList::~LinkedList()
{
//	cout << "LinkedList deconstructor " << endl;

	node * current;
	node * previous;

	current = head;
	previous = head;

	while (current != NULL)
	{
//		cout << "linkedChar = " << current->linkedChar;
		previous = current;
		current->linkedChar = '\0';
		current=current->next;
		delete previous;
	}


	return;
}

void LinkedList::add(char ch)
{
/*	cout << "===== " << endl; 
	cout << "add " << endl;
	cout << "ch = " << ch << endl;
*/
	node * n;//, *current;
	node * current;

	n = new node;
	current = NULL;
//	cout << "n = " << n << endl;
	
//	n->linkedChar = new char[MAXSTRING + 1];
	n->linkedChar = ch;
//	cout << "linkedChar = " << n->linkedChar << endl;

	if (head == NULL)
	{
//		cout << "creating list " << endl;
//		n = new node;
//		current = NULL;
//		cout << "n = " << n << endl;

/*		n->linkedChar = new char[MAXSTRING + 1];
		n->linkedChar[0] = ch;
		cout << "linkedChar = " << n->linkedChar[0] << endl;

*/		head = n;
		head->next = NULL;
	}
	else if (n < head)
//`	else if (n < head)
	{
//		cout << "new head " << endl;

		n->next = head;
		head = n; 
	}
	else
	{
//		cout << "after head " << endl;

		current = head;

		while (current != NULL)
		{
			if (n < current)
			{
//				cout << "after current " << endl;
				n->next = current;
			}
			else if (current->next == NULL)
			{
//				cout << "last" << endl;

				current->next = n;
				n->next = NULL;

				return;
			}
			else 
			{
//				cout << "next" << endl;

				current = current->next;
			}

		}

	}

	return;
}

bool LinkedList::find(char& ch)
{
/*	cout << "===== " << endl; 
	cout << "find " << endl;
	cout << "ch = " << ch << endl;
*/
	node * current;
	current = head;
//	cout << "current = " << current << endl;
//	cout << "linkedCh = " << current->linkedChar << endl;

	bool chFound = false;
	
	for (int i = 0; current != NULL; i++)
//	while (current != NULL)
	{

//	cout << "linkedCh = " << current->linkedChar << endl;

//		if (current->linkedChar[i] == ch)
		if (current->linkedChar == ch)
		{
//			cout << "found " << endl;
			chFound = true;

			break;

//		return 0;
		}
		else if (current->next == NULL)
		{
//			cout << "not found" << endl;
			chFound = false;

			break;

//			return 1;
		}
		else
		{
//1			cout << "next " << endl;

			current = current->next;
		}
	}

//	cout << "chFound = " << chFound << endl;
	return chFound;
//	return 0;
}

bool LinkedList::del(char ch)
{
/*	cout << "===== " << endl; 
	cout << "delete " << endl;
	cout << "ch = " << ch << endl;
*/
	node * current;
	node * previous;
	current = NULL;
	previous = NULL;
//	cout << "linkedChar = " << current->linkedChar << endl;

	bool chFound = false;

//	cout << "checking " << endl;
//	int i = 0;	
//	for (int i = 0; i++) 
//	if (ch == head->linkedChar[i])
	if (ch == head->linkedChar)
	{
//		cout << "head deleted " << endl;
		current = head;
		head = current->next;
		current->linkedChar = '\0';
		delete current;
		chFound = true; 
	}
	else
	{
//		cout << "after head " << endl;
		current = head;
		previous = head;

		while (current != NULL)
		{
//			cout << "current = " << current << endl;

//			if (ch == current->linkedChar[i])
			if (ch == current->linkedChar)
			{
//				cout << ch << " deleted " << endl;
				previous->next = current->next;
				current->linkedChar = '\0';
				delete current;
				chFound = true;

				break;
			}
			else
			{
//				cout << "del next " << endl;
				previous = current;
				current = current->next;
			}
		}

	}

	return chFound;
}

void LinkedList::print()
{
//	cout << "===== " << endl;
//	cout << "print " << endl;

	node * current;
	current = head;
//	cout << "current = " << current << endl;

	while (current != NULL)
	{
//		cout << "ch = " << current->linkedChar << endl;
		cout << current->linkedChar;

		current = current->next;
	}
	cout << "\n";// << endl;
	return;
}
