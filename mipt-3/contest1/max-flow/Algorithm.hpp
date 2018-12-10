//
//  Algorithm.hpp
//  max flow
//
//  Created by Andrey Danilov on 08.12.16.
//  Copyright © 2016 Andrey Danilov. All rights reserved.
//

#ifndef Algorithm_hpp
#define Algorithm_hpp

#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <fstream>

struct vertex : std::unordered_map<int, int>{
    enum Color{B, W};
    mutable Color color;
};

typedef std::vector<vertex> Graph;

std::vector<int> find_shortest_way(const Graph &graph, int start, int target); // bfs

int find_max_flow(Graph &graph, int start, int target); // поиск максимального потока

std::tuple<Graph, int, int> read_graph(std::istream &in); // считывание графа

#endif /* Algorithm_hpp */
