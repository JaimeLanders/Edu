#include "dlist.h"
//#include "supplied.o"
using namespace std;

int main()
{

	int newInt = 0;
	int position = 0;
	int nodeNum = 0;
	node * head = NULL;
	build(head);
	display(head);

	//PLEASE PUT YOUR CODE HERE to call the function assigned
	
	nodeNum = count(head);
	cout << "\nNumber of nodes: " << nodeNum << endl;  

	cout <<  "Enter a number to add to the list: ";
	cin >> newInt;
	cout << "newInt = " << newInt << endl;

	cout << "Enter an index to place the number: ";
	cin >> position;
	cout << "position = " << position << endl;

	if (position == 0)
	{
		insert(head,newInt,position);
		head = head->previous;
	}
	else if (position != 0 && position < nodeNum)
	{
		insert(head,newInt,position);
	}
	else
	{
		cout << "Position exceeds index... " << endl;

		insert(head,newInt,nodeNum);

	}

	display(head);

	cout << "\nNow removing " << newInt << " at position " << position << endl;

	if (position == 0)
	{
		head = head->next;
		remove(head,position);
	}
	else
		remove(head,position);

	display(head);
	destroy(head);    
	return 0;
}
