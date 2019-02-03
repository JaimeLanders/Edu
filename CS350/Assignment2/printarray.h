#include <iostream>

void printArray(int a[], int min, int max)
{
    for(int i = min ; i < max ; i++)
    {
        std::cout << a[i];

        if(i + 1 < max)
           std::cout << ", ";
    }
    std::cout << std::endl;
}
