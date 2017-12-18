#ifndef _LINKED_LIST_
#define _LINKED_LIST_

#include <iostream>

using namespace std;

const int MAXSTRING = 100;

struct node 
{
//	char * linkedChar;
	char linkedChar;

	node * next;

	node();
//	~node();
};

class LinkedList
{
private:
	node * head;
public:
	LinkedList();
	~LinkedList();
	 
//	char linkedChar;

	void add(char ch);
	bool find(char& ch);
	bool del(char ch);
	void print();

	friend std::ostream& operator<<(std::ostream& out, LinkedList& list);
};

#endif // _LINKED_LIST_jjkkk
