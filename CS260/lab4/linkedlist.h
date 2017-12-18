#ifndef _LINKED_LIST_
#define _LINKED_LIST_

#include <iostream>

using namespace std;

const int MAXSTRING = 100;

struct node 
{
//	char * linkedChar;
//	char linkedChar;
	int linkedNum;

	node * next;

	node();
//	~node();
};

class LinkedList
{
public:
	node * head;
	void add(int num);
//	void add(char ch);
//	void del(char ch);
	bool del(int num);
//	bool del(char ch);
//	void find(char ch);
	bool find(int num);
//	bool find(char ch);
	void print();
	int sum(void);
	int sumR();  
//	int sumR(void);  
	LinkedList();
	~LinkedList();
private:
//	char linkedChar;
	void add(node * nodeIn, int num);
//	void add(node * nodeIn, char ch);
	bool del(node * nodeIn, int num);
//	bool del(node * nodeIn, char ch);
//	bool find(char& ch);
//	bool find(node * nodeIn, bool chFoundPass, char& ch);
//	void find(node * nodeIn, char& ch);
	bool find(node * nodeIn, int& num);
//	bool find(node * nodeIn, char& ch);
	void print(node * nodeIn);
	int sumR(node * nodeIn, int num);  

	friend std::ostream& operator<<(std::ostream& out, LinkedList& list);
};

#endif // _LINKED_LIST_
