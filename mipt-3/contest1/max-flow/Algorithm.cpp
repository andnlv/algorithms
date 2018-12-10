//
//  Algorithm.cpp
//  max flow
//
//  Created by Andrey Danilov on 08.12.16.
//  Copyright © 2016 Andrey Danilov. All rights reserved.
//

#include "Algorithm.hpp"

std::vector<int> find_shortest_way(const Graph &graph, int start, int target){
    std::vector<std::pair<int, int>> que;
    que.push_back({start, -1});
    int i = 0;
    for(int i = 0; i < graph.size(); ++i)
        graph[i].color = vertex::W;
    graph[start].color = vertex::B;
    while(i < que.size()){
        int current = que[i].first;
        if(current == target){
            std::vector<int> result;
            std::pair<int, int> p = que[i];
            while(i != -1){
                result.push_back(que[i].first);
                i = que[i].second;
            }
            return std::vector<int>(result.rbegin(), result.rend());
        }
        for(auto it = graph[current].begin(); it != graph[current].end(); ++it){
            if(it->second > 0 && graph[it->first].color == vertex::W){
                que.push_back({it->first, i});
                graph[it->first].color = vertex::B;
            }
        }
        ++i;
    }
    return std::vector<int>();
}

int find_max_flow(Graph &graph, int start, int target){
    std::vector<int> shortes_way;
    int max_flow = 0;
    while(!(shortes_way = find_shortest_way(graph, start, target)).empty()){
        int min_weight = INT32_MAX;
        for(auto it = shortes_way.begin(); it+1 != shortes_way.end(); ++it)
            min_weight = std::min(min_weight, graph[*it][*(it+1)]);
        for(auto it = shortes_way.begin(); it+1 != shortes_way.end(); ++it){
            graph[*it][*(it+1)] -= min_weight;
            graph[*(it+1)][*it] += min_weight;
        }
        max_flow += min_weight;
    }
    return max_flow;
}

std::tuple<Graph, int, int> read_graph(std::istream &in){
    int k, e, s, t;
    in >> k;
    if(k == 0)
        return std::make_tuple(Graph(), -1, -1);
    Graph graph(k);
    in >> s >> t >> e;
    --s; --t;
    for(int i = 0; i < e; ++i){
        int u, v, w;
        in >> u >> v >> w;
        --u; --v;
        if(graph[u].count(v) == 0){
            graph[u][v] = w;
            graph[v][u] = w;
        }
        else{
            graph[u][v] += w;
            graph[v][u] += w;
        }
    }
    return std::make_tuple(graph, s, t);
}
