//
//  Algorithm.cpp
//  Floid
//
//  Created by Andrey Danilov on 14.10.16.
//  Copyright © 2016 Andrey Danilov. All rights reserved.
//

#include "Algorithm.hpp"

void readGraph(Graph<WEdge, GraphVertex>& graph, std::istream& in){
    int n;
    in >> n;
    std::vector<std::vector<WEdge>> graphTable;
    graphTable.resize(n);
    WEdge edge;
    for(int i = 0; i < n; ++i){
        
        for(int j = 0; j < n; ++j){
            double weight;
            in >> weight;
            if( i == j )
                continue;
            edge.vertexTo = j;
            edge.vertexFrom = i;
            edge.weight = weight;
            graphTable[i].push_back(edge);
        }
    }
    graph = Graph<WEdge, GraphVertex>(graphTable);
}

void Floid(Graph<WEdge>& g, std::ostream &out){
    std::vector<std::vector<std::vector<double>>> t;
    t.resize(g.sizeV()+1);
    for(std::vector<std::vector<double>> & i : t){
        i.resize(g.sizeV());
        for(std::vector<double> & j : i)
            j.resize(g.sizeV());
    }
    for(int i = 0; i < g.sizeV(); ++i){
        for(int j = 0; j < g.sizeV(); ++j){
            t[0][i][j] = 1e100 * (i != j);
            for(auto& k : g.getEdgesFrom(i))
                if(k->vertexTo == j)
                    t[0][i][j] = k->weight;
        }
    }
    for(int i = 1; i <= g.sizeV(); ++i){
        for(int j = 0; j < g.sizeV(); ++j){
            for(int k = 0; k < g.sizeV(); ++k){
                t[i][j][k] = std::min(t[i-1][j][k], t[i-1][j][i-1] + t[i-1][i-1][k]);
            }
        }
    }
    for(auto& j: t[g.sizeV()]){
        for(auto& k: j)
            out << k << " ";
        out << "\n";
    }
};
