/*
 * NAME:        Jaime Landers
 * CRN:         13759          
 * ASSIGNMENT:  Lab 2
 * SOURCES:     None
 *
*/

#include <iostream>

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
    int residue = 0;
    int res[100];
    int resCount = 0;
    int bits [64] = {0};

    long long *q = new long long;
    long long *r = new long long;

    *r = x;

    // Convert exponent (a) to binary
    decToBi(a, bits);

    // Calculate residues for all powers of 2
    for (int i = 0; i < 63; i++)
    {
        int a_i = 1;

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

            res[resCount] = *r;
            resCount++;
        }
    }

    // Final step, calculate final residue
    residue = 1;

    for (int i = 0; i < resCount; i++)
    {
        residue *= res[i];
    }

    div(residue,n,q,r);
    residue = *r;

    delete q;
    delete r;

    return residue;
}

int main ()
{
    std::cout << "Welcome to Lab 2 " << std::endl;

    for (int i = 0; i < 4; i++)
    {
        int a = -1; 
        int n = -1;
        int x = -1;

        // Get user input for x, a and n
        while (x < 0)
        {
            std::cout << "\nEnter a positive integer (x >= 0): ";
            std::cin >> x;
            std::cin.clear();
        }
        while (a < 0)
        {
            std::cout << "Enter a positive integer (a >= 0): ";
            std::cin >> a;
            std::cin.clear();
        }
        while (n <= 0)
        {
            std::cout << "Enter a positive integer (n >= 1): ";
            std::cin >> n;
            std::cin.clear();
        }

        std::cout << "\nThe residue of " << x << "^" << a << " mod " << n << " is: " << residue(x, a, n) << std::endl;
        std::cout << "\n=====" << std::endl;;

    } // for loop 

    std::cout << "\n";

    return 0;
}
