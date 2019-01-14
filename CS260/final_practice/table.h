#ifndef TABLE_H
#define TABLE_H
//table.h
#include <iostream>
#include <cstring>
#include <cctype>
using namespace std;

struct node
{
    int data;
    node * left;
    node * right;
};

void build(node * & root);  //supplied
void display(node *  root); //supplied
void destroy(node * & root); //supplied

/* ************** PLACE YOUR PROTOTYPE HERE ***************** */

bool addNode(node * root, int dataIn);
node* addNodeHelper(node *& nodeIn, int dataIn);

node* deleteNode(node *& nodeIn);

void destroyTree(node * root);

bool findValue(node * root, int dataIn);
bool findValueHelper(node * nodeIn, int dataIn);

int height(node * root);
int heightHelper(node * nodeIn);

void inOrder(node * root);
void inOrderHelper(node * nodeIn);

int numberOfNodes(node * root);
int numberOfNodesHelper(node * nodeIn, int& nodeCountIn);

void preOrder(node * root);
void preOrderHelper(node * nodeIn);

void postOrder(node * root);
void postOrderHelper(node * nodeIn);

bool removeLargest(node *& root);
bool removeLargestHelper(node *& nodeIn);

bool removeValue(node *& root, int numIn);
bool removeValueHelper(node *& nodeIn, int numIn);

bool removeSmallest(node *& root);
bool removeSmallestHelper(node *& nodeIn);

int removeEven(node *& root);
int removeEvenHelper(node *& nodeIn, int& nodesRemovedIn);

int removeOdd(node *& root);
int removeOddHelper(node *& nodeIn, int& nodesRemovedIn);

int sum(node * root);
int sumHelper(node * nodeIn, int sumIn);

#endif
