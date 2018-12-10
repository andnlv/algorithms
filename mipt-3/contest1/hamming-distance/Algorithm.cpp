//
//  Algorithm.cpp
//  Hamming distance
//
//  Created by Andrey Danilov on 08.12.16.
//  Copyright © 2016 Andrey Danilov. All rights reserved.
//

#include "Algorithm.hpp"


void makeLayeredNetwork(Graph &graph, int s, int t){
    for(int i = 0; i < graph.size(); ++i)
        graph[i].distance = -1;
    graph[s].distance = 0;
    std::queue<int> bfsQueue;
    bfsQueue.push(s);
    while(!bfsQueue.empty()){
        int current = bfsQueue.front();
        bfsQueue.pop();
        for(auto it = graph[current].begin(); it != graph[current].end(); ++it){
            if(it->second > 0 && graph[it->first].distance < 0){
                graph[it->first].distance = graph[current].distance + 1;
                bfsQueue.push(it->first);
            }
        }
    }
};

int dfsRecursive(Graph &graph, int s, int &t, int flowLeft){
    if(flowLeft == 0)
        return 0;
    if(s == t)
        return flowLeft;
    for(; graph[s].it != graph[s].end(); ++graph[s].it) {
        if (graph[s].distance + 1 != graph[graph[s].it->first].distance)
            continue;
        int flow = dfsRecursive(graph, graph[s].it->first, t, std::min(flowLeft, graph[s].it->second));
        if (flow > 0) {
            graph[s].it->second -= flow;
            graph[graph[s].it->first][s] += flow;
            return flow;
        }
    }
    return 0;
}

int Dinitz(Graph& graph, int s, int t){
    int maxFlow = 0;
    while (true) {
        makeLayeredNetwork(graph, s, t);
        if(graph[t].distance == -1)
            break;
        for(int i = 0; i < graph.size(); ++i)
            graph[i].it = graph[i].begin();
        while(int flow = dfsRecursive(graph, s, t, INT32_MAX))
            maxFlow += flow;
    }
    return maxFlow;
};

void makeGraph(std::string &s, std::string &p, Graph &graph, int &totalScore){
    graph.clear();
    totalScore = 0;
    std::unordered_map<int, int> positionS;
    std::unordered_map<int, int> positionP;
    graph.push_back(vertex());
    graph.back().stringName = '0';
    graph.push_back(vertex());
    graph.back().stringName = '1';
    for(int i = 0; i < s.length(); ++i)
        if(s[i] == '?'){
            auto pos(positionS.size());
            positionS[i] = 2 + int(pos);
            graph.push_back(vertex());
            graph.back().stringName = 's';
            graph.back().stringPosition = i;
        }
    for(int i = 0; i < p.length(); ++i)
        if(p[i] == '?'){
            auto pos(positionP.size());
            positionP[i] = 2 + int(positionS.size() + pos);
            graph.push_back(vertex());
            graph.back().stringName = 'p';
            graph.back().stringPosition = i;
        }
    for(int i = 0; i < s.length() - p.length() + 1; ++i){
        for(int j = 0; j < p.length(); ++j){
            if(s[i+j] != '?' && p[j] != '?')
                totalScore += s[i+j] != p[j];
            else if(s[i+j] == '?' && p[j] == '?'){
                if(graph[positionS[i+j]].count(positionP[j]) == 0){
                    graph[positionS[i+j]][positionP[j]] = 1;
                    graph[positionP[j]][positionS[i+j]] = 1;
                }
                else{
                    graph[positionS[i+j]][positionP[j]] += 1;
                    graph[positionP[j]][positionS[i+j]] += 1;
                }
            }
            else if(s[i+j] == '?'){
                if(graph[positionS[i+j]].count(p[j] == '1') == 0){
                    graph[positionS[i+j]][p[j] == '1'] = 1;
                    graph[p[j] == '1'][positionS[i+j]] = 1;
                }
                else{
                    graph[positionS[i+j]][p[j] == '1'] += 1;
                    graph[p[j] == '1'][positionS[i+j]] += 1;
                }
            }
            else if(p[j] == '?'){
                if(graph[positionP[j]].count(s[i+j] == '1') == 0){
                    graph[positionP[j]][s[i+j] == '1'] = 1;
                    graph[s[i+j] == '1'][positionP[j]] = 1;
                }
                else{
                    graph[positionP[j]][s[i+j] == '1'] += 1;
                    graph[s[i+j] == '1'][positionP[j]] += 1;
                }
            }
        }
    }
}

void algorithm(std::string &s, std::string &p, int &totalScore){
    Graph graph;
    makeGraph(s, p, graph, totalScore);
    totalScore += Dinitz(graph, 0, 1);
    makeLayeredNetwork(graph, 0, 1);
    for(int i = 0; i < graph.size(); ++i){
        if(graph[i].distance == -1){
            if(graph[i].stringName == 's')
                s[graph[i].stringPosition] = '1';
            else if(graph[i].stringName == 'p')
                p[graph[i].stringPosition] = '1';
        }
        else{
            if(graph[i].stringName == 's')
                s[graph[i].stringPosition] = '0';
            else if(graph[i].stringName == 'p')
                p[graph[i].stringPosition] = '0';
        }
    }
}
