//#include <iostream>
#include "kruskal.h"
#include "kruskaltest.h"
#include "prim.h"
#include "primtest.h"

//Forward Declarations:
void printMST(E & e);
void printMSTw(Ew & e);

int main()
{
    std::cout << "Welcome to Assignment 4 " << std::endl;

    G g;
    E MST;

    initGraph(g, "city-pairs.txt");

    std::cout << "\nPerforming Prim's algorithm on the graph " << std::endl;
    MST = prim(g);

    std::cout << "\nPrinting Prim's MST " << std::endl;
    printMST(MST);

    if(primTest(MST))
    {
        std::cout << "The Prim MST is correct " << std::endl;
    }
    else
    {
        std::cout << "The Prim MST is NOT correct " << std::endl;
    }

    std::cout << "\nPerforming Kruskal's algorithm on the graph " << std::endl;
    Ew MSTw = kruskal(g);

    std::cout << "\nPrinting Kruskal's MST " << std::endl;
    printMSTw(MSTw);

    if(kruskalTest(MSTw))
    {
        std::cout << "The Kruskal MST is correct " << std::endl;
    }
    else
    {
        std::cout << "The Kruskal MST is NOT correct " << std::endl;
    }
    return 0;
}

void printMST(E & e)
{
//    std::cout << "\nprintMST " << std::endl;

    E::iterator itE;
    int ttlDis = 0;

//    std::cout << "\nPrinting all edges and weights of MST: " << std::endl;
    std::cout << "Source: Destination: Distance: Cumulative Distance; " << std::endl;
    for(itE = e.begin(); itE != e.end(); itE++)
    {
        ttlDis += itE->second;

        std::cout << itE->first.first << " ";
        std::cout << itE->first.second << " ";
//        std::cout << itE->second << std::endl;
        std::cout << itE->second << " ";
        std::cout << ttlDis << std::endl; 
    }
    std::cout << "\nThe total distance of the MST is " << ttlDis << "." << std::endl;  
}

void printMSTw(Ew & e)
{
//    std::cout << "\nprintMST " << std::endl;

    Ew::iterator itE;
    int ttlDis = 0;

//    std::cout << "\nPrinting all edges and weights of MST: " << std::endl;
    std::cout << "Source: Destination: Distance: Cumulative Distance; " << std::endl;
    for(itE = e.begin(); itE != e.end(); itE++)
    {
        ttlDis += itE->second;

        std::cout << itE->first.first << " ";
        std::cout << itE->first.second << " ";
//        std::cout << itE->second << std::endl;
        std::cout << itE->second << " ";
        std::cout << ttlDis << std::endl; 
    }
    std::cout << "\nThe total distance of the MST is " << ttlDis << "." << std::endl;  
}
