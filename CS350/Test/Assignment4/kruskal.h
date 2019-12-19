#ifndef KRUSKAL_H  
#define KRUSKAL_H 

#include "disjointSet.h"
#include "graph.h"

Ew kruskal(G & g)
{
//    std::cout << "\nkruskal " << std::endl; 

    // Kruskal’s algorithm for constructing a minimum spanning tree
    // Input: A weighted connected graph G = <V, E>
    // Output: E_T, the set of edges composing a minimum spanning tree of G 
    // sort E in nondecreasing order of the edge weights w(e_i_1) ≤...≤ w(e_i_|E|)
    Ew ew; 

    disjointSet dis;

    ew = sortWeight(g.second);
    
    for(Ew::iterator it = ew.begin(); it != ew.end(); it++)
    {
        dis.makeset(*it);
    }
//        std::cout << "dis size = " << dis.size() << std::endl;

    // E_T ← ∅; ecounter ← 0 // initialize the set of tree edges and its size
    Ew E_T;

    unsigned long eCount = 0;

    // k ← 0, initialize the number of processed edges
    int k = 0;

    // while ecounter < |V| − 1 do
    while(eCount < 1)
    {
//        std::cout << "eCount = " << eCount << std::endl;

        // k ← k + 1
        k += 1;

        // if E_T ∪ {e_i_k) is acyclic
        for(Ew::iterator it1 = ew.begin(); it1 != ew.end(); it1++)
        {
            if(dis.findSet(it1->first.first) != dis.findSet(it1->first.second))
            {
                // E_T ← E_T ∪ {e_i_k}; 
                E_T.insert(*it1);
                e eTemp1;
                e eTemp2;

                eTemp1 = std::make_pair(std::make_pair(it1->first.first, ""),it1->second);
                eTemp2 = std::make_pair(std::make_pair(it1->first.second, ""),it1->second);

                dis.unionSet(eTemp1, eTemp2);
            
                // ecounter ← ecounter + 1
                eCount += 1; 
            }
        }
    }

    return E_T;
}
#endif
