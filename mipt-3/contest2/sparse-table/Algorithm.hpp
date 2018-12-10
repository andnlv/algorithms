//
//  Algorithm.hpp
//  Sparse Table
//
//  Created by Andrey Danilov on 16.12.16.
//  Copyright © 2016 Andrey Danilov. All rights reserved.
//

#ifndef Algorithm_hpp
#define Algorithm_hpp

#include <vector>
#include <algorithm>
#include <cassert>

int log(int x); // двоичный логарифм округлённый вниз

int pow(int x); // степень двойки

std::pair<int, int> two_least(std::pair<int, int>& p1, std::pair<int, int>& p2, const std::vector<int>& v);
// возвращает из двух пар первой и второй порядковых статистик первую и вторую порядковую статистику их объедиения

std::vector<std::vector<std::pair<int, int>>> make_sparse_table(const std::vector<int> &v); //создаёт sparse table

#endif /* Algorithm_hpp */