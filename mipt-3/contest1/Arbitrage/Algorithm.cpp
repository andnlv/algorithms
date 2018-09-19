//
//  Algorithm.cpp
//  Arbitrage
//
//  Created by Andrey Danilov on 07.10.16.
//  Copyright © 2016 Andrey Danilov. All rights reserved.
//

#include <stdio.h>
#include "Algorithm.hpp"

void readGraph(Graph<WEdge, GraphVertex>& graph){
    int n;
    std::cin >> n;
    std::vector<std::vector<WEdge>> graphTable;
    graphTable.resize(n);
    WEdge edge;
    for(int i = 0; i < n; ++i){
        
        for(int j = 0; j < n; ++j){
            if( i == j )
                continue;
            double weight;
            std::cin >> weight;
            if(weight == -1)
                continue;
            edge.vertexTo = j;
            edge.vertexFrom = i;
            edge.weight = weight;
            graphTable[i].push_back(edge);
        }
    }
    graph = Graph<WEdge, GraphVertex>(graphTable);
}

bool searching_for_cycles(Graph<WEdge> g){
    std::vector<std::vector<std::vector<double>>> t;
    t.resize(g.sizeV()+1);
    for(auto& i : t){
        i.resize(g.sizeV());
        for(auto& j : i)
            j.resize(g.sizeV());
    }
    for(int i = 0; i < g.sizeV(); ++i){
        for(int j = 0; j < g.sizeV(); ++j){
            t[0][i][j] = (i == j);
            for(auto& k : g.getEdgesFrom(i))
                if(k->vertexTo == j)
                    t[0][i][j] = k->weight;
        }
    }
    for(int i = 1; i <= g.sizeV(); ++i){
        for(int j = 0; j < g.sizeV(); ++j){
            for(int k = 0; k < g.sizeV(); ++k){
                t[i][j][k] = std::max(t[i-1][j][k], t[i-1][j][i-1] * t[i-1][i-1][k]);
                if(j == k && t[i][j][k] > 1)
                    return true;
            }
        }
    }
    return false;
};