//
//  Algorithm.hpp
//  Hamming distance
//
//  Created by Andrey Danilov on 08.12.16.
//  Copyright © 2016 Andrey Danilov. All rights reserved.
//

#ifndef Algorithm_hpp
#define Algorithm_hpp

#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <queue>

enum class Color{W, B};

struct vertex : std::unordered_map<int, int>{ // Вершина для графа
    int distance; // Растояние от истока
    char stringName; // К какой строке относится вершина (s или p)
    int stringPosition; // позиция в строке
    Color color;
    unordered_map<int, int>::iterator it;
};

typedef std::vector<vertex> Graph;

void makeLayeredNetwork(Graph &graph, int s, int t); // построение слоистой сети для диницы

int dfsRecursive(Graph &graph, int s, int &t, int flowLeft); // построение увеличивающего потока

int Dinitz(Graph& graph, int s, int t); // диница

void makeGraph(std::string &s, std::string &p, Graph &graph, int &totalScore); // строит граф из строки и шаблона

void algorithm(std::string &s, std::string &p, int &totalScore);

#endif /* Algorithm_hpp */
