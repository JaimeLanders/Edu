/*
 *
 * NAME:        Jaime Landers
 * CRN:         43753 
 * ASSIGNMENT:  Lab 3
 * SOURCES:     None
 *
*/

#include <iostream>
#include <string.h>

int STRINGSIZE = 9;

int * halfSum = new int;
int * halfCarry = new int;
int * carryOut = new int;
int * sumOut = new int;

void halfAdder (int p, int q)// Half adder
{
    *halfSum = (p ^ q);
    *halfCarry = (p & q);
}

void fullAdder (int p, int q, int r)// Full adder
{
    int carry1;
    int carry2;
    int sum1;
    int sum2;

    halfAdder(p, q);
    sum1 = *halfSum;
    carry1 = *halfCarry; 

    halfAdder(sum1, r);
    sum2 = *halfSum;
    carry2 = *halfCarry;

    *carryOut = (carry1 | carry2); 
    *sumOut = sum2; 

    std::cout << "The bits are " << p << " and " << q << ".";
    std::cout << "  The carry in is " << r << ".";
    std::cout << "  The sum is " << *sumOut << ".";
    std::cout << "  The carry out is " << *carryOut << std::endl; 

}

int main ()
{
    std::cout << "Welcome to lab 3!\n " << std::endl;

    for (int l = 0; l < 4; l++)
    {

        char a [STRINGSIZE] = {'0','0','0','0','0','0','0','0','\0'};
        char b [STRINGSIZE] = {'0','0','0','0','0','0','0','0','\0'};
        char sum [STRINGSIZE] = {'0','0','0','0','0','0','0','0','\0'};
        char userIn[30];

        *halfSum = 0;
        *halfCarry = 0;
        *sumOut = 0;
        *carryOut = 0;

        bool valid  = 0;

        while(valid == 0) 
        {
            std::cout << "Enter binary number 1: ";
            std::cin.getline(userIn,30,'\n');

            if (strlen(userIn) < STRINGSIZE)
            {
                for(int i = 0; i < strlen(userIn); i++)
                {
                    if ((userIn[i] - '0' == 0) || (userIn[i] - '0' == 1))
                    {
                        if (strlen(userIn) == 8) 
                            a[i] = userIn[i];
                        else
                            a[7-i] = userIn[i];
                        valid = 1;
                    }
                    else
                    {
                        valid = 0;
                        break;
                    }
                }
           }

           if (valid == 0)
               std::cout << "Please enter a valid 8 bit binary number " << std::endl;
        }

        valid = 0;

        while(valid == 0) 
        {
            std::cout << "Enter binary number 2: ";
            std::cin.getline(userIn,30,'\n');

            if (strlen(userIn) < STRINGSIZE)
            {
                for(int i = 0; i < strlen(userIn); i++)
                {
                    if ((userIn[i] - '0' == 0) || (userIn[i] - '0' == 1))
                    {
                        if (strlen(userIn) == 8) 
                            b[i] = userIn[i];
                        else
                            b[7-i] = userIn[i];
                        valid = 1;
                    }
                    else
                    {
                        valid = 0;
                        break;
                    }
                }
           }
           if (valid == 0)
               std::cout << "Please enter a valid 8 bit binary number " << std::endl;
        }      
        
        std::cout << "\nThe numbers to be added are " << a << " and " << b << std::endl;
        
        for (int i = STRINGSIZE - 2; i >= 0; i--)
        {
            fullAdder(a[i]-'0',b[i]-'0',*carryOut);
            sum[i] = *sumOut + '0';
        }

        std::cout << "The answer is " << sum << "\n" << std::endl; 
    }

    return 0;
}
