
//
//  main.cpp
//  max flow
//
//  Created by Andrey Danilov on 09.11.16.
//  Copyright © 2016 Andrey Danilov. All rights reserved.
//

#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <fstream>
#include "Algorithm.hpp"
int main(int argc, const char * argv[]) {
    while(true){
        auto input = read_graph(std::cin);
        if(std::get<1>(input) == -1){
            return 0;
        }
        std::cout << find_max_flow(std::get<0>(input), std::get<1>(input), std::get<2>(input)) << "\n";
    }
}