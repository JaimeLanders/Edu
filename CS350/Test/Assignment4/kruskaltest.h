#ifndef KRUSKALTEST_H
#define KRUSKALTEST_H

#include "kruskal.h"
#include <iostream>

bool kruskalTest(Ew e)
{
//    std::cout << "\nkruskalTest " << std::endl;

    bool passed = true;
    G testG;

    initGraph(testG, "city-pairs-best.txt"); 
    Ew ewTest;
    ewTest = sortWeight(testG.second);

    E::iterator tIt;
    tIt = ewTest.begin();

    for(E::iterator it = e.begin(); it != e.end(); it++)
    {
        if(ewTest.size() != e.size() || (it->first.first != tIt->first.first && it->first.second != tIt->first.second && it->second != tIt->second))
        {
            passed = false;
        }
        tIt++;
    }

    return passed;
}

#endif
