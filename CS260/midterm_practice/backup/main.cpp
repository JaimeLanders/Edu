#include "dlist.h"
using namespace std;

int main()
{

	int newInt = 0;
	int position = 0;
    node * head = NULL;
    build(head);
    display(head);

    //PLEASE PUT YOUR CODE HERE to call the function assigned
	count(head);
	insert(head,newInt,position);
	remove(head,position);


//    display(head);
//    destroy(head);    
    return 0;
}
