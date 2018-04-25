/*
 * NAME:        Jaime Landers
 * CRN:         13759          
 * ASSIGNMENT:  Lab 1
 * SOURCES:     None
 *
 * TODO:
 * - Fix cardinality of powerSet logic if cardinality > long long max value
 * - Fix trailing comma
 *
*/

#include <iostream>
#include <vector>

int main ()
{
    std::string a;
    std::string b;
    long long cardinality = 0;
    int maxSize = 200;
    int setSize = 0;
    int stringSize = 0;
    std::vector<std::string> setA;
    std::vector<std::string> setB;

    std::cout << "Welcome to Lab 1 " << std::endl;

    //Get set A and read into array A
    
    std::cout << "\nEnter set A: ";
    std::getline(std::cin, a);
    std::cin.clear();
      stringSize = a.size();

    int end = 0;
    int i = 0;
    std::string::iterator it = a.begin();

    while ((it != a.end()) && (end >= 0) && (end < stringSize))
    {
        int begin = end; 

        end = a.find(" ", end);
        std::string element = a.substr(begin, end - begin);
        setA.push_back(element);

        i++;
        it++;

        if (end <= stringSize && end >= 0)
        {
            end += 1;
        }
    }

    //Get set B and read into array B

    std::cout << "\nEnter set B: ";
    std::getline(std::cin, b);
    std::cin.clear();
    stringSize = b.size();

    end = 0;
    i = 0;
    it = b.begin();

    while ((it != b.end()) && (end >= 0) && (end < stringSize))
    {
        int begin = end; 

        end = b.find(" ", end);
        std::string element = b.substr(begin, end - begin);
        setB.push_back(element);

        i++;
        it++;

        if (end <= stringSize && end >= 0)
        {
            end += 1;
        }
    }
    i = 0;

    std::cout << "\nSet A: {";
    for(std::vector<std::string>::iterator it = setA.begin(); it != setA.end() ; it++)
    {
        std::cout << *it;
        std::cout << ", ";

        i++;
        cardinality++;
    }
    std::cout << "}\n";
    std::cout << "The cardinality of Set A: " << cardinality << std::endl;
    i = 0;
    cardinality = 0;

    std::cout << "\nSet B: {";
    for(std::vector<std::string>::iterator it = setB.begin(); it != setB.end() ; it++)
    {
        std::cout << *it;
        std::cout << ", ";

        i++;
        cardinality++;
    }
    std::cout << "}\n";
    std::cout << "The cardinality of Set B: " << cardinality << std::endl;
    i = 0;
    cardinality = 0;

    // Set arraySize to be equal to cardinality of smallest set (if differenct cardinalities)
    
    if (setA.size() <= setB.size())
    {
        setSize = setA.size();
    }
    else
    {
        setSize = setB.size();
    }

    if(setSize > maxSize)
    {
        std::cout << "\nSet A or B is over " << maxSize << " elements, only counting first " << maxSize << "... " << std::endl;
        setSize = maxSize;
    }
    
    //Print cardinality and roster of the intersection of sets A and B
    
    std::cout << "\nRoster of intesection of A and B: " << std::endl;
    std::cout << "{";
    for(std::vector<std::string>::iterator itA = setA.begin(); itA != setA.end(); itA++)
    {
        for(std::vector<std::string>::iterator itB = setB.begin(); itB != setB.end(); itB++)
        {
            if(*itA == *itB)
            {
                std::cout << *itA;

                i++;
                cardinality++;

                std::cout << ", ";
            }
        }
    }   
    std::cout << "}" << std::endl;
    i = 0;

    std::cout << "The cardinality of the intersection of A and B is: " << cardinality << std::endl;
    cardinality = 0;

    //Print cardinality and roster of the union of sets A and B
    
    std::cout << "\nRoster of union of A and B: " << std::endl;
    std::cout << "{";

    for(int i = 0; i < setSize; i++)
    {
        if(setA[i] != setB[i])
        {
            std::cout << setA[i];
            std::cout << ", ";

            cardinality++;

            bool found = false;

            for(int j = 0; j < setSize; j++)
            {
                if (setA[j] == setB[i])
                {
                    found = true;
                    break; //temp
                }
            }

            if (found == false)
            {
                std::cout << setB[i];
                std::cout << ", ";

                cardinality++;

            }
        }
        else
        {
            std::cout << setA[i];
            cardinality++;

            std::cout << ", ";
        }
    }
    std::cout << "}" << std::endl;

    std::cout << "The cardinality of the union of A and B is: " << cardinality << std::endl;
    cardinality = 0;

    //Print cardinality and roster of the relative complement of sets A and B (A - B)
    
    std::cout << "\nRoster of relative complement of A and B (A - B): " << std::endl;
    std::cout << "{";
    for(int i = 0; i < setSize; i++)
    {
        bool found = false;

        for(int j = 0; j < setSize; j++)
        {
            if (setA[i] == setB[j])
            {
                found = true;
            }
        }

        if (found == false)
        {
            std::cout << setA[i];
            cardinality++;

            std::cout << ", ";
        }
    }   
    std::cout << "}" << std::endl;   

    std::cout << "The cardinality of the complement of A and B is: " << cardinality << std::endl;
    cardinality = 0;

    //Print cardinality and roster of the relative complement of sets B and A (B - A)
    
    std::cout << "\nRoster of relative complement of B and A (B - A): " << std::endl;
    std::cout << "{";
    for(int i = 0; i < setSize; i++)
    {
        bool found = false;

        for(int j = 0; j < setSize; j++)
        {
            if (setB[i] == setA[j])
            {
                found = true;
            }
        }

        if (found == false)
        {
            std::cout << setB[i];
            cardinality++;

            std::cout << ", ";
        }
    }   
    std::cout << "}" << std::endl;

    std::cout << "The cardinality of the complement of B and A is: " << cardinality << std::endl;
    cardinality = 0;

    //Print cardinality and roster of the cross product of sets A and B (A - B)
    
    std::cout << "\nRoster of cross product of A and B: " << std::endl;
    std::cout << "{";
    for(int i = 0; i < setSize; i++)
    {
        for(int j = 0; j < setSize; j++)
        {
        std::cout << "(";
        std::cout << setA[i];
        std::cout << ", ";
        std::cout << setB[j];
        std::cout << ")";
        std::cout << ", ";

        cardinality++;
        }
    }   
    std::cout << "}" << std::endl;

    std::cout << "The cardinality of the cross product of A and B is: " << cardinality << std::endl;

    //Print cardinality power set of the cross product of sets A and B (A - B)
    
    long long powerCard = 1;

    for(int i = 0; i < cardinality; i++)
    {
        powerCard *= 2;
    }

    std::cout << "\nThe cardinality of the power set of the cross product of A and B is: 2^" << cardinality; 

    if ((powerCard > 0) && (cardinality > 0) && (powerCard <= 9223372036854775807)) // Dont print if > long long limit
    {
        std::cout << " = " << powerCard << std::endl;
    }

    std::cout << "\n"; // Temp

    return 0;
}
