#include "table.h" //Please put the impelementation of the required functions here //

node* copyTree(node * root, node *& newRoot) 
{

//	cout << "\ncopyTree " << endl;
//	cout << "root = " << root << endl;
//	cout << "newRoot = " << newRoot << endl;

	newRoot = copyTreeHelper(root, newRoot);
//	return copyTreeHelper(root, newRoot);
}

node* copyTreeHelper(node * nodeIn, node *& newNodeIn) 
{
//	cout << "\ncopyTreeHelper " << endl;
	cout << "nodeIn = " << nodeIn << endl;
	cout << "nodeIn->data = " << nodeIn->data << endl;
//	cout << "newNodeIn = " << newNodeIn << endl;
	
	if (nodeIn)
	{
		if (nodeIn->left || nodeIn->right)
		{
			cout << "not leaf " << endl;
//			cout << "nodeIn " << endl;
//			cout << "nodeIn->data = " << nodeIn->data << endl;
//			cout << "newNodeIn = " << newNodeIn << endl;
//			cout << "newNodeIn->data " << newNodeIn->data << endl;

			if (nodeIn->left)
//				return copyTree(nodeIn->left, newNodeIn);
				newNodeIn->left = copyTree(nodeIn->left, newNodeIn);

			if (nodeIn->right)
//				return copyTree(nodeIn->right, newNodeIn);
				newNodeIn->right = copyTree(nodeIn->right, newNodeIn);

		}
		else
		{
			cout << "leaf " << endl;

			newNodeIn = new node;//(root->data);
			newNodeIn->data = nodeIn->data;
			cout << "newNodeIn->data = " << newNodeIn->data << endl;

//			if (!newRoot)
//				newRoot = newNodeIn

//			if (nodeIn->left)
//			{ 
//				cout << "left " << endl;
//				newNodeIn->left = copyTree(nodeIn->left, newNodeIn);
//			}
//			else
//				nodeIn->left = NULL;

//			if (nodeIn->right)
//			{
//				cout << "right " << endl;
//				newNodeIn->right = copyTree(nodeIn->right, newNodeIn);
//			}
//			else
//				nodeIn->right = NULL;

//			cout << "check " << endl;
			return newNodeIn;
		}
	}
	else
	{
		return NULL;
	}

//	return newRoot;
//	return newNodeIn;
}

int sum(node * root)
{
//	Recursively compute and return the sum of ints contained in the bst.
//	cout << "\nsum " << endl;
//	cout << "root = " << root << endl;

	if (root)
		sumHelper(root, 0);
	else
		return 0;
}

int sumHelper(node * nodeIn, int sumIn)
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
