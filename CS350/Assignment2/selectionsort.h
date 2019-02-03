#include <iostream>

void selectionSort(int a[], int n)
{
//    std::cout << "\nselectionSort " << std::endl;
//    std::cout << "n = " << n << std::endl; 

    for (int i = 0; i <=  n - 2; i++)
    {
//        std::cout << "a[" << n << "] = " << a[i] << std::endl; 
        int min = i;
        
        for(int j = i +1; j <= n - 1; j++)
        {
            if(a[j] < a[min])
            {
                min = j;
            }
        }

        int temp = a[min];
        a[min] = a[i];
        a[i] = temp;
    }
}
