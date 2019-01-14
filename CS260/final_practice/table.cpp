#include "table.h"

//Please put the impelementation of the required functions here

bool addNode (node * root, int numIn)
{
//	cout << "\naddNode " << endl;

	node * nodeStatus = NULL;

	nodeStatus = addNodeHelper(root, numIn);

	if (nodeStatus)
		return true;
	else
		return false;
}

node* addNodeHelper (node *& nodeIn, int numIn)
{
//	cout << "\naddNodeHelper " << endl;
//	cout << "nodeIn = " << nodeIn << endl;
//	cout << "numIn = " << numIn << endl;

	int compData = 0;

	if (nodeIn)
	{	
//		cout << "nodeIn " << endl;
//		cout << "nodeIn->data = " << nodeIn->data << endl;

		compData = nodeIn->data;
//		cout << "compData = " << compData << endl;

		if (numIn < compData)
		{ 
//			cout << "left " << endl;
			nodeIn->left = addNodeHelper(nodeIn->left, numIn);
		}
		else// if(numIn >= compData)
		{
//			cout << "right " << endl;
			nodeIn->right = addNodeHelper(nodeIn->right, numIn);
		}
	}
	else
	{
//		cout << "leaf " << endl;
		nodeIn = new node;
		nodeIn->data = numIn;
		nodeIn->left = NULL;
		nodeIn->right = NULL;
		return nodeIn;
	}

	return nodeIn;
}

node * deleteNode(node *& nodeIn)
{
//	cout << "\ndeleteNode " << endl;
//	cout << "nodeIn = " << nodeIn << endl;
//	cout << "nodeIn->data = " << nodeIn->data << endl;

	node * temp = NULL;
	
	if (!nodeIn->left && !nodeIn->right)
	{
//		cout << "leaf " << endl;
		delete nodeIn;
		nodeIn = NULL;
		return nodeIn; 
	}
	else if (!nodeIn->right)
	{
//		cout << "left child only " << endl;

		temp = nodeIn;
		nodeIn = nodeIn->left;
		temp->left = NULL;
		delete temp;
		return nodeIn; 
	}
	else if (!nodeIn->left)
	{
//		cout << "right child only "  << endl;

		temp = nodeIn;
		nodeIn = nodeIn->right;
		temp->right = NULL;
		delete temp;
		return nodeIn; 
	}
	else
	{
//		cout << "+++left and right children+++ " << endl;

		node * currNode = nodeIn->right;
		node * prevNode = NULL; 

//		cout << "check " << endl;

		while (currNode->left)
		{
//			cout << "currNode->left " << endl;
			prevNode = currNode;
			currNode = currNode->left;
		}	

		nodeIn->data = currNode->data;
//		cout << "nodeIn->data = currNode->data = " << currNode->data << endl;

		if (!prevNode)
			nodeIn->right = currNode->right;
		else
			prevNode->left = currNode->right;

		currNode->right = NULL;
		delete currNode;
		return nodeIn; 
	}
}

void destroyTree(node * root)
{
//	cout << "\ndestroyTree " << endl;
//	cout << "root = " << root << endl;
	
	if (root)
	{
		destroyTree(root->left);
		destroyTree(root->right);
		delete root;
		root = NULL;
	}
}

bool findValue(node * root, int valueIn)
{
//	cout << "findValue " << endl;
//	cout << "valueIn = " << valueIn << endl;

	return findValueHelper(root,valueIn);
}

bool findValueHelper(node * nodeIn, int valueIn)
{
//	cout << "findValueHelper " << endl;
//	cout << "valueIn = " << valueIn << endl;

	int compData = 0;

	if (nodeIn)
	{
		compData = nodeIn->data;
//		cout << "compData = " << compData << endl;

		if (valueIn < compData)
		{
//			cout << "left " << endl;
			return findValueHelper(nodeIn->left,valueIn);
		}
		else if (valueIn > compData)
		{
//			cout << "right " << endl;
			return findValueHelper(nodeIn->right,valueIn);
		}
		else if (valueIn == compData)
		{
//			cout << "match " << endl;
			return true;
		}
	}
	else
		return false;
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

void inOrder(node * root)
{
//	cout << "inOrder " << endl;

	inOrderHelper(root); 	
}

void inOrderHelper(node * nodeIn)
{
//	cout << "inOrderHelper " << endl;

	if (nodeIn)
	{
		inOrderHelper(nodeIn->left); 	
		cout << nodeIn->data << " ";// << endl;
		inOrderHelper(nodeIn->right); 	
	}
}

int numberOfNodes(node * root)
{
//	cout << "\nnumberOfNode " << endl;
//	cout << "root = " << root << endl;

	int nodeCount = 0;

	return numberOfNodesHelper(root, nodeCount);
}

int numberOfNodesHelper(node * nodeIn, int& nodeCountIn)
{
//	cout << "\nnumberOfNode " << endl;
//	cout << "nodeIn = " << nodeIn << endl;
//	cout << "nodeCountIn = " << nodeCountIn << endl;

	if ( nodeIn)
	{
//		cout << "nodeIn " << endl;

		nodeCountIn++;
//		cout << "nodeCount = " << nodeCount << endl;

		numberOfNodesHelper(nodeIn->left, nodeCountIn);

		numberOfNodesHelper(nodeIn->right, nodeCountIn);
	}

	return nodeCountIn;
}

void postOrder(node * root)
{
//	cout << "postOrder " << endl;

	postOrderHelper(root); 	
}

void postOrderHelper(node * nodeIn)
{
//	cout << "postOrderHelper " << endl;

	if (nodeIn)
	{
		postOrderHelper(nodeIn->left); 	
		postOrderHelper(nodeIn->right); 	
		cout << nodeIn->data << " ";// << endl;
	}
}

void preOrder(node * root)
{
//	cout << "preOrder " << endl;

	preOrderHelper(root); 	
}

void preOrderHelper(node * nodeIn)
{
//	cout << "preOrderHelper " << endl;

	if (nodeIn)
	{
		cout << nodeIn->data << " ";// << endl;
		preOrderHelper(nodeIn->left); 	
		preOrderHelper(nodeIn->right); 	
	}
}

bool removeLargest(node *& root)
{
//	cout << "\nremoveLargest " << endl;
//	cout << "root = " << root << endl;
//	cout << "root->data = " << root->data << endl;

	removeLargestHelper(root);
}

bool removeLargestHelper(node *& nodeIn)
{
//	cout << "\nremoveLargestHelper " << endl;
//	cout << "nodeIn = " << nodeIn << endl;
//	cout << "nodeIn->data = " << nodeIn->data << endl;

	node * temp = NULL;

	if (nodeIn)
	{
		if (nodeIn->right)
		{
//			cout << "left " << endl;
			return removeLargestHelper(nodeIn->right);
		}
		else if (nodeIn->left)
		{
//			cout << "right child "  << endl;
			temp = nodeIn->left;
			nodeIn->data = temp->data;
			nodeIn->right = temp->right;
			nodeIn->left = temp->left;
			delete temp;
			temp = NULL;
			return true;	
		}
		else
		{
//			cout << "leaf " << endl;
			delete nodeIn;
			nodeIn = NULL;
			return true;	
		}
	}
	else
		return false;
//		return NULL;
}

bool removeSmallest(node *& root)
{
//	cout << "\nremoveSmallest " << endl;
//	cout << "root = " << root << endl;
//	cout << "root->data = " << root->data << endl;

	removeSmallestHelper(root);
}

bool removeSmallestHelper(node *& nodeIn)
{
//	cout << "\nremoveSmallestHelper " << endl;
//	cout << "nodeIn = " << nodeIn << endl;
//	cout << "nodeIn->data = " << nodeIn->data << endl;

	node * temp = NULL;

	if (nodeIn)
	{
		if (nodeIn->left)
		{
//			cout << "left " << endl;
			return removeSmallestHelper(nodeIn->left);
		}
		else if (nodeIn->right)
		{
//			cout << "right child "  << endl;
			temp = nodeIn->right;
			nodeIn->data = temp->data;
			nodeIn->left = temp->left;
			nodeIn->right = temp->right;
			delete temp;
			temp = NULL;
			return true;	
		}
		else
		{
//			cout << "leaf " << endl;
			delete nodeIn;
			nodeIn = NULL;
			return true;	
		}
	}
	else
		return false;
//		return NULL;
}

int removeEven(node *& root)
{
//	cout << "\nremoveEven " << endl;
//	cout << "root = " << root << endl;

	int nodesRemoved = 0;

	return removeEvenHelper(root, nodesRemoved);
//	cout << "nodesRemove return = " << nodesRemoved << endl;
}

int removeEvenHelper(node *& nodeIn, int& nodesRemovedIn)
{
//	cout << "\nremoveEvenHelper " << endl;
//	cout << "nodeIn = " << nodeIn << endl;
//	cout << "nodesRemovedIn = " << nodesRemovedIn << endl;

	node * temp = NULL;

	if (nodeIn) 
	{
//		cout << "nodeIn = " << nodeIn << endl;
//		cout << "nodeIn->data = " << nodeIn->data << endl;

		if (nodeIn->left)
		{
//			cout << "Going left " << endl;
			removeEvenHelper(nodeIn->left, nodesRemovedIn);
		}

		if (nodeIn->right)
		{
//			cout << "Going right " << endl;
			removeEvenHelper(nodeIn->right, nodesRemovedIn);
		}

		if (nodeIn->data % 2 == 0)
		{
//			cout << "nodeIn & even " << endl;

			nodesRemovedIn++;
//			cout << "nodesRemovedIn " << nodesRemovedIn << endl;

//			deleteNode(nodeIn);
			nodeIn = deleteNode(nodeIn);
		}
	}

	return nodesRemovedIn;
}

bool removeValue(node *& root, int numIn)
{
//	cout << "\nremoveValue " << endl;
//	cout << "root = " << root << endl;
//	cout << "numIn = " << numIn << endl;

	return removeValueHelper(root, numIn);
}

bool removeValueHelper(node *& nodeIn, int numIn)
{
//	cout << "\nremoveValueHelper " << endl;
//	cout << "nodeIn = " << nodeIn << endl;
//	cout << "numIn = " << numIn << endl;

	int compData = 0;

	if (nodeIn)
	{
//		cout << "nodeIn " << endl;
//		cout << "nodeIn->data = " << nodeIn->data << endl;
		
		compData = nodeIn->data;
//		cout << "compData = " << compData << endl;

		if (numIn == compData)
		{
//			cout << "match " << endl;
			nodeIn = deleteNode(nodeIn);

			return true;
		}
		else if(numIn < compData)
		{
//			cout << "left " << endl;
			return removeValueHelper(nodeIn->left, numIn);
		}
		else
		{
//			cout << "right " << endl;
			return removeValueHelper(nodeIn->right, numIn);
		}
	}
	else
		return false;
}

int removeOdd(node *& root)
{
//	cout << "\nremoveOdd " << endl;
//	cout << "root = " << root << endl;

	int nodesRemoved = 0;

	return removeOddHelper(root, nodesRemoved);
//	cout << "nodesRemove return = " << nodesRemoved << endl;
}

int removeOddHelper(node *& nodeIn, int& nodesRemovedIn)
{
//	cout << "\nremoveOddHelper " << endl;
//	cout << "nodeIn = " << nodeIn << endl;
//	cout << "nodesRemovedIn = " << nodesRemovedIn << endl;

	node * temp = NULL;

	if (nodeIn) 
	{
//		cout << "nodeIn = " << nodeIn << endl;
//		cout << "nodeIn->data = " << nodeIn->data << endl;

		if (nodeIn->left)
		{
//			cout << "Going left " << endl;
			removeOddHelper(nodeIn->left, nodesRemovedIn);
		}

		if (nodeIn->right)
		{
//			cout << "Going right " << endl;
			removeOddHelper(nodeIn->right, nodesRemovedIn);
		}

		if (nodeIn->data % 2 != 0)
		{
//			cout << "nodeIn & odd " << endl;

			nodesRemovedIn++;
//			cout << "nodesRemovedIn " << nodesRemovedIn << endl;

//			deleteNode(nodeIn);
			nodeIn = deleteNode(nodeIn);
		}
	}

	return nodesRemovedIn;
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
