/*
 * NAME:        Jaime Landers
 * CRN:         13759          
 * ASSIGNMENT:  Lab 4
 * SOURCES:     None
 *
*/

#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

typedef int src, dest, weight;

int kFind(int n, src root, src source, dest destination, std::vector<std::vector<weight>> t)
{
    weight weight1 = 0;

    for (int i = 0; i < n; i++)
    {
        weight1 = t[destination - 1][i];

        if (weight1 != 0) 
        {
            if (i + 1 != source)
            {
                if(destination == root)
                {
                    return root;
                }
                else
                {
                    return kFind(n, root, destination, i + 1, t);
                }
            }
            else if(destination == root)
            {
                return root;
            }
        }
   }

    return 0;
}

int main ()
{
    std::pair<int, std::pair<int, int>> p;
    std::vector<std::vector <int>> G =
        { 
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0}
        };
    std::vector<std::vector <weight>> T;
    std::vector<std::pair<weight, std::pair<src, dest>>> E;
    std::vector<std::pair<weight, std::pair<src, dest>>>::iterator setIt;// = 0;
    int n = 12;
    int gWeight = 0;
    int maxSize = 12;
    std::string userIn;

    std::cout << "Welcome to Lab 4 " << std::endl;

    // Get user input
    int run = 1;
    int col = 0;

    std::cout << "Enter WAM: " << std::endl;
    while (col < n) 
    {
        std::string sub;
        std::size_t pos = 0, end = 0;
        std::getline(std::cin, userIn);// << std::endl; 

        std::string::iterator strIt = userIn.begin();
        size_t strSize = userIn.size();

        int row = 0;

        while (strIt != userIn.end() && end < strSize)
        {
            pos = end;
            end = userIn.find(" ", end);
            sub = userIn.substr(pos, end - pos);

            if (run == 1)
            {
                n = std::count(userIn.begin(), userIn.end(), ' ') + 1;
            }

            G[col][row] = std::stoi (sub);

            strIt++;
            row += 1;

            if (end <= strSize)
            {
                end += 1;
            }

            run +=1;
        }

        col += 1;
    }

    setIt = E.begin();

    std::cout << "\nThe WAM is: " << std::endl;
    for (int i = 0; i < n; i++) // Print row
    {
        for (int j = 0; j < n; j++)
        {
            std::pair<weight, std::pair<src, dest>> temp;
            temp = std::make_pair(G[i][j], std::make_pair(j + 1, i + 1));
            std::vector<std::pair<weight, std::pair<src, dest>>>::iterator it = std::find(E.begin(), E.end(), temp);

            std::cout << G[i][j] << "\t ";

            if(G[i][j] > 0 && it == E.end())
            {
                p = std::make_pair(G[i][j], std::make_pair(i + 1, j + 1));
                E.push_back(p);
            }
        }
        std::cout << "\n";
    }
    std::cout << "\n";

    // Sort E by increasing weight
    sort(E.begin(), E.end());

    // Kruskal's Algorithm
    // 1. Initialize T to have all the vertices of G and no edges
    T = G;
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            T[i][j] = 0;
        }
    }
    
    // 2. Let E be the set of all edges of G, and let m = 0;
    int m = 0;

    //3. 
    setIt = E.begin();
    std::vector<std::pair<weight, std::pair<src, dest>>> t;

    while (m < n - 1) 
    {
        std::pair<weight, std::pair<src, dest>> e;
        e.first = setIt->first;
        e.second.first = setIt->second.first;
        e.second.second = setIt->second.second;
        
        //3a. Find an edge e in E of least weight

        //3b. Delete e from E
//        E.erase(setIt); // Needs deep copy

        //3c. If addition of e to the edge set of T does not produce a circuit
              // Then add e to the edge set of T and set m = m + 1
              
        if(T.empty())
        {
            T[e.second.first - 1][e.second.second - 1] = e.first;            
            T[e.second.second - 1][e.second.first - 1] = e.first;            
            m += 1;
            gWeight += e.first;
        }
        else
        {
            bool found = false;
                
            src source = e.second.first;  
            dest destination = e.second.second;  

            if (kFind(n, source, source, destination, T) == source)
            {
                found = true;
            }

            if (found == false)
            {
                t.push_back(e);
                T[e.second.first - 1][e.second.second - 1] = e.first;            
                T[e.second.second - 1][e.second.first - 1] = e.first;            
                gWeight += e.first;
                m += 1;
            }
        }
            
        setIt++;
    }

    // Output T (miniumum spanning tree for G)
    std::cout << "\nThe output from Kruskal's Algorithm is: " << std::endl;
    for (int i = 0; i < n; i++) // Print row
    {
        for (int j = 0; j < n; j++)
        {
            std::cout << T[i][j] << "\t ";
        }
        std::cout << "\n";
    }

    std::cout << "\nThe total weight of the graph is " << gWeight << std::endl; 
    std::cout << "\nThe number of edges  of the graph is " << m << std::endl; 

    // Re-initialze T
    T.clear();

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            T[i][j] = 0;
        }
    }

    gWeight = 0;

    std::vector<std::vector <weight>> T2 = {{0}};
    std::vector<src> V;

    // Prim's Algorithm
    //1.  Pick a vertex v of G and let T be the graph with one vertex, v, and no edges.
    int v = 0;
    bool found = false;

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            if (G[i][j] != 0)
            {
                v = i + 1;
                found = true;
                break;
            }

        }
        if (found == true)
        {
            break;
        }
    }
    //2.  Let V be the set of all vertices of G except v.
    for(int i = v + 1; i <= n; i++)  
    {
        V.push_back(i);
    }

    //3.    
    for (int i = 0; i < n; i++)
    {

        if (V.empty())
        {
            break;
        }

        std::pair<weight, std::pair<src, dest>> e;
        e.first = 0;
        e.second.first = 0;
        e.second.second = 0;
    
        //3a. Find an edge e of G such that (1) e connects T to one of the vertices in V, and (2) e has the least wieght of
        //    all edges connecting T to a vertex in V.  Let w be the endpoint of e that is in V.
        for (int j = 0; j < n; j++)
        {
            if(((std::find(V.begin(), V.end(), j + 1) != V.end()) || (std::find(V.begin(), V.end(), i + 1) != V.end())) && (!V.empty()))
            {
                if (((G[i][j] != 0) && (G[i][j] <= (e.first))) || (e.first == 0)) 
                {
                    e.first = G[i][j];
                    e.second.first = i + 1;
                    e.second.second = j + 1;
                }
            }
        }
    
        //3b. Add e and w to the edge and vertex sets of T, and delete w from V.
        T[e.second.first - 1][e.second.second - 1] = e.first;
        T[e.second.second - 1][e.second.first - 1] = e.first;

        std::vector<src>::iterator w = std::find(V.begin(), V.end(), e.second.second);

        if(w != V.end())
        {
            V.erase(w);
        }
        else
        {
            w = std::find(V.begin(), V.end(), e.second.first);
            if(w != V.end())
            {
                V.erase(w);
            }

        }

        gWeight += e.first;
    }
        
// Output T (miniumum spanning tree for G)
    std::cout << "\nThe output from Prim's Algorithm is: " << std::endl;
    for (int i = 0; i < n; i++) // Print row
    {
        for (int j = 0; j < n; j++)
        {
            std::cout << T[i][j] << "\t ";
        }
        std::cout << "\n";
    }

    std::cout << "\nThe total weight of the graph is " << gWeight << std::endl; 
    std::cout << "\nThe number of edges  of the graph is " << m << std::endl; 

    return 0;
}
