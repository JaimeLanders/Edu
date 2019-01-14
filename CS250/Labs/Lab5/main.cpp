/*
 *
 * NAME:        Jaime Landers
 * CRN:         43753 
 * ASSIGNMENT:  Lab 5
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

int gcd (long long x, long long y, long long * q, long long * r)
{
    long long a = x;
    long long b = y;
    long long result = 0;

    *q = 0;
    r = &y;

    while (b != 0)
    {
        div(a,b,q,r);
        a = b;
        b = *r;
    }

    result = a;

    return result;
}

int main ()
{
    long long cd = 0;
    long long quotient = 0;
    long long remainder = 0;
    long long * q  = new long long;
    long long * r  = new long long;
    long long x = 0;
    long long y = 0;

    std::cout << "\nWelcome to lab 5! \n" << std::endl;

    for (int i = 0; i < 4; i++)
    {

        while (x <= 1)
        {
            std::cout << "Enter a number (x) between 1 and 2^63 (exclusive): ";
            std::cin >> x;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        }
        while (y < 1 || y > x)
        {
            std::cout << "Enter a number (y) between 1 and " << x << " (inclusive): ";
            std::cin >> y;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        }

        div(x, y, q, r);
        quotient = *q;
        remainder = *r;
        cd = gcd(x, y, q, r);

        std::cout << "The quotient and remainder of " << x << " and " << y << " is ";
        std::cout << quotient << " and " << remainder << std::endl;
        std::cout << "The gcd of " << x << " and " << y << " is " << cd << std::endl;
        std::cout << "\n";

        x = 0;
        y = 0;

    }

    delete q;
    delete r;

    return 0;
}
