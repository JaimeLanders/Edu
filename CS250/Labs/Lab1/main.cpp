#include <fstream>
#include <iostream>
#include <list>
#include <set>
#include <string>

int main ()
{
    std::string fileName;
    std::list<std::string> dataList;
    std::list<std::string>::iterator it;

    std::cout << "Welcome to lab 1! " << std::endl;

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
    }

    // Read data and add to list
    std::string newString;

    while (!inFile.eof() && !inFile.fail())
    {
        std::string tempString;

        inFile >> newString;

        it = dataList.begin();

        if (dataList.empty()) // Case 1: List empty
        {
            dataList.insert(it, newString);
        }
        else // Case 2: List not empty
        {
            while (it != dataList.end())
            {
                tempString = *it;       
        
                if (newString < tempString) // Case 2a: newString before it
                {
                    dataList.insert(it, newString);
                    break;
                }
                else if (newString > tempString && (next(it) != dataList.end())) // Case 2b: newString after it
                {
                    // Do nothing
                } 
                else if (newString == tempString) // Case 2c: newString already exists
                {
                    break;
                }
                else // Case 2d: newString at end of list
                {
                    dataList.push_back (newString);
                }

                ++it;
                
            }
        }

    }

    // Close file
    inFile.close();

    // Output list
    if (fileOpen == true)
    {
        std::cout << "\nWords in the file: " << std::endl;

        for(it = dataList.begin(); it != dataList.end(); it++)
        {
            
            std::cout << *it << std::endl;
        }

        std::cout << "\n";
    }

    return 0;
}
