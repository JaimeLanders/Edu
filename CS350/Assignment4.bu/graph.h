#ifndef GRAPH_H
#define GRAPH_H

#include <fstream>
#include <iostream>
#include <vector>
#include <set>
#include <string>

// Type definitions:
typedef int w;
typedef std::string e1, e2, v;
typedef std::pair<e1, e2> es; 
typedef std::pair<es, w> e; 
typedef std::set<v> V;
typedef std::set<e> E; // Sorted by v_1 A-Z
typedef std::pair<V, E> G;

struct Comparator
{
//    std::cout<< "\ngraph Comparator " << std::endl;
    bool operator()(const e & lhs, const e & rhs) const
    {
        return lhs.second <= rhs.second;
    }
};

typedef std::set<e, Comparator> Ew; // Sorted by w 
typedef std::pair<V, Ew> Gw;

// Forward declarations:
void printGraph(G & g);
void printGraphw(Gw & g);
void printe(const e & itE);
void printE(const E & e);
void printEw(const Ew & e);
void printV(V & v);
Ew sortWeight(const E & e);

void initGraph(G & g, std::string fileName)
{
//    std::cout << "\ngraph initGraph " << std::endl;

    std::ifstream inFile;
    inFile.open(fileName);

    V tempV;
    E tempE;

    std::string temp;

    while(std::getline(inFile, temp))
    {
        std::string delim = " ";

        std::size_t e1Start = 0;
        std::size_t e1End = temp.std::string::find(delim);

        e1 e1Temp  = temp.substr(e1Start, e1End);

        std::size_t e2Start = e1End + 1;
        std::size_t e2End = temp.std::string::find(delim, e2Start);

        e2 e2Temp = temp.substr(e2Start, e2End - e2Start);

        std::size_t wStart = e2End + 1;
        std::size_t wEnd = temp.std::string::find(delim, e2Start);

        w wTemp = std::stoi(temp.substr(wStart, wEnd - wStart));

        es esTemp;
        esTemp = std::make_pair(e1Temp, e2Temp);

        e eTemp = std::make_pair(esTemp, wTemp);

        es esCheck;
        esCheck = std::make_pair(e2Temp, e1Temp);

        e eCheck = std::make_pair(esCheck, wTemp);

        tempV.insert(e1Temp);
        tempE.insert(eTemp);
    }

    g = (std::make_pair(tempV, tempE));

    inFile.close();
}

void printe(const e & itE)
{
//    std::cout << "\nGraph printe " << std::endl;
//
    std::cout << itE.first.first << " ";
    std::cout << itE.first.second << " ";
    std::cout << itE.second << std::endl;
   
}

void printE(const E & e)
{
//    std::cout << "\nGraph printE " << std::endl;

    E::iterator itE;

    for(itE = e.begin(); itE != e.end(); itE++)
    {
        std::cout << itE->first.first << " ";
        std::cout << itE->first.second << " ";
        std::cout << itE->second << std::endl;
    }
}

void printEw(const Ew & e)
{
//    std::cout << "\nGraph printEw " << std::endl;

    Ew::iterator itE;

    for(itE = e.begin(); itE != e.end(); itE++)
    {
        std::cout << itE->first.first << " ";
        std::cout << itE->first.second << " ";
        std::cout << itE->second << std::endl;
    }
}

void printGraph(G & g)
{
//    std::cout << "\nGraph printGraph " << std::endl;

    E tempE = g.second;
    V tempV = g.first;

    std::cout << "\nPrinting all vertices: " << std::endl;
    printV(tempV);

    std::cout << "\nPrinting all edges and weights: " << std::endl;
    printE(tempE);
}

void printGraphw(Gw & g)
{
//    std::cout << "\nGraph printGraphw " << std::endl;

    Ew tempE = g.second;
    V tempV = g.first;

    std::cout << "\nPrinting all vertices: " << std::endl;
    printV(tempV);

    std::cout << "\nPrinting all edges and weights: " << std::endl;
    printEw(tempE);
}

void printV(V & v)
{
//    std::cout << "\nGraph printV " << std::endl;

    V::iterator itV;

    for(itV = v.begin(); itV != v.end(); itV++)
    {
        std::cout << *itV << std::endl;
    }
}

Ew sortWeight(const E & e)
{
//    std::cout << "\nGraph sortWeight " << std::endl;
    Ew ew;

    for(E::iterator it = e.begin(); it != e.end(); it++)
    {
        ew.insert(*it);
    }

    return ew;
}
#endif
