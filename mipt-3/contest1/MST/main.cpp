//
//  main.cpp
//  Kruskal
//
//  Created by Andrey Danilov on 14.10.16.
//  Copyright © 2016 Andrey Danilov. All rights reserved.
//

#include <iostream>
#include "Algorithm.hpp"
#include <fstream>
int main(int argc, const char * argv[]) {
    std::ifstream in("kruskal.in");
    std::ofstream out("kruskal.out");
    out << Boruvka(read_graph(in));
    return 0;
}