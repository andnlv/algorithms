//
//  main.cpp
//
//
//  Created by Andrey Danilov on 21.10.16.
//  Copyright © 2016 Andrey Danilov. All rights reserved.
//

#include <iostream>
#include <unordered_map>
#include <fstream>
#include <string>
#include <vector>

void algorithm(const std::string &t, const std::string &p){
    size_t n = t.size();
    size_t m = p.size();
    std::vector<int> z(m, 0);
    int l = 0;
    int r = 0;
    for (int i = 1; i < m; ++i){
        if (i <= r)
            z[i] = std::min(r - i + 1, z[i - l]);
        while(i + z[i] < m && p[z[i]] == p[i + z[i]])
            ++z[i];
        if(i + z[i] - 1 > r){
            l = i;
            r = i + z[i] - 1;
        }
    }
    l = 0;
    r = 0;
    int x;
    for (int i = 0; i < n; ++i) {
        x = 0;
        if (i <= r)
            x = std::min(r - i + 1, z[i - l]);
        while(x < m && i + x < n && p[x] == t[i + x])
            ++x;
        if(x == m)
            std::cout << i << " ";
        if(i + x - 1 > r){
            l = i;
            r = i + x - 1;
        }
    }
}

int main(int argc, const char * argv[]) {
    std::string t, p;
    std::cin >> p >> t;
    algorithm(t, p);
    return 0;
}