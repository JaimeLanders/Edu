/*
 *
 * NAME:        Jaime Landers
 * CRN:         43753 
 * ASSIGNMENT:  Lab 6
 * SOURCES:     None
 *
*/

#include <iostream>
#include <limits>

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
    long long * q  = new long long;
    long long * r  = new long long;
    long long i = 0;
    long long j = n;

    while (i == 0 || j != 0)
    {

       div(j,2, q, r); 

        m[i] = *r;
        j = *q;
        i = i + 1;
    }
    
    delete q;
    delete r;

    return;
}

int main ()
{

    std::cout << "\nWelcome to lab 6! \n" << std::endl;

    for (int i = 0; i < 4; i++)
    {

        long long x = 0;
        int bits [64] = {0};
        bool leadBit = false;

        while (x <= 1)
        {
            std::cout << "Enter a positive integer: ";
            std::cin >> x;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        }

        decToBi(x, bits);

        std::cout << x << " in binary is ";

        for (int i = 63; i >= 0; i--)
        {
            if (bits[i] == 1)
                leadBit = true;

            if (leadBit == true)
            {
                if ((i + 1) % 4 == 0)
                    std::cout << " ";

                std::cout << bits[i];
            }
        }

        std::cout << "\n";

    } // for loop

    return 0;
}
