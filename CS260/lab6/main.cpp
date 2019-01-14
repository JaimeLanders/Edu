#include "table.h"

#include <iostream>

using namespace std;

int main()
{
    node * root = NULL;
    build(root);
    display(root);

    /*  PLACE YOUR FUNCTION CALL HERE */
    cout << "\nThe number of items in the tree: " << count(root) << endl;
    cout << "\nThe sum of all data is : " << sum(root) << endl;
    cout << "\nThe height of the tree is: " << height(root) << endl;

    display(root);
    destroy(root);
    return 0;
}
