#include <algorithm>
#include <chrono>
#include <fstream>
#include <iostream>
#include "copyarray.h"
#include "countsort.h"
#include "mergesort.h"
#include "printarray.h"
#include "rand.h"
#include "reversearray.h"
#include "selectionsort.h"

int main()
{
    std::cout << "Welcome to Assignment 2 " << std::endl;

    std::ofstream file;
    file.open("data.csv");
    file << "Sort Algorithm, Array Type, Time (s) "<< std::endl;  

    float timeSec = 0.0;

    int nMax = 250000; // Number of elements
//    int n = 250000; // Number of elements
//    int n = 523496; // Max for Merge Sort 
////    int n = 523496; // Max for Merge Sort 
//    n = rand(0, n); // Randomize n 

//    int a[] = {13,11,12,13,12,12}; // Example from book 
//    int a[] = {4,1,5,4,5,1,0}; 
//    int a[nMax];// = {0};
//    int a[n];// = {0};

    for(int n = 50000 ; n <= nMax;  n += 50000)
    {

    std::cout << "n = " << n << std::endl;
    
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
    timeSec = (std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()) / 1000.0;
    std::cout << "The array took " << timeSec << " seconds to initialize. "<<  std::endl;

//    std::cout << "\nArray before sorting: " << std::endl;
//    printArray(a, 0, n);

    int temp[n]; // Tempoary array to copy a to

    //Selection Sort
    
    copyArray(a, temp, 0, n, 0, n); // Initialize temp array 

    std::cout << "\nPerforming selection sort on the random array... " << std::endl;
    start = std::chrono::steady_clock::now(); 

    selectionSort(temp, n);

    end = std::chrono::steady_clock::now(); 
    timeSec = (std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()) / 1000.0;

    file << "Selection, Random, " << timeSec << "," << n <<  std::endl;  
    std::cout << "The random array took " << timeSec << " seconds to selection sort. "<<  std::endl;

    std::cout << "\nPerforming selection sort on the sorted array... " << std::endl;
    start = std::chrono::steady_clock::now(); 

    selectionSort(temp, n);

    end = std::chrono::steady_clock::now(); 
    timeSec = (std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()) / 1000.0;

    file << "Selection, Sorted, " << timeSec << "," << n <<  std::endl;  
    std::cout << "The sorted array took " << timeSec << " seconds to selection sort. "<<  std::endl;

    reverseArray(a, temp, 0, n, 0, n); // Reverse sort the temp array 

    std::cout << "\nPerforming selection sort on the reverse sorted array... " << std::endl;
    start = std::chrono::steady_clock::now(); 

    selectionSort(temp, n);

    end = std::chrono::steady_clock::now(); 
    timeSec = (std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()) / 1000.0;

    file << "Selection, Reverse, " << timeSec << "," << n <<  std::endl;  
    std::cout << "The reverse sorted array took " << timeSec << " seconds to selection sort. "<<  std::endl;

//    std::cout << "\nArray after selection sorting: " << std::endl;
//    printArray(temp, 0, n);

    // Merge Sort
/*    
    copyArray(a, temp, 0, n, 0, n); // Reset temp array 
//    std::cout << "\nTemp array after reset: " << std::endl;
//    printArray(temp, 0, n);

    std::cout << "\nPerforming merge sort on the random array... " << std::endl;

    start = std::chrono::steady_clock::now(); 

    mergeSort(temp, n);

    end = std::chrono::steady_clock::now(); 
    timeSec = (std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()) / 1000.0;

    file << "Merge, Random, " << timeSec << "," << n <<  std::endl;  
    std::cout << "The random array took " << timeSec << " seconds to merge sort. "<<  std::endl;

    std::cout << "\nPerforming merge sort on the sorted array... " << std::endl;

    start = std::chrono::steady_clock::now(); 

    mergeSort(temp, n);

    end = std::chrono::steady_clock::now(); 
    timeSec = (std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()) / 1000.0;

    file << "Merge, Sorted, " << timeSec << "," << n <<  std::endl;  
    std::cout << "The sorted array took " << timeSec << " seconds to merge sort. "<<  std::endl;

    reverseArray(a, temp, 0, n, 0, n); // Reverse sort the temp array 

    std::cout << "\nPerforming merge sort on the reverse sorted array... " << std::endl;

    start = std::chrono::steady_clock::now(); 

    mergeSort(temp, n);

    end = std::chrono::steady_clock::now(); 
    timeSec = (std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()) / 1000.0;

    file << "Merge, Reverse, " << timeSec << "," << n <<  std::endl;  
    std::cout << "The reverse sorted array took " << timeSec << " seconds to merge sort. "<<  std::endl;
//    std::cout << "\nArray after merge sorting: " << std::endl;
//    printArray(temp, 0, n);

    // Distribution Count Sort
  
    copyArray(a, temp, 0, n, 0, n); // Reset temp array 
//    std::cout << "\nTemp array after reset: " << std::endl;
//    printArray(temp, 0, n);

    int min = *std::min_element(temp, temp + n);
    int max = *std::max_element(temp, temp + n);
//    std::cout << "min = " << min << std::endl;
//    std::cout << "max = " << max << std::endl;

    std::cout << "\nPerforming count sort on the random array... " << std::endl;
    start = std::chrono::steady_clock::now(); 

    countSort(a, temp, n, min, max); // Temp

    end = std::chrono::steady_clock::now(); 
    timeSec = (std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()) / 1000.0;
//    timeSec = (std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()) / 1000.0;

    file << "Count, Random, " << timeSec << "," << n <<  std::endl;  
    std::cout << "The array took " << timeSec << " seconds to count sort. "<<  std::endl;

    std::cout << "\nPerforming count sort on the sorted array... " << std::endl;
    start = std::chrono::steady_clock::now(); 

    countSort(a, temp, n, min, max); // Temp

    end = std::chrono::steady_clock::now(); 
    timeSec = (std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count());
//    timeSec = (std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()) / 1000.0;

    file << "Count, Sorted, " << timeSec << "," << n <<  std::endl;  
    std::cout << "The array took " << timeSec << " seconds to count sort. "<<  std::endl;

    reverseArray(a, temp, 0, n, 0, n); // Reverse sort the temp array 

    std::cout << "\nPerforming count sort on the reverse sorted array... " << std::endl;
    start = std::chrono::steady_clock::now(); 

    countSort(a, temp, n, min, max); // Temp

    end = std::chrono::steady_clock::now(); 
    timeSec = (std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count());
//    timeSec = (std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()) / 1000.0;

    file << "Count, Reverse, " << timeSec << "," << n <<  std::endl;  
    std::cout << "The array took " << timeSec << " seconds to count sort. "<<  std::endl;

//    std::cout << "\nArray after count sorting: " << std::endl;
//    printArray(temp, 0, n);
*/
    } // close for loop

    file.close();

    return 0;
}

/*void sort(int alg, int a[], int min, int max, ofstream file)
{
    if(alg == 1)
    {
        auto start = std::chrono::steady_clock::now(); 

        selectionSort(a, max);

        auto end = std::chrono::steady_clock::now(); 
        float timeSec = (std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()) / 1000.0;

        file << "Selection, Random, " << timeSec << std::endl;  
    }
}
*/
