//list.h
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

int count(node * root);
int countHelper(node * root, int countIn);
int sum(node * root);
int sumHelper(node * nodeIn, int sumIn);
int height(node * root);
//int heightHelper(node * nodeIn, int heightIn);
//int heightHelper(node * nodeIn, int lHeightIn, int rHeightIn);
int heightHelper(node * nodeIn);
