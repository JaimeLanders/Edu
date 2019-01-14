/*
 *
 * NAME:        Jaime Landers
 * CRN:         43753 
 * ASSIGNMENT:  Lab 7
 * SOURCES:     None
 *
*/

#include <cmath>
#include <iostream>
#include <limits>
#include <string>

float negFactor(float a, float b, float c)
{

    bool debug = false;
//    bool debug = true;

    float result = 0.0;

    if(debug == true)
    {
        std::cout << "\nnegFactor" << std::endl;
        std::cout << "a = " << a << std::endl;
        std::cout << "b = " << b << std::endl;
        std::cout << "c = " << c << std::endl;
    }

    result = (-b - (sqrt((b * b) - (4 * a * c)))) / (2 * a); 

    return result;
}

float posFactor(float a, float b, float c)
{

    bool debug = false;
//    bool debug = true;

    float result = 0.0;

    if(debug == true)
    {
        std::cout << "\nposFactor" << std::endl;
        std::cout << "a = " << a << std::endl;
        std::cout << "b = " << b << std::endl;
        std::cout << "c = " << c << std::endl;
    }

    result = (-b + sqrt((b * b) - (4 * a * c))) / (2 * a); 

    return result;
}

int main ()
{
    bool debug = false;
//    bool debug = true;

    std::cout << "\nWelcome to lab 7!" << std::endl;

    for (int i = 0; i < 4; i++)
    {

        bool validInput = false;
        float a = 0.0;
        float b = 0.0;
        float c = 0.0;
        float d = 0.0;
        float a_0 = 0.0;
        float a_1 = 0.0;
        float r = 0.0;
        float s = 0.0;
        float a_k [6];// = 0;
        std::string userIn;

        std::cout << "\n=====" << std::endl;
        
        while (userIn.empty() || validInput == false)
        {
            std::cout << "\nEnter a number (A): ";
            std::cin >> userIn;
            std::cin.clear();

            if(debug == true)
                std::cout << "userIn = " << userIn << std::endl;

            validInput = (userIn.find_last_not_of("0123456789-") == std::string::npos);

            if (validInput == false)
                std::cout << "Not a valid number, try again... " << std::endl;

        }

        a = std::stof (userIn);

        if(debug == true)
            std::cout << "a = " << a << std::endl;

        userIn.clear();
        validInput = false;

        while (userIn.empty() || validInput == false)
        {
            std::cout << "Enter a number (B) other than zero : ";
            std::cin >> userIn;
            std::cin.clear();

            if(debug == true)
                std::cout << "userIn = " << userIn << std::endl;

            validInput = (userIn.find_last_not_of("0123456789-") == std::string::npos);

            if(validInput == true)
            {
                if (std::stof (userIn) == 0)
                {
                    std::cout << "B cannot be 0, try again... \n" << std::endl;
                    validInput = false;
                } 
            }
            else
                std::cout << "Not a valid number, try again... \n" << std::endl;

        }

        b = std::stof (userIn);

        if(debug == true)
            std::cout << "b = " << b << std::endl;

        userIn.clear();
        validInput = false;

        while (userIn.empty() || validInput == false)
        {
            std::cout << "Enter a number (a_0): ";
            std::cin >> userIn;
            std::cin.clear();

            if(debug == true)
                std::cout << "userIn = " << userIn << std::endl;

            validInput = (userIn.find_last_not_of("0123456789-") == std::string::npos);

            if (validInput == false)
                std::cout << "Not a valid number, try again... \n" << std::endl;

        }

        a_0 = std::stof (userIn);

        a_k[0] = a_0;

        if(debug == true)
            std::cout << "a_k[0] = " << a_k[0] << std::endl;

        userIn.clear();
        validInput = false;

        while (userIn.empty() || validInput == false)
        {
            std::cout << "Enter a number (a_1): ";
            std::cin >> userIn;
            std::cin.clear();

            if(debug == true)
                std::cout << "userIn = " << userIn << std::endl;

            validInput = (userIn.find_last_not_of("0123456789-") == std::string::npos);

            if (validInput == false)
                std::cout << "Not a valid number, try again... \n" << std::endl;

        }

        a_1 = std::stof (userIn);

        a_k[1] = a_1;

        if(debug == true)
            std::cout << "a_k[1] = " << a_k[1] << std::endl;

        userIn.clear();
        validInput = false;

        std::cout << "\nFormula: a_k = (" << a << ")a_(k-1) + ("<< b << ")a_(k-2)" << std::endl;

        std::cout << "\nCharacteristic Equation = t^2 - (" << a << ")t - ("<< b << ") = 0 " << std::endl;


        if(debug == true)
            std::cout << "test = " << ((a * a) - (4  * -b)) << std::endl;
//break
        if (((a * a) - (4  * -b)) < 0) // Complex root case
        {
            std::cout << "\nComplex root detected " << std::endl;

//            return 0;
        }
        else
        {
            
            r = posFactor(1, -a, -b);

            if (debug == true)
                std::cout << "r = " << r << std::endl;

            s = negFactor(1, -a, -b);

            if (debug == true)
                std::cout << "s = " << s << std::endl;
            if (r != s) // Distinct roots case
            {
                c = (a_1 - (s * a_0)) / (r - s); 
                
                if (debug == true)
                    std::cout << "c = " << c << std::endl;

                d = (a_1 - (r * a_0)) / (-r + s); 

                if (debug == true)
                    std::cout << "d = " << d << std::endl;

                if (c != 0 && d != 0)
                    std::cout << "\nDistinct-Roots Equation: b_n = (" << c << ")(" << r << ")^n + (" << d << ")(" << s << ")^n" << std::endl; 
                else if (c != 0)
                    std::cout << "\nDistinct-Roots Equation: b_n = (" << c << ")(" << r << ")^n" << std::endl; 

                else if (d != 0)
                    std::cout << "\nDistinct-Roots Equation: b_n = (" << d << ")(" << s << ")^n" << std::endl; 
                else
                    std::cout << "\nDistinct-Roots Equation: 0" << std::endl;
            }
            else if (r == s) // Single-root case
            {
                c = a_0;
                
                if (debug == true)
                    std::cout << "c = " << c << std::endl;

                d = (a_1-(c*r)) / s; 

                if (debug == true)
                    std::cout << "d = " << d << std::endl;

                if (c != 0 && d != 0)
                    std::cout << "\nSingle-Roots Equation: b_n = (" << c << ")(" << r << ")^n + (" << d << ")(n)(" << s << ")^n" << std::endl; 
                else if (c != 0)
                std::cout << "\nSingle-Roots Equation: b_n = (" << c << ")(" << r << ")^n " << std::endl; 
                else if (d != 0)
                    std::cout << "\nSingle-Roots Equation: b_n = (" << d << ")(n)(" << s << ")^n" << std::endl; 
                else
                    std::cout << "0" << std::endl;

            }

            for (int k = 2; k <= 6; k++)
            {
                if (debug == true)
                    std::cout << "k = " << k << std::endl;

                a_k[k] = (a * a_k[k - 1]) + (b * a_k[k - 2]);

                if (debug == true)
                    std::cout << "a_k[" << k << "] = " << a_k[k] << std::endl;
            }

            std::cout << "\nThe first 6 terms of the sequence are: ";

            for (int k = 0; k <= 6; k++)
            {
                if (debug == true)
                    std::cout << "k = " << k << std::endl;

                std::cout << a_k[k];

                if (k < 6)
                    std::cout << ", ";

                if (debug == true)
                    std::cout << "a_k[" << k << "] = " << a_k[k] << std::endl;
            }

            std::cout << "\n";

        }

    } // for loop

    return 0;
}
