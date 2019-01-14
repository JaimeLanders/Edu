#include <iostream>
// include the correct include file
#include <list>

using namespace std;

int main()
{
    // list declaration goes here
    list<int> nList;
    
    int prev = 0;
    int curr = 1;
    while (curr < 1000) {

	// add the value to the list here
    nList.push_back(curr);
	
	int newfib = curr + prev;
	prev = curr;
	curr = newfib;
    }

    // add code to iterate through the list and print all values here
    for (list<int>::iterator it2 = nList.begin(); it2 != nList.end(); ++it2 )
    {
        cout << *it2 << endl;
    }
}
