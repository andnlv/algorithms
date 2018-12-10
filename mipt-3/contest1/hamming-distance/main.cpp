//
//  main.cpp
//  Hamming distance
//
//  Created by Andrey Danilov on 16.11.16.
//  Copyright © 2016 Andrey Danilov. All rights reserved.
//

#include <iostream>
#include "Algorithm.hpp"

int main(int argc, const char * argv[]) {
    std::string s, p;
    std::cin >> s >> p;
    int score;
    algorithm(s, p, score);
    std::cout << score << "\n" << s << "\n" << p << "\n";
    return 0;
}
