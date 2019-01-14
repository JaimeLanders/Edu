#include <iostream>
#include "clist.h"

using namespace std;

// Write your functions in this file.

int count (node * head)
{
//	cout << "count " << endl;
//	cout << "head = " << head << endl;

	node * currNode = head;
//	cout << "currNode = " << currNode << endl;
	int count = 1;
//	cout << "count = " << count << endl; 

	while (currNode->next != head)// != NULL)
	{
		count++;
//		cout << "count = " << count << endl; 
		currNode = currNode->next;
//		cout << "currNode = " << currNode << endl;
	}
	
//	cout << "count total = " << count << endl; 
	return count;
}

int countR (node * head)
{
//	cout << "countR " << endl;
//	cout << "head = " << head << endl;

	if (head)
		return countR(head,head,1);
	else
		return 0;
}

int countR (node * head, node * nodeIn, int countIn)
{
//	cout << "countR private" << endl;
//	cout << "nodeIn = " << nodeIn << endl;
//	cout << "coutIn = " << countIn << endl; 

	node * currNode = nodeIn;
//	cout << "currNode = " << currNode << endl;
	int count = countIn;
//	cout << "count = " << count << endl; 

	if (currNode->next != head)
	{
		count++;
		countR(head,currNode->next, count);//++);
	}
	else
		return count;
}

int sum (node * head)
{
//	cout << "sum " << endl;
//	cout << "head = " << head << endl;

	node * currNode = head;
//	cout << "currNode = " << currNode << endl;
	int sum = currNode->data;
//	cout << "sum = " << sum << endl; 

	while (currNode->next != head)// != NULL)
	{
		sum = sum + currNode->data;
//		cout << "sum = " << sum << endl; 
		currNode = currNode->next;
//		cout << "currNode = " << currNode << endl;
	}
	
//	cout << "sum total = " << sum << endl; 
	return sum;
}

int sumR (node * head)
{
//	cout << "sumR " << endl;
//	cout << "head = " << head << endl;

	if (head)
		return sumR(head,head,head->data);
	else
		return 0;
}

int sumR (node * head, node * nodeIn, int sumIn)
{
//	cout << "sumR private" << endl;
//	cout << "nodeIn = " << nodeIn << endl;
//	cout << "sumIn = " << sumIn << endl; 

	node * currNode = nodeIn;
//	cout << "currNode = " << currNode << endl;
	int sum = sumIn;
//	cout << "sum = " << sum << endl; 

	if (currNode->next != head)
	{
		sum = sum + currNode->data;
		sumR(head,currNode->next,sum);
	}
	else
		return sum;
}
