#include <fstream>
#include <iostream>
#include <list>
#include <set>
#include <string>

/* TODO:
 *
 * Fix extra this 
 * Cleanup code
 * Test on syccuxas01
 * Submit project
 *
*/

//using namespace std; // Temp

int main ()
{
    std::string fileName;// = "Input.txt"; // Hard code temp
    bool debug = true;
//    bool debug = false;
    std::list<std::string> dataList;
    std::list<std::string>::iterator it;

    std::cout << "Welcome to lab 1! " << std::endl;

    // Prompt user for file to open
    std::cout << "\nFile location to read: ";// << std::endl;
    std::cin >> fileName;// >> std::endl; 

//    if (debug == true)
//        std::cout << "fileName = " << fileName << std::endl;

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

//    std::cout << "peek = " << inFile.peek() << std::endl;

    while (!inFile.eof() && !inFile.fail())
    {
        std::string tempString;

        inFile >> newString;

//        if (debug == true);
//            std::cout << "newString = " << newString << std::endl;
        
        it = dataList.begin();

        if (dataList.empty()) // Case 1: List empty
        {
//            std::cout << "List is empty " << std::endl;
            dataList.insert(it, newString);
        }
        else // Case 2: List not empty
        {
            while (it != dataList.end())
            {
                tempString = *it;       
//                std::cout << "tempString = " << tempString << std::endl;
        
                if (newString < tempString) // Case 2a: newString before it
                {
//                    std::cout << newString << " < " << tempString << std::endl;
                    dataList.insert(it, newString);
                    break;
                }
                else if (newString > tempString && (next(it) != dataList.end())) // Case 2b: newString after it
                {
//                    std::cout << newString << " > " << tempString << std::endl;
                } 
                else if (newString == tempString) // Case 2c: newString already exists
                {
//                    std::cout << newString << " == " << tempString << std::endl;
                    break;
                }
                else // Case 2d: newString at end of list
                {
//                    std::cout << newString << " is end of list " << std::endl;
                    dataList.push_back (newString);
//                    dataList.insert(it, newString);
//                    break;
                }

                ++it;
                
            } // Closes while
        } // Closes if   

//        std::cout << "\n-----\n" << std::endl;
//        std::cout << "\nbreak \n" << std::endl;

    } // Closes while

//    if (debug == true);
//        std::cout << "dataList size = " << dataList.size() << std::endl;

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
