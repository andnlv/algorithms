//
//  main.cpp
//  Arbitrage
//
//  Created by Andrey Danilov on 07.10.16.
//  Copyright © 2016 Andrey Danilov. All rights reserved.
//

#include <iostream>
#include "Graph.hpp"
#include "Algorithm.hpp"

int main(int argc, const char * argv[]) {
    Graph<WEdge> g;
    readGraph(g);
    if(searching_for_cycles(g))
        std::cout << "YES";
    else
        std::cout << "NO";
    return 0;
}