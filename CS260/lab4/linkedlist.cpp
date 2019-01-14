#include "linkedlist.h"

node::node()
{
//	linkedChar = '\0';
	linkedNum = 0;

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
		current->linkedNum = 0;
//		current->linkedChar = '\0';
		current=current->next;
		delete previous;
	}

	return;
}

void LinkedList::add(int num)
//void LinkedList::add(char ch)
{
//	cout << "===== " << endl; 
//	cout << "add 1 " << endl;
//	cout << "ch = " << ch << endl;

/*	node * n;//, *current;
	n = new node;
	cout << "n = " << n << endl;
	n->linkedChar = ch;
	add (n, ch);
	add (head, ch);
*/	add (head, num);
}


void LinkedList::add(node * nodeIn, int num)
//void LinkedList::add(node * nodeIn, char ch)
//void LinkedList::add(char ch)
{
/*	cout << "===== " << endl; 
	cout << "add 2 " << endl;
	cout << "num = " << num << endl;
//	cout << "ch = " << ch << endl;
*/
//	node * n;//, *current;
//	node * current;
//	node * after;
//	node * previous;

//	n = new node;
//	n->linkedChar = new char[MAXSTRING + 1];
//	n->linkedChar = ch;
//	cout << "linkedChar = " << n->linkedChar << endl;

//	n = nodeIn;
//	previous = nodeIn;
//	current = nodeIn;
//	after = nodeIn->next;
//	current = nodeIn->next;
//	current = NULL;
//	cout << "n = " << n << endl;
//	cout << "current = " << current << endl;
//	cout << "after = " << after << endl;
//	cout << "previous = " << previous << endl;

//	cout << "check " << endl;

	if (head == NULL)
	{
//		cout << "creating list " << endl;

		node * n;
		n = new node;
		n->linkedNum = num;
//		n->linkedChar = ch;
//		current = NULL;
//		cout << "n = " << n << endl;

/*		n->linkedChar = new char[MAXSTRING + 1];
		n->linkedChar[0] = ch;
		cout << "linkedChar = " << n->linkedChar[0] << endl;

*/ 		head = n;		
//		head = previous;
		head->next = NULL;
	}
	else
	{
//		cout << "after head " << endl;

		node * current = head;

		while (current->next != NULL)
		{
		       current = current->next;
		}

		node * n;
		n = new node;
		n->linkedNum = num;
		current->next = n;
		n->next = NULL;
	}

/*	else if (num < head->linkedNum)
//	else if (ch < head->linkedNum)
//	else if (ch < head->linkedChar)
//	else if (n->linkedChar < head->linkedChar)
//`	else if (n < head)
	{
		cout << "new head " << endl;

		node * n;
		n = new node;
		n->linkedNum = num;
//		n->linkedChar = ch;

		n->next = head;
		head = n; 
	}
	else if (nodeIn->next == NULL)
//	else if (current->next == NULL)
//	else if (current == NULL)
	{
		cout << "end " << endl;

		node * n;
		n = new node;
		n->linkedNum = num;
//		n->linkedChar = ch;

		nodeIn->next = n;	
//		current->next = n;	
//		previous->next = n;	
		n->next = NULL;
	}
	else if (num < nodeIn->linkedNum) 
//	else if (ch < nodeIn->linkedNum) 
//	else if (ch < nodeIn->linkedChar) 
//	else if (n->linkedChar < current->linkedChar) 
	{
		cout << "n < current " << endl;

		node * n;
		n = new node;
		n->linkedNum = num;
//		n->linkedChar = ch;

//		previous->next = n;
		n->next = nodeIn;
//		n->next = current;
	}
	else
	{
		cout << "next " << endl;
//		delete n;

//		previous = current;
//		current = current->next;
//		current = current->next;
		
		add (nodeIn->next, num);
//		add (nodeIn->next, ch);
//		add (current, ch);
	}

*/	return;
}

bool LinkedList::del(int num)
//bool LinkedList::del(char ch)
//void LinkedList::del(char ch)
{
//	cout << "===== " << endl; 
//	cout << "delete 1" << endl;
//	cout << "ch = " << ch << endl;

	if (del(head, num))
//	if (del(head, ch))
		return true;
	else
		return false;

//	return 0;
}

bool LinkedList::del(node * nodeIn, int num)
//bool LinkedList::del(node * nodeIn, char ch)
{
//	cout << "===== " << endl; 
//	cout << "delete 2" << endl;
//	cout << "ch = " << ch << endl;

//	node * current;
//	node * next;
//	node * previous;
//	current = nodeIn;
//	previous = nodeIn;
//	current = nodeIn->next;
//	next = nodeIn->next;
//	current = NULL;
//	previous = NULL;
//	previous = NULL;
//	cout << "linkedChar = " << current->linkedChar << endl;

//	bool chFound = false;

//	cout << "checking " << endl;
//	int i = 0;	
//	for (int i = 0; i++) 
//	if (ch == head->linkedChar[i])
	if (num == head->linkedNum)
//	if (ch == head->linkedChar)
	{
//		cout << "head deleted " << endl;
		node * current = head;
		head = current->next;	
//		current = head;
//		head = current->next;
		current->linkedNum = 0;
//		current->linkedChar = 0;
//		current->linkedChar = '\0';
		delete current;
//		chFound = true; 
		return true;
	}
	else
	{
//		cout << "after head " << endl;
/*		node * current;
		node * previous;
		current = nodeIn->next;
		previous = nodeIn;
*/
		if (nodeIn == NULL)
//		if (current == NULL)
		{
			return false;
//			chFound = false;
		}
//		else if (ch == next->linkedChar)
		else if (num == nodeIn->next->linkedNum)
//		else if (ch == nodeIn->next->linkedChar)
//		else if (ch == current->linkedChar)
		{
//			cout << ch << " deleted " << endl;
			node * current = nodeIn->next;
			node * previous = nodeIn;

			previous->next = current->next;
//			current->next = next->next;
//			nodeIn->linkedChar = '\0';
//			previous->linkedChar = '\0';
			current->linkedNum = '\0';
//			current->linkedChar = '\0';

//			delete next;
//			delete next;
//			delete previous;
			delete current;
//			chFound = true;

//			break;
			return true;
		}
		else
		{
//			cout << "del next " << endl;
//			previous = current;
//			current = current->next;
			del(nodeIn->next, num);
//			del(nodeIn->next, ch);
//			del(current, ch);
//			del(previous, ch);
//			del(next, ch);
		}

	}

//	return -1;
//	return chFound;
}


//void LinkedList::find(char ch)
bool LinkedList::find(int num)
//bool LinkedList::find(char ch)
{
//	cout << "===== " << endl; 
//	cout << "find 1 " << endl;
//	cout << "ch = " << ch << endl;

//	bool chFoundPass;
//     	chFoundPass = false;
//	cout << "chFoundPass initial= " << chFoundPass << endl;

//	chFoundPass = find(head, ch);
//	chFoundPass = find(head, chFoundPass, ch);
//	find(head, ch);

//	cout << "chFoundPass out = " << chFoundPass << endl;
//	return find(head, ch);
//	return chFoundPass;
//	return 1;
//	return 0;
	if (find(head,num))
//	if (find(head,ch))
//	if(chFoundPass)
		return true;
	else
		return false;
}

//bool LinkedList::find(node * nodeIn, bool chFoundPass, char& ch)
//void LinkedList::find(node * nodeIn, char& ch)
bool LinkedList::find(node * nodeIn, int& num) 
//bool LinkedList::find(node * nodeIn, char& ch)
//bool LinkedList::find(char& ch)
{
//	cout << "===== " << endl; 
//	cout << "find 2 " << endl;
//	cout << "ch = " << ch << endl;

//	node * current;
//	current = nodeIn;
//	current = head;
//	cout << "current = " << current << endl;

//	bool chFound;
//  	chFound = 0;
//	chFound = false;
//	cout << "chFound in = " << chFound << endl;

//	cout << "linkedCh = " << current->linkedChar << endl;
		
	if (nodeIn == NULL)
//	if (current == NULL)
	{
//		cout << "not found" << endl;

//		cout << "did not find " << ch << endl;
//		chFound = false;

//		return chFound;
		return false;
	} // CLoses if
	else if (nodeIn->linkedNum == num)
//	else if (nodeIn->linkedNum == ch)
//	else if (nodeIn->linkedChar == ch)
//	if (current->linkedChar == ch && current != NULL)
	{
//		cout << "***found*** " << endl;
//		chFound = true;

//		cout << "found " << ch << endl;

//		return chFound;
		return true;
	} // Closes else if
//	else if (current->linkedChar != ch && current != NULL)		
//	else if (current != NULL)
//	else if (current->next != NULL)
	else
	{
//		cout << "next " << endl;

//		current = current->next;

//		find(current->next, chFound, ch);
//		find(current, chFound, ch);
		find(nodeIn->next, num);
//		find(nodeIn->next, ch);
	} // Closes else if
//	else
//	{
/*		cout << "check " << endl;

		cout << "chFound out = " << chFound << endl;

		if (chFound == true)
			return true;
		else
			return false;
	} //  Closes else
*/
//	cout << "chFound out = " << chFound << endl;
		
//	return true;
//	return chFoundPass;
//	return chFound;
//	return 0;
//	return -1;
//	return;

//	if (chFound == true)
//		return true;
//	else
//		return false;

} // CLoses find()

void LinkedList::print()
{
//	cout << "===== " << endl;
//	cout << "print 1 " << endl;

	print(head);
	return;
}

void LinkedList::print(node * nodeIn)
{
//	cout << "===== " << endl;
//	cout << "print 2 " << endl;

	node * current;
	current = nodeIn;
//	current = head;
//	cout << "current = " << current << endl;

	if (current != NULL)
//	while (current != NULL)
	{
//		cout << "ch = " << current->linkedChar << endl;
		cout << current->linkedNum;
//		cout << current->linkedChar;

//		current = current->next;

		print(current->next);
	}
	else
/*	{
//		print()
		return;
	}
*/		cout << "\n";// << endl;
	return;
}

int LinkedList::sum(void)
{
//	cout << "\nsum working " << endl;

	node * current = head;
	int numTtl = 0;

	while (current != NULL)
	{
//		cout << "\ncurrent " << current << endl;
//		cout << "linkedNum = " << current->linkedNum << endl;
		numTtl = current->linkedNum + numTtl;
//		cout << "numTtl = " << numTtl << endl;

		current = current->next;
	}

	return numTtl;
}

int LinkedList::sumR(void)
{
//	cout << "\nsumR initial working " << endl;

	if (head)
		return sumR(head,0);
	else
		return 0;
}

int LinkedList::sumR(node * nodeIn, int num)
//int LinkedList::sumR(void)
{
//	cout << "\nsumR working " << endl;

	node * current = nodeIn;
//	cout << "current " << current << endl;
	int numTtl = num;

	if (current != NULL)
	{
//		cout << "linkedNum = " << current->linkedNum << endl;

		numTtl = current->linkedNum + numTtl;
//		cout << "numTtl = " << numTtl << endl;

		current = current->next;

		sumR(current, numTtl);
	}
	else
		return numTtl;
//	return 0;
}
