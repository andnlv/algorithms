//
//  main.cpp
//  Game15
//
//  Created by Andrey Danilov on 12.10.16.
//  Copyright © 2016 Andrey Danilov. All rights reserved.
//

#include <iostream>
#include <unordered_set>
#include <vector>
#include <fstream>
#include "Solver.hpp"

int main(int argc, const char * argv[]) {
    std::unordered_set<Vertex> visitedVertices; // хеш-таблица с посещёнными вершинами
    std::vector<const Vertex*> heap; // очередь вершин в Astar
    std::ifstream in("puzzle.in", std::fstream::in); // файл ввода
    std::ofstream out("puzzle.out", std::fstream::out); // файл вывода
    Vertex start = readInput(std::cin); // чтение данных
    push_heap(heap, &*visitedVertices.insert(start).first); // кладём в очередь первую вершину
    if(isSolved(start)) // если решено выводим 0
        std::cout << 0 << "\n\n";
    else if(isSolving(start)){ //если решается решаем
        clock_t t1 = clock();
        printAnswer(visitedVertices, AStar(visitedVertices, heap), std::cout);
        clock_t t2 = clock();
        std::cout << "time = " << double(t2-t1)/CLOCKS_PER_SEC << "\n";
    }
    else // если не решается выводим 0
        std::cout << -1 << "\n";
    in.close();
    out.close();
    return 0;
}
