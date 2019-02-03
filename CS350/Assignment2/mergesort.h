#include <iostream>
#include <cmath> 

void merge(int b[], int c[], int a[], int p, int q)
{
//    std::cout << "merge " << std::endl;
    int i = 0, j = 0 , k = 0;

    while (i < p and j < q) 
    {
//        std::cout << "i = " << i << std::endl;
//        std::cout << "j = " << j << std::endl;

        if (b[i] <= c[j])
        {
            a[k] = b[i];
            i += 1; 
        }
        else
        {
            a[k] = c[j];
            j += 1;
        }
        k += 1;
//        std::cout << "k = " << k << std::endl;
    }
    if (i == p)
    {
//        std::cout << "i == p = " << i << std::endl;
        copyArray(c, a, j, q, k, p + q);
    }
    else 
    { 
//        std::cout << "i != p " << std::endl;
        copyArray(b, a, i, p, k, p + q);
    }
}

void mergeSort(int a[], int n)
{
//    std::cout << "\nmergeSort " << std::endl;
//    std::cout << "n = " << n << std::endl;
//    std::cout << "a[0] = " << a[0] << std::endl;

    if (n > 1)
    {
        int bSize = int(std::floor(n/2.0));
        int cSize = std::ceil(n/2.0);

//        std::cout << "bSize = " << bSize << std::endl;
//        std::cout << "cSize = " << cSize << std::endl;

        int b[bSize];
        int c[cSize];

        copyArray(a, b, 0, bSize, 0, bSize);
        copyArray(a, c, bSize, n, 0, cSize);
        mergeSort(b, bSize);
        mergeSort(c, cSize);
        merge(b, c, a, bSize, cSize); 
    }
}
