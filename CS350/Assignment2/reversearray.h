#include <iostream>

void reverseArray(int a[], int b[], int aMin, int aMax, int bMin, int bMax)
{
//    std::cout << "reverseArray " << std::endl;

    int j = bMin;

    for(int i = aMax - 1; i >= aMin; i--)
    {
//        std::cout << "i = " << i << std::endl;
//        std::cout << "j = " << j << std::endl;
//        std::cout << "a[" << i << "] = " << b[i] << std::endl;

        b[j] = a[i];
//        std::cout << "b[" << j << "] = " << b[j] << std::endl;

        if(j < bMax)
        {
            j += 1;
//            std::cout << "j = " << j << std::endl;
        }
    }
}
