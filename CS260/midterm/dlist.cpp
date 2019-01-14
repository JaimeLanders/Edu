#include "dlist.h"

using namespace std;

//put the implmenetation of the required functions here

int countEven(node * head) 
{
    if (head == NULL) 
        return 0;
    else
        return countEven(head, 0); 
} 

int countEven(node * nodeIn, int currCount) 
{
/*  cout << "countEven " << endl;
    cout << "nodeIn = " << nodeIn << endl;
    cout << "currCount = " << currCount << endl;
*/
    int numEven = currCount;

    if (nodeIn == NULL) 
        return numEven;
    else if(nodeIn->data % 2 == 0)
        numEven++;

    countEven(nodeIn->next, numEven); 
} 

int removeEven(node * head) 
{
 if (head == NULL) 
        return 0;
    else
        return removeEven(head, 0);
} 

int removeEven(node * nodeIn, int currCount) 
{
    cout << "\nremoveEven " << endl;
    cout << "nodeIn = " << nodeIn << endl;
    cout << "currCount = " << currCount << endl;

    int numRemoved = currCount;

    if (nodeIn == NULL) 
        return numRemoved;
    else if(nodeIn->data % 2 == 0)
    {
        cout << "nodeIn data = " << nodeIn->data << endl;
	cout << "deleted" << endl;

        node * currNode = nodeIn;
    	node * nextNode = nodeIn->next;
    	node * prevNode = nodeIn->previous;

        if (nextNode != NULL) 
	{
	    prevNode->next = nextNode; 
            nextNode->previous = prevNode;
	}
	else 
	    prevNode->next = NULL;

	currNode->next = NULL;
	currNode->previous = NULL;
        delete currNode;

        numRemoved++;
        removeEven(nextNode, numRemoved);

        cout << "check " << endl;
    } 
    else
   	    removeEven(nodeIn->next, numRemoved);

} 
