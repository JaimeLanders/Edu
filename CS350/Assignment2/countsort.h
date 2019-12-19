#include <iostream>

void countSort(int a[], int s[], int n, int l, int u)
//int* countSort(int a[], int s[], int n, int l, int u)
{
/*    std::cout << "\ncountSort " << std::endl;
    std::cout << "n = " << n << std::endl;
    std::cout << "l = " << l << std::endl;
    std::cout << "u = " << u << std::endl;
    std::cout << "u - l = " << u - l << std::endl;
*/
    int ul = u - l;
//    std::cout << "ul = " << ul << std::endl;

    int d[ul + 1];// = {};
//    int d[l - u + 1];// = {};
//    int * s = new int[n];
//    static int s[] = {};

//    std::cout << "====="<< std::endl;
    for (int j = 0; j <= ul ; j++) // Initialize frequencies
//    for (int j = 0; j <= (u - l); j++) // Initialize frequencies
    {
//        std::cout << "j = " << j << std::endl;

        d[j] = 0;
    }
//    std::cout << "====="<< std::endl;

    for (int i = 0; i < n; i++) // Compute frequencies
    {
//        std::cout << "i = " << i << std::endl;
//        std::cout << "a[i] - l = " << a[i] - l << std::endl;

        d[a[i]-l] += 1;
//        std::cout << "a[" << a[i] - l << "] = " << d[a[i]-l] << std::endl;
    }
//    std::cout << "====="<< std::endl;
    for (int j = 1; j <= u - l; j++) // Reuse for distribtution
    {
//        std::cout << "j = " << j << std::endl;

        d[j] = d[j - 1] + d[j];
//        std::cout << "d[" << j << "] = " << d[j] << std::endl;

    }

//    std::cout << "====="<< std::endl;
    for (int i = n - 1; i >= 0; i--)
    {
//        std::cout << "i = " << i << std::endl;

        int j = a[i] - l;
//        std::cout << "j = " << j << std::endl;
//        std::cout << "d[" << j << "] = " << d[j] << std::endl; 
//        std::cout << "d[" << j << "] - 1 = " << d[j] -1 << std::endl; 

//        std::cout << "n = " << n << std::endl;

//        std::cout << "bp1 " << std::endl;
//        std::cout << "a[" << i << "] = " << a[i] << std::endl;
//        std::cout << "s[898] = " << s[898] << std::endl; 
        s[d[j] - 1] = a[i]; // Seg faults when n >= 899 
//        std::cout << "bp2 " << std::endl;
//        std::cout << "s[" << d[j] - 1 << "] = " << s[d[j] - 1] << std::endl; 

        d[j] -= 1;
//        std::cout << "d[" << j << "] = " << d[j] << std::endl;
    }
    
//    std::cout << "check " << std::endl;

//    return s;
}
