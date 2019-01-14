#include "dlist.h"
using namespace std;

int main()
{
    node * head = NULL;
    int nodeNum = 0; 
    int nodeRem = 0; 
    build(head);
    display(head);

    //PLEASE PUT YOUR CODE HERE to call the function assigned

    nodeNum = countEven(head);
    cout << "\nThe number of even nodes is " << nodeNum << endl;

    while (head != NULL && nodeRem < nodeNum)
    {
        if (head->data % 2 == 0) 
        {
	    node * currNode = head;
	    node * nextNode = head->next;

	    head = nextNode;
	    nextNode->previous = NULL;

	    delete currNode; 
	    nodeRem++;
        }
    	else 
    	{
    	    nodeRem = nodeNum + removeEven(head);
    	}
    }

	cout << "\nRemoved " << nodeNum << " even nodes" << endl;

    display(head);
    destroy(head);    
    return 0;
}
