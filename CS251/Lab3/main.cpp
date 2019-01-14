/*
 * NAME:        Jaime Landers
 * CRN:         13759          
 * ASSIGNMENT:  Lab 3
 * SOURCES:     None
 *
*/

#include <fstream>
#include <iostream>
#include <list>

void div (long long x, long long y, long long * q, long long * r)
{
    long long quotient = 0;
    long long remainder = x;

    while (remainder >= y)
    {
        remainder = remainder - y;
        quotient = quotient + 1;
    }

    *q = quotient;
    *r = remainder;

    return;
}

void decToBi (long long n, int m[])
{
    long long * s  = new long long;
    long long * t  = new long long;
    long long i = 0;
    long long j = n;

    while (i == 0 || j != 0)
    {
       div(j,2, s, t); 

       m[i] = *t;
       j = *s;
       i = i + 1;
    }
    
    delete s;
    delete t;

    return;
} 

int residue (int x, int a, int n)
{

    long long residue = 0;
    int res[100];
    int rn = 0;
    int bits [64] = {0};
    bool leadBit = false;

    long long *q = new long long;
    long long *r = new long long;

    *r = x;

    // Convert exponent (a) to binary
    decToBi(a, bits);

    // Calculate residues for all powers of 2
    int a_i = 0;

    for (int i = 0; i < 63; i++)
    {
        a_i = 1;

        if (bits[i] == 1)
        {
            leadBit = true;
        }

        if (leadBit == true)
        {

            if (bits[i] == 1)
            {
                for (int j = 0; j < i; j++)
                {
                    a_i *= 2;
                
                }

                *r = x;

                for (int j = 1; j <= a_i; j *= 2)
                {
                    if (j != 1)
                    {
                        *r *= *r;
                    }

                    div(*r, n, q, r);
                }

                res[rn] = *r;
                rn++;

            }
        }
    }

    // Final step, calculate final residue
    residue = 1;
    for (int i = 0; i < rn; i++)
    {
        residue *= res[i];
    }

    residue = residue % n; // For speeding up operation
//    div(residue,n,q,r); // Slooooooow...
//    residue = *r;
    leadBit = false;

    delete q;
    delete r;

    return residue;
}

int main ()
{
    std::string fileName;
    std::list<int> dataList;
    std::list<int>::iterator it;

    int n = 323; // pq
    int d = 107;

    std::cout << "Welcome to Lab 2 " << std::endl;

    // Prompt user for file to open
    std::cout << "\nFile location to read: ";
    std::cin >> fileName;

    // Open file 
    bool fileOpen = false;

    std::ifstream inFile;
    inFile.open(fileName);

    if (inFile.is_open())
    {
        std::cout << "\n" << fileName << " opened " << std::endl;
        fileOpen = true;
    }
    else
    {
        std::cout << "\n" << "Could not open " << fileName << std::endl;
        return 0;
    }

    // Read data and add to list
    int newString;

    while (inFile >> newString)
    {
        it = dataList.begin();

        dataList.push_back (newString);
    }

    // Close file
    inFile.close();

    // Decrypt message
    
    std::cout << "\nDecrypting message, please wait... " << std::endl;
    
    std::cout << "\nThe secret message is: ";

    for (it = dataList.begin(); it != dataList.end(); it++)
    {
        char M = 96;

        int C = *it;

        M += residue(C, d, n);
          
        if (M != 123)
        {
            std::cout << M;
        }
        else
        {
            std::cout << " ";
        }
    }

    std::cout << "\n";

    return 0;
}
