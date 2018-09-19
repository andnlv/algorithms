//
//  Algorithm.hpp
//  Aho-Corasik
//
//  Created by Andrey Danilov on 11.12.16.
//  Copyright © 2016 Andrey Danilov. All rights reserved.
//

#ifndef Algorithm_hpp
#define Algorithm_hpp

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <map>
#include <cassert>
#include <sstream>
#include <queue>

void read_pattern(std::pair<std::vector<std::string>, std::vector<int>>& input, size_t &lenght, std::istream& in);

class BorTree{
public:
    BorTree(const std::vector<std::string>& patterns); // строит дерево по вектору шаблонов
    std::vector<int> checkForString(const std::string &s, const std::vector<int> &begins, const std::vector<std::string> &strings); // прогоняет строку через бор, возвращает вектор с количеством шаблонов начинающихся в i-ой позиции
private:
    struct vertex{
        char c; // символ вершины
        int parent; // номер родителя
        std::vector<int> stringNumbers; // номера строк которые оканчиваются в этом символе
        std::map<char, int> next; // все потомки
        std::map<char, int> change; // переход по символу
        int sufficsLink; // суффиксная ссылка
    };
    const int patternsNumber; // количество шаблонов
    std::vector<vertex> data; // само дерево
    int addVertex(char c, int prev);
    int nextChar(int n, const char &c);
    void addString(const std::string &s, int n);
    void countSufficsLinks();
    void recountStringsEnds();
};

std::string algorithm(std::istream &in);

#endif /* Algorithm_hpp */
