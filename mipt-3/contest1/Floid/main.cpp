//
//  main.cpp
//  Floid
//
//  Created by Andrey Danilov on 14.10.16.
//  Copyright © 2016 Andrey Danilov. All rights reserved.
//

#include <iostream>
#include <fstream>
#include "Graph.hpp"
#include "Algorithm.hpp"

int main(int argc, const char * argv[]) {
    std::ifstream in("floyd.in");
    std::ofstream out("floyd.out");
    Graph<WEdge> g;
    readGraph(g, in);
    Floid(g, out);
    in.close();
    out.close();
    return 0;
}
