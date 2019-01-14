/*
 * NAME:        Jaime Landers
 * CRN:         43753 
 * ASSIGNMENT:  Lab 2
 * SOURCES:     None
*/

#include <iostream>

bool ifOnlyIf(bool p, bool q)
{
    // Evaluates inputs (q if and only if p) and returns result, do not edit this function!
    if ((p == 1 && q == 1) || (p == 0 && q == 0))
        return true;
    else
        return false;
}

bool ifThen(bool p, bool q)
{
    // Evaluates inputs (if p then q) and returns result, do not edit this function!
    if ((p == 1 && q == 1) || (p == 0 && q == 1) || (p == 0 && q == 0))
        return true;
    else
        return false;
}

bool conclusion (bool p, bool q, bool r)
{
    // Evaluates conclusion of argument entered below if if statement, edit this function.
    
//    if ( ENTER CONCLUSION HERE ) // <-- Edit this to change conclusion 

    // Conclusion: (P v R)
    if (p || r) // Comment out after adding conclusion above
        return true;
    else
        return false;
}

bool premise (bool p, bool q, bool r)
{
    // Evaluates premise of argument entered below in return statement, edit this function.
    
//    return ( ENTER PREMISE HERE ); // <-- Edit this to change premise

    // Premise: (((P v Q) ^ (Q -> R)) XOR (P ^ R)) <-> (R ^ Q)
    return (ifOnlyIf((((p | q) & (ifThen(q,r))) ^ (p & r)),(r & q)));  // Comment out after adding premise above
}


int main () // Do not edit anything in main
{
    bool p [8] = {1,1,1,1,0,0,0,0};
    bool q [8] = {1,1,0,0,1,1,0,0};
    bool r [8] = {1,0,1,0,1,0,1,0};
    bool prem [8] = {0};
    bool concl [8] = {0};
    bool argInvalid = 0;

    std::cout << "Welcome to lab 2!\n " << std::endl;
    
    for (int i = 0; i < 8; i++)
    {
        prem[i] = premise(p[i],q[i],r[i]);
        concl[i] = conclusion(p[i],q[i],r[i]);
        
        if (prem[i] == 1 && concl[i] == 0)
        {
            std::cout << "The argument is invalid in row " << i << std::endl;
            argInvalid = 1;
        }
    }

    if (argInvalid == 0)
        std::cout << "\nThe argument is valid. " << std::endl;

    std::cout << "Row";
    std::cout << "\tP";
    std::cout << "\tQ";
    std::cout << "\tR";
    std::cout << "\tPrem";
    std::cout << "\tConcl" << std::endl;

    for (int i = 0; i < 8; i++)
    {
        std::cout << i;
        std::cout << "\t" << p[i];
        std::cout << "\t" << q[i];
        std::cout << "\t" << r[i];
        std::cout << "\t" << prem[i];
        std::cout << "\t" << concl[i] << std::endl;
    }

    std::cout << "\n";
    
    return 0;
}
