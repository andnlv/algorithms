//
//  Solver.hpp
//  Game15
//
//  Created by Andrey Danilov on 12.10.16.
//  Copyright © 2016 Andrey Danilov. All rights reserved.
//

#ifndef Solver_hpp
#define Solver_hpp

#include <iostream>
#include <vector>
#include <unordered_set>
#include <stack>
#include <cassert>

const unsigned long long power16[16] = {1, 16, 256, 4096, 65536, 1048576, 16777216,
    268435456, 4294967296, 68719476736, 1099511627776, 17592186044416,
    281474976710656, 4503599627370496, 72057594037927936, 1152921504606846976};
#define s 4
const bool searchMinWay = false;
//const int s = 5; // размер поля

enum class Direction{R, U, L, D};

class Vertex {
public:
    struct field {
        #if s > 4
            std::vector<unsigned char>  value; // храним поле в векторе
        #else
            unsigned long long value; // кодируем поле unsigned long long
        #endif
        unsigned char operator [] (int n) const; // возвращает соответствующую клетку поля
        void swap(int i, int j); // меняет местами соответствующие клетки поля
    };
    field box;
    mutable int way; // длина пути
    mutable Direction moveDone; // движение, которым мы попали в эту вершину
    mutable int heap_position; // номер элемента в очереди
    int h; // эвристика

    int countHeuristic() const; // посчёт эвристики
    Vertex(std::vector<unsigned char> a); // инициализация вершины
    Vertex(unsigned long long a);
    std::vector<Direction> availableDirections() const; // возвращает вектор возможных направлений
    Vertex getVertex(Direction dir) const; // возвращает вершину полученную данным перемещением
    bool operator < (const Vertex & other) const; // сравнение для очереди
    bool operator <= (const Vertex & other) const; // сравнение для очереди
    bool operator == (const Vertex & other) const; // сравнение для хеш-таблицы
};

Vertex makeFinish(); // генерирует финишную вершину
const Vertex finishVertex = makeFinish(); // финишная вершина

// хеш-функтор для таблицы
template<>
class std::hash<Vertex>{
public:
    unsigned long long operator()(const Vertex &v) const;
};

void heap_swap(const Vertex*& x, const Vertex*& y); // специальный swap обменивающий значение полей heap_position и самих указателей
// функции для работы с очередью
void sift_up(std::vector<const Vertex*> &heap, size_t n);
void sift_down(std::vector<const Vertex*> &heap, size_t n);
void push_heap(std::vector<const Vertex*> &heap, const Vertex* vertex);
const Vertex* pop_heap(std::vector<const Vertex*> &heap);

Vertex readInput(std::istream& in); // чтение данных
void printAnswer(std::unordered_set<Vertex>& visitedVertices, Vertex finishVertex, std::ostream& out); // вывод данных

bool isSolving(const Vertex& vertex); // проверка на решаемость
bool isSolved(const Vertex& vertex); // проверка на решённость

Vertex AStar(std::unordered_set<Vertex>& visitedVertices, std::vector<const Vertex*>& heap); // алгоритм эвристического поиска Astar

#endif /* Solver_hpp */
