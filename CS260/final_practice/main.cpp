#include "table.h"

#include <iostream>

using namespace std;

int main()
{
	node * root = NULL;

	bool nodeAdded = false;  
	bool nodeFound = false;  
	bool nodeRemoved = false;  
	int addData = 157;
	int nodeNum = 0;
	int nodeSum = 0;
	int treeHeight = 0;

	build(root);

	cout << "\n===== " << endl;

	display(root);

	cout << "\n===== " << endl;

	/*  PLACE YOUR FUNCTION CALL HERE */

	cout << "In-order traversal: " << endl;
	inOrder(root);

	cout << "\n===== " << endl;

	cout << "Pre-order traversal: " << endl;
	preOrder(root);

	cout << "\n===== " << endl;

	cout << "Post-order traversal: " << endl;
	postOrder(root);

	cout << "\n===== " << endl;

	nodeAdded = addNode(root, addData);

	if (nodeAdded == true)
	    cout << "\n" << addData << " added to the BST " << endl;
	else
	    cout << "\nCould not add " << addData << " to the BST... " <<  endl;

	cout << "\n===== " << endl;

	nodeFound = findValue(root, addData);	

	if (nodeFound == true)
		cout << "\n" << addData << " found " << endl;
	else
		cout << "\n" << addData << " not found " << endl;

	cout << "\n===== " << endl;

	nodeNum = numberOfNodes(root);
	cout << "\nThe number of nodes is : " << nodeNum << endl;

	cout << "\n===== " << endl;

	nodeSum = sum(root);
	cout << "\nThe sum of all data is: " << nodeSum << endl;

	cout << "\n===== " << endl;

	treeHeight = height (root);
	cout << "\nThe height of the tree is : " << treeHeight << endl;

	cout << "\n===== " << endl;

	nodeRemoved = removeValue(root, addData);

	if (nodeRemoved == true)
		cout << "\n" << addData << " removed " << endl;
	else
		cout << "\nUnable to remove " << addData << "... " << endl;

	cout << "\n===== " << endl;

	nodeRemoved = removeSmallest(root);

	if (nodeRemoved == true)
		cout << "\nSmallest node removed " << endl;
	else
		cout << "\nNothing to remove... " << endl;

	cout << "\n===== " << endl;

	nodeRemoved = removeLargest(root);

	if (nodeRemoved == true)
		cout << "\nLargest node removed " << endl;
	else
		cout << "\nNothing to remove... " << endl;

	cout << "\n===== " << endl;

	nodeNum = removeEven(root);
	cout << "\nThe number of even nodes removed is : " << nodeNum << endl;

	cout << "\n===== " << endl;

	nodeNum = removeOdd(root);
	cout << "\nThe number of odd nodes removed is : " << nodeNum << endl;

	cout << "\n===== " << endl;

	display(root);

	cout << "\n===== " << endl;

//	destroy(root);

	destroyTree(root);

	return 0;
}
