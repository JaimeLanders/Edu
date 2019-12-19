#ifndef PRIMTTEST_H
#define PRIMTEST_H

#include "prim.h"
#include <iostream>

bool primTest(E e)
{
//    std::cout << "\nprimTest " << std::endl;

    bool passed = true;
    G testG;

    initGraph(testG, "city-pairs-best.txt"); 

    E::iterator tIt;
    tIt = testG.second.begin();

    for(E::iterator it = e.begin(); it != e.end(); it++)
    {
        if(testG.second.size() != e.size() || (it->first.first != tIt->first.first && it->first.second != tIt->first.second && it->second != tIt->second))
        {
            passed = false;
        }
        tIt++;
    }

    return passed;
}
#endif
