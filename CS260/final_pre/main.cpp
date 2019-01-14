#include "table.h"

#include <iostream>

using namespace std;

int main()
{
	node * root = NULL;
	node * newRoot = NULL;
	int nodeSum = 0;
	build(root);
	display(root);

/*  PLACE YOUR FUNCTION CALL HERE */

	cout << "\n===== " << endl;

	nodeSum = sum(root);
	cout << "\nThe sum of all data is: " << nodeSum << endl;

	cout << "\n===== " << endl;

	cout << "\nCopying tree... " << endl;
	copyTree(root, newRoot);
//	newRoot = copyTree(root, newRoot);

	cout << "\nThe new tree data is : " << endl;
    	display(newRoot);

	cout << "\n===== " << endl;

	display(root);

//	destroy(newRoot);
	destroy(root);
	return 0;
}
