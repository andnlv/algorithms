//
//  Algorithm.cpp
//  Kruskal
//
//  Created by Andrey Danilov on 14.10.16.
//  Copyright © 2016 Andrey Danilov. All rights reserved.
//

#include "Algorithm.hpp"

DSDS::DSDS(size_t size)
: vertices(size){
    for(int i = 0; i < size; ++i){
        vertices[i].parent = i;
        vertices[i].rank = 1;
    }
};

int DSDS::find(int x){
    if(x != vertices[x].parent)
        return find(vertices[x].parent);
    vertices[x].parent = vertices[vertices[x].parent].parent;
    return x;
}

void DSDS::merge(int x, int y){
    int xParent = find(x);
    int yParent = find(y);
    if(vertices[xParent].rank < vertices[yParent].rank){
        vertices[xParent].parent = yParent;
    }
    else if(vertices[xParent].rank > vertices[yParent].rank){
        vertices[yParent].parent = xParent;
    }
    else{
        vertices[xParent].parent = yParent;
        ++vertices[y].rank;
    }
}

long Boruvka(std::vector<std::unordered_map<int,int>> graph){
    long res = 0;
    int treeSize = 0;
    auto less = [&graph](const std::pair<int, int> &e1, const std::pair<int, int> &e2){
        if(e2.first == -1){
            return true;
        }
        return graph[e1.first][e1.second] < graph[e2.first][e2.second] ||
               (graph[e1.first][e1.second] == graph[e2.first][e2.second] &&
                graph.size()*e1.first + e1.second < graph.size()*e2.first + e2.second);
    };
    
    std::unordered_map<int, std::pair<int, int>> minEdge;
    std::vector<std::unordered_map<int,int>> tree(graph.size());
    DSDS sets(graph.size());
    while(treeSize < graph.size() - 1){
        minEdge.clear();
        for(int i = 0; i < graph.size(); ++i){
            for(auto it = graph[i].begin(); it != graph[i].end(); ++it){
                int v = sets.find(i);
                int u = sets.find(it->first);
                if(u != v){
                    if(minEdge.count(v) == 0 || less({i, it->first}, minEdge[v])){
                        minEdge[v] = {i, it->first};
                    }
                    if(minEdge.count(u) == 0 || less({i, it->first}, minEdge[u])){
                        minEdge[u] = {i, it->first};
                    }
                }
            }
        }
        for(auto it = minEdge.begin(); it != minEdge.end(); ++it){
            if(sets.find(it->second.first) == sets.find(it->second.second))
                continue;
            sets.merge(it->second.first, it->second.second);
            tree[it->second.first][it->second.second] = graph[it->second.first][it->second.second];
            tree[it->second.second][it->second.first] = graph[it->second.second][it->second.first];
            ++treeSize;
        }
    }
    for(int i = 0; i < tree.size(); ++i){
        for(auto it = tree[i].begin(); it != tree[i].end(); ++it){
            res += tree[i][it->first];
        }
    }
    return res/2;
};

std::vector<std::unordered_map<int,int>> read_graph(std::istream& in){
    int n, m, u, v, w;
    in >> n >> m;
    std::vector<std::unordered_map<int,int>> graph(n);
    for(int i = 0; i < m; ++i){
        in >> u >> v >> w;
        --u; --v;
        if(!(graph[u].count(v) != 0 && graph[u][v] < w)){
            graph[u][v] = w;
            graph[v][u] = w;
        }
    }
    return graph;
}


