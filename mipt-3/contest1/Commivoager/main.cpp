//
//  main.cpp
//  Commivoager
//
//  Created by Andrey Danilov on 14.11.16.
//  Copyright © 2016 Andrey Danilov. All rights reserved.
//

#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <fstream>
#include <algorithm>
#include <cmath>
#include <stack>
#include <cassert>
#include <iomanip>
#include "Algorithm.hpp"

const int number_of_experiments = 100;

/*
 Программа выводит для графов размером от 3 до 11:
 mean_real - средний вес минимальных гамильтоновых циклов
 mean_approx - средний вес приближённых гамильтоновых циклов
 diff - относительная среднеквадратичная погрешность 
 
 Видно, что относительная погрешность увеличивается с размером графа, что весьма логичо.
*/
int main(int argc, const char * argv[]) {
    srand(8768);
    std::cout << std::setprecision(3);
    std::cout << std::fixed;
    for(int i = 3; i <= 11; ++i){
        double mean_real = 0, mean_approx = 0, diff = 0;
        std::cout << "Graph size " << i << ":\n";
        for(int j = 0; j < number_of_experiments; ++j){
            Graph graph = generate_graph(i, rand());
            double w1 = find_gamilton(graph);
            double w2 = Boruvka(graph);
            //std::cout << w1 << " " << w2 <<"\n";
            mean_real += w1;
            mean_approx += w2;
            diff += (w1-w2)*(w1-w2);
        }
        mean_real /= number_of_experiments;
        mean_approx /= number_of_experiments;
        diff = sqrt(diff/number_of_experiments)/mean_real;
        std::cout << "mean_real = " << mean_real << "\n"
                  << "mean_approx = " << mean_approx << "\n"
                  << "diff = " << diff << "\n";
    }
    return 0;
}
