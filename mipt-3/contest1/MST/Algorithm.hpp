//
//  Algorithm.hpp
//  Kruskal
//
//  Created by Andrey Danilov on 14.10.16.
//  Copyright © 2016 Andrey Danilov. All rights reserved.
//

#ifndef Algorithm_hpp
#define Algorithm_hpp

#include <vector>
#include <unordered_map>
#include <iostream>

class DSDS{ // Система не пересекающихся множеств
public:
    int find(int x); // Находит главную вершину свзности
    void merge(int x, int y); // Объединяет связности
    DSDS(size_t size);
private:
    struct Node{
        int parent;
        int rank;
    };
    std::vector<Node> vertices;
};

long Boruvka(std::vector<std::unordered_map<int,int>>);

std::vector<std::unordered_map<int,int>>read_graph(std::istream& in);
#endif /* Algorithm_hpp */
