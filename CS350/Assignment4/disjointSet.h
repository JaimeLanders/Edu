#ifndef DISJOINTSET_H  
#define DISJOINTSET_H 

#include "graph.h"

class disjointSet
{
    std::set<E> disSet;
    int disSetSize;
public:
    disjointSet(){disSetSize = 0;};
    E findSet(e1 x)
    {
//        std::cout << "\ndisjoinSet findSet " << std::endl;

        E tempE;

        for(std::set<E>::iterator it = disSet.begin(); it != disSet.end(); it++)
        { 
            for(E::iterator itE = it->begin(); itE != it->end(); itE++)
            {
                if(itE->first.first == x)
                {
                    tempE = *it;
                }
            }
        }

        return tempE;
    }

    E getSet()
    {
//        std::cout << "\ndisjointSet getSet " << std::endl;
        return *disSet.begin();
    }

    void makeset(e x)
    {
//        std::cout << "\ndisjointSet makeset " << std::endl;
        e1 e1Temp = x.first.first;
        e2 e2Temp = x.first.second;
        w wTemp = 0;
        e eTemp = make_pair(make_pair(e1Temp, e1Temp), wTemp);// = *it; 
        e eTempR = make_pair(make_pair(e2Temp, e2Temp), wTemp);// = *it; 

        E tempE;
        E tempER;
        tempE.insert(eTemp);
        tempER.insert(eTempR);
            

        if(disSet.count(tempE) == 0)
        {
            disSet.insert(tempE);
            disSetSize++;
        }
        else if(disSet.count(tempER) == 0)
        {
             disSet.insert(tempER);
             disSetSize++;
        }
    }

    int size()
    {
        return disSetSize;
    }
    void print()
    {
//        std::cout << "\ndisjointSet print " << std::endl;
        for(std::set<E>::iterator it = disSet.begin(); it != disSet.end(); it++)
        {
            printE(*it);
        }
    }
    void unionSet(e x, e y)
    {
//        std::cout << "\ndisjointSet unionSet " << std::endl;

        E tempE;
        E tempEx = findSet(x.first.first);
        E tempEy = findSet(y.first.first);
        e eTemp;

        if(tempEx != tempEy)
        {
            for(E::iterator it = tempEx.begin(); it != tempEx.end(); it++)
            {
                tempE.insert(*it);
            }
            for(E::iterator it = tempEy.begin(); it != tempEy.end(); it++)
            {
                tempE.insert(*it);
            }

            disSet.insert(tempE);

            disSet.erase(tempEx);
            disSet.erase(tempEy);
            disSetSize -= 1;
        }
    }
};
#endif
