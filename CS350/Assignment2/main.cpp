#include <algorithm>
#include <chrono>
#include <fstream>
#include <iostream>
#include "copyarray.h"
#include "countsort.h"
#include "mergesort.h"
#include "printarray.h"
#include "rand.h"
#include "selectionsort.h"

int main()
{
    std::cout << "Welcome to Assignment 2 " << std::endl;

    std::ofstream file;
    file.open("data.csv");
    file << "Sort Algorithm, Time (s) "<< std::endl;  

    float timeSec = 0.0;

    int n = 6; // Number of elements
//    n = rand(0, n); // Randomize n 
    std::cout << "n = " << n << std::endl;

//    int a[] = {13,11,12,13,12,12}; // Example from book 
//    int a[] = {4,1,5,4,5,1,0}; 
    int a[n];// = {0};

    auto start = std::chrono::steady_clock::now(); 

    std::cout << "\nInitializing array of " << n <<" random elements... " << std::endl;
    for(int i = 0; i < n; i++)
    {
//        std::cout << "i = " << i << std::endl;
//        a[i] = 0;
//        a[i] = n - i; // Worst case
        a[i] = rand(0, n);
    }

    auto end = std::chrono::steady_clock::now(); 
/*    timeSec = (std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()) / 1000.0;
    std::cout << "The array took " << timeSec << " seconds to initialize. "<<  std::endl;
*/
    std::cout << "\nArray before sorting: " << std::endl;
    printArray(a, 0, n);

    int temp[n]; // Tempoary array to copy a to

    //Selection Sort
/*   copyArray(a, temp, 0, n, 0, n); 

    std::cout << "\nPerforming selection sort on the array... " << std::endl;
    start = std::chrono::steady_clock::now(); 
    selectionSort(temp, n);

    end = std::chrono::steady_clock::now(); 
    timeSec = (std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()) / 1000.0;
    file << "Selection, " << timeSec << std::endl;  
    std::cout << "The array took " << timeSec << " seconds to selection sort. "<<  std::endl;

//    std::cout << "\nArray after selection sorting: " << std::endl;
//    printArray(temp, 0, n);

    // Merge Sort
    copyArray(a, temp, 0, n, 0, n); 
//    std::cout << "\nTemp array after reset: " << std::endl;
//    printArray(temp, 0, n);

    std::cout << "\nPerforming merge sort on the array... " << std::endl;
    start = std::chrono::steady_clock::now(); 
    mergeSort(temp, n);
    end = std::chrono::steady_clock::now(); 
    timeSec = (std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()) / 1000.0;
    file << "Merge, " << timeSec << std::endl;  
    std::cout << "The array took " << timeSec << " seconds to merge sort. "<<  std::endl;

    std::cout << "\nArray after merge sorting: " << std::endl;
    printArray(temp, 0, n);
*/
    // Count Sort
     copyArray(a, temp, 0, n, 0, n); 
    std::cout << "\nTemp array after reset: " << std::endl;
    printArray(temp, 0, n);

    std::cout << "\nPerforming count sort on the array... " << std::endl;
    start = std::chrono::steady_clock::now(); 

    int min = *std::min_element(temp, temp + n);
    int max = *std::max_element(temp, temp + n); // Temp
    std::cout << "min = " << min << std::endl;
    std::cout << "max = " << max << std::endl;

    int * s = countSort(temp, n, min, max); // Temp
    std::cout << "return check " << std::endl;
    end = std::chrono::steady_clock::now(); 
    timeSec = (std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()) / 1000.0;
    file << "Count, " << timeSec << std::endl;  
    std::cout << "The array took " << timeSec << " seconds to count sort. "<<  std::endl;

    std::cout << "\nArray after count sorting: " << std::endl;
    printArray(s, 0, n);
*/
    file.close();

    return 0;
}
