#include "table.h"

/*
int data;
node * left;
node * right;
*/


int count (node * root)
{
//	cout << "\ncount " << endl;
//	cout << "root = " << root << endl;

	int count = 0;

	if (root)
		return countHelper(root,count);
	else
		return 0;
}

int countHelper (node * nodeIn, int countIn)
{
//	 Recursively compute and return the number of nodes in the bst.

//	cout << "\ncountHelper " << endl;
//	cout << "nodeIn = " << nodeIn << endl;
//	cout << "countIn = " << countIn << endl;

	int count = countIn;
	node * currNode = nodeIn;

	if (nodeIn)
	{
		count++;
		count =	countHelper(nodeIn->left,count);
		count = countHelper(nodeIn->right,count);
	}

	return count;
}

int sum (node * root)
{
//	Recursively compute and return the sum of ints contained in the bst.
//	cout << "\nsum " << endl;
//	cout << "root = " << root << endl;

	if (root)
		sumHelper(root, 0);
	else
		return 0;
}

int sumHelper (node * nodeIn, int sumIn)
{
//	Recursively compute and return the sum of ints contained in the bst.
//	cout << "\nsumHelper " << endl;
//	cout << "nodeIn = " << nodeIn << endl;
//	cout << "sumIn = " << sumIn << endl;

	int sum = sumIn;
	node * currNode = nodeIn;

	if (nodeIn)
	{
		sum = currNode->data + sum;
		sum = sumHelper(nodeIn->left,sum);
		sum = sumHelper(nodeIn->right,sum);
	}

	return sum;
}

int height (node * root)
{
//	cout << "\nheight " << endl;
//     	cout << "root = " << root << endl;
	
	if (root)
		return heightHelper(root);
	else
		return 0;
}

int heightHelper (node * nodeIn)
{
//	Recursively compute and return the height of the bst.
//	cout << "\nheightHelper " << endl;
//     	cout << "nodeIn = " << nodeIn << endl;

	int tHeight = 0;
	
	if (nodeIn)
	{
		int lHeight = heightHelper(nodeIn->left);		
		int rHeight = heightHelper(nodeIn->right);		

		if (lHeight >= rHeight)
		{
			tHeight = lHeight;
		}
		else
		{
			tHeight = rHeight;
		}

	}
	else
		return 0;
	
//	cout << "tHeight = " << tHeight << endl;
	return (tHeight) + 1;
}
