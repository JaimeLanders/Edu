/*
 * NAME:        Jaime Landers
 * CRN:         13759          
 * ASSIGNMENT:  Lab 5
 * SOURCES:     None
 *
*/

#include <chrono>
#include <ctime>
#include <iostream>
#include <random>
#include <vector>

double horner(int n, double x, std::vector<long int> a)
{
    double polyval = a[0];

    for (int i = 1; i <= n + 1; i++)
    {
        double term = a[i];

        for(int j = 1; j <= i; j++)
        {
            term *= x;
        }

        polyval += term;
    }

    return polyval;
}

double nonHorner(int n, double x, std::vector<long int> a)
{
    double polyval = 0.0;

    for (int i = n + 1; i >= 0; i--)
    {
        double term = 1;

        if(i != 0)
        {
            for(int j = i; j >= 1; j--)
            {
                term *= x;
            }
        }
        term *= a[i];

        polyval += term;
    }

    return polyval;
}

int main ()
{
    std::vector<long int> coeff;
    int degree = 25;
    std::random_device rd;
    std::mt19937 engine(rd());

    std::cout << "Welcome to Lab 5 " << std::endl;

    //1.
    for(int n = 0; n < degree; n++)
    {
        double x = 0.0;
        double polyval = 0.0;

        //2. Generate random polynomial of degree n with integer coefficients between 1 and 99. 
        for(int i = 0; i <= n + 1; i++)
        {
            std::normal_distribution<> dist(50,2);
            long int a = round(dist(engine));

            coeff.push_back(a);

        }

        //3. Generate random real value x in the range -20.00 to 20.00
        std::uniform_real_distribution<> dist(-20,20);

        x = dist(engine);
        
        //4. Evaluate the polynomial using Homers algorithm 11.3.3. 
        std::chrono::time_point<std::chrono::system_clock> begin = std::chrono::system_clock::now();

        polyval = horner(n, x, coeff);

        std::chrono::time_point<std::chrono::system_clock> end  = std::chrono::system_clock::now();

        std::chrono::duration<long double> elapsed_time = end - begin;
        
        //5. Evaluate the polynomial without using Horners        
        std::chrono::time_point<std::chrono::system_clock> begin2 = std::chrono::system_clock::now();

        polyval = nonHorner(n, x, coeff);

        std::chrono::time_point<std::chrono::system_clock> end2  = std::chrono::system_clock::now();

        std::chrono::duration<long double> elapsed_time2 = end2 - begin2;

        //6. Display the polynomial and report the time required to execute step 4.  
        std::cout << "\nCase " << n + 1 << ": ";
        std::cout << "x = " << x << ", ";
        for(int j = 0; j <= n + 1; j++)
        {
            std::cout << "a_" << j << " = " << coeff[j] << ", ";
        }

        std::cout << "\n  Polynomial = ";
        for(int j = n + 1; j >= 0; j--)
        {
            std::cout << coeff[j] << "(" << x  << ")**" << j; 
            if(j != 0)
            {
                std::cout << " + ";
            }

        }
        std::cout << "\n";

        std::cout << "  Horner CPU TIme: " << elapsed_time.count() << std::endl;
        std::cout << "  Non-Horner CPU TIme: " << elapsed_time2.count() << std::endl;
        std::cout << "  P(x) = " << polyval << std::endl;
    }

    return 0;
}
