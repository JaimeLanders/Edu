/*
 *
 * NAME:        Jaime Landers
 * CRN:         43753 
 * ASSIGNMENT:  Lab 4
 * SOURCES:     None
 *
*/

#include <iostream>
#include <vector>

int main ()
{
    bool isPrime = true;
    long long n = 0;
    long long userNum = 0;
    std::vector<int> primeFactors;
    std::vector<int>::iterator it;

    std::cout << "Welcome to lab 4! " << std::endl;

    for (int i = 0; i < 4; i++)
    {

        userNum = -1;

        // Ask for user input    
        while (userNum < 0)
        {
            std::cout << "\nInput a positve integer: ";
            std::cin >> userNum;

            if (userNum < 0)
            {
                std::cout << "You did not enter a positive integer, try again... " << std::endl;;
                std::cin.clear();
            }

        }
    
        n = userNum;

        it = primeFactors.begin();

        for (int i = 2; i <= n; i++)
        {
            if (n % i == 0 && (i != n || isPrime == false))
            {
                n = n / i;
                primeFactors.push_back(i);
                isPrime = false;
                i--;
            }
        }

        if (isPrime == true)
            std::cout << "\n" << userNum << " is prime. " << std::endl;
        else
        {
            std::cout << "\n" << userNum << " is not prime. " << std::endl;
            std::cout << "factors: " << std::endl;
            for (it = primeFactors.begin(); it < primeFactors.end(); it++)
                std::cout << *it << std::endl;
        }

        primeFactors.clear();
        isPrime = true;
    }

        return 0;
}
