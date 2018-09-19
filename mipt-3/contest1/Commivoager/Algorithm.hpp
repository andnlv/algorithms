//
//  Algorithm.hpp
//  Commivoager
//
//  Created by Andrey Danilov on 14.11.16.
//  Copyright © 2016 Andrey Danilov. All rights reserved.
//

#ifndef Algorithm_hpp
#define Algorithm_hpp

#include <vector>

enum Color{B, W};

template<class T>
struct vertex : std::vector<T>{
    mutable Color color;
};

typedef std::vector<vertex<double>> Graph;

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

double count_weight(const std::vector<int>& way, const Graph& graph); //считает вес цикла на вершинах
double find_gamilton(const Graph &graph); // ищет вес минимального гамильтонова цикла полным перебором
double Boruvka(const Graph& graph); // ищет вес гамильтонова цикла построеном на минимальном остовном дереве
Graph generate_graph(int size, int seed); // генерирует случайный граф

#endif /* Algorithm_hpp */
