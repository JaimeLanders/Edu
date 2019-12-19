#ifndef PRIM_H  
#define PRIM_H 

#include "graph.h"

// ALGORITHM Prim(G)
E prim(G & g)
{
//    std::cout << "\nprim " << std::endl;

    // Prim’s algorithm for constructing a minimum spanning tree
    // Input: A weighted connected graph G = <V, E>
    // Output: E_T , the set of edges composing a minimum spanning tree of G
    // VT ← {v_0} //the set of tree vertices can be initialized with any vertex
    V V_T; 
    V_T.insert(*g.first.begin());
    V VminV_T = g.first;
    VminV_T.erase(VminV_T.begin());

    // E_T ← ∅
    E E_T;

    // for i ← 1 to |V| − 1 do
    for(size_t i = 0; i < g.first.size() - 1; i++)
    {
        // find a minimum-weight edge e^∗ = (v^∗, u^∗) among all the edges (v, u) such that v is in V_T and u is in V − V_T
        e eTemp;
        v uTemp = *VminV_T.begin();
        v vTemp;
        int min = g.second.begin()->second;
        
        for(V::iterator itV = V_T.begin(); itV != V_T.end(); itV++)
        {
            vTemp = *itV; 

            for(E::iterator itE = g.second.begin(); itE != g.second.end(); itE++)
            {
                if(itE->first.first == vTemp && itE->second < min && E_T.count(*itE) == 0 && VminV_T.count(itE->first.second) != 0)
                {
                    uTemp = itE->first.second;
                    eTemp = *itE;

                    min = itE->second;
                }
            }
        }

        if(E_T.count(eTemp) == 0)
        {
            // V_T ← V_T ∪ {u^∗}
            V_T.insert(uTemp);
            VminV_T.erase(uTemp); // Test

            // E_T ← E_T ∪ {e^∗}
            E_T.insert(eTemp);
        }
    }

     return E_T;
}
#endif
