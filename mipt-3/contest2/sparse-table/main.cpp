//
//  main.cpp
//  Sparse Table
//
//  Created by Andrey Danilov on 15.12.16.
//  Copyright © 2016 Andrey Danilov. All rights reserved.
//

#include <iostream>
#include <vector>
#include "Algorithm.hpp"

int main(int argc, const char * argv[]) {
    int n, m;
    std::cin >> n >> m;
    std::vector<int> v(n);
    for(int i = 0; i < n; ++i)
        std::cin >> v[i];
    std::vector<std::vector<std::pair<int, int>>> table(make_sparse_table(v));
    for(int k = 0; k < m; ++k){
        int i, j;
        std::cin >> i >> j;
        --i; --j;
        int l = log(j - i);
        std::cout << v[two_least(table[l][i], table[l][j-pow(l)+1], v).second] << "\n";
    }
    return 0;
}


