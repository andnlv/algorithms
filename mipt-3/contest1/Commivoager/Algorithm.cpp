//
//  Algorithm.cpp
//  Commivoager
//
//  Created by Andrey Danilov on 14.11.16.
//  Copyright © 2016 Andrey Danilov. All rights reserved.
//

#include "Algorithm.hpp"
#include <cassert>
#include <iostream>
#include <cmath>
#include <unordered_map>
#include <stack>

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

double count_weight(const std::vector<int>& way, const Graph& graph){
    assert(way.size() == graph.size());
    double res = 0;
    for(int i = 0; i < way.size()-1; ++i){
        res += graph[way[i]][way[i+1]];
    }
    res += graph[way[0]][way.back()];
    return res;
}

double find_gamilton(const Graph &graph){
    double res = INFINITY;
    std::vector<int> way(graph.size());
    for(int i = 0; i < graph.size(); ++i){
        way[i] = i;
    }
    do{
        res = std::min(res, count_weight(way, graph));
    }
    while(std::next_permutation(way.begin()+1, way.end()));
    return res;
}

double Boruvka(const Graph& graph){
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
    std::vector<vertex<int>> tree(graph.size());
    DSDS sets(graph.size());
    while(treeSize < graph.size() - 1){
        minEdge.clear();
        for(int i = 0; i < graph.size(); ++i){
            for(int j = 0; j < graph.size(); ++j){
                int v = sets.find(i);
                int u = sets.find(j);
                if(u != v){
                    if(minEdge.count(v) == 0 || less({i, j}, minEdge[v])){
                        minEdge[v] = {i, j};
                    }
                    if(minEdge.count(u) == 0 || less({i, j}, minEdge[u])){
                        minEdge[u] = {i, j};
                    }
                }
            }
        }
        for(auto it = minEdge.begin(); it != minEdge.end(); ++it){
            if(sets.find(it->second.first) == sets.find(it->second.second))
                continue;
            sets.merge(it->second.first, it->second.second);
            tree[it->second.first].push_back(it->second.second);
            tree[it->second.second].push_back(it->second.first);
            ++treeSize;
        }
    }
    for(int i = 0; i < tree.size(); ++i){
        tree[i].color = W;
    }
    std::stack<int> stk;
    std::vector<int> way;
    stk.push(0);
    while(!stk.empty()){
        int current_v = stk.top();
        way.push_back(current_v);
        tree[current_v].color = B;
        stk.pop();
        for(int i = 0; i < tree[current_v].size(); ++i){
            if(tree[tree[current_v][i]].color == W){
                stk.push(tree[current_v][i]);
            }
        }
    }
    return count_weight(way, graph);
};

Graph generate_graph(int size, int seed){
    srand(seed);
    std::vector<std::pair<double, double>> points(size);
    for(int i = 0; i < size; ++i){
        double fi, r;
        fi = (rand()%1000000+1.)/1000000;
        r = (rand()%1000000+1.)/1000000;
        points[i].first = cos(2*M_PI*fi)*sqrt(-2*log(r));
        points[i].second = sin(2*M_PI*fi)*sqrt(-2*log(r));
    }
    Graph graph(size);
    for(int i = 0; i < size; ++i)
        graph[i].resize(size);
    for(int i = 0; i < size; ++i){
        for(int j = 0; j <= i; ++j){
            graph[i][j] = graph[j][i] = sqrt((points[i].first-points[j].first)*(points[i].first-points[j].first) + (points[i].second-points[j].second)*(points[i].second-points[j].second));
        }
    }
    return graph;
}
