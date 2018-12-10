//
//  Algorithm.cpp
//  Sparse Table
//
//  Created by Andrey Danilov on 16.12.16.
//  Copyright © 2016 Andrey Danilov. All rights reserved.
//

#include "Algorithm.hpp"

int log(int x){
    int res;
    assert(x != 0);
    for(res = 0; x != 1; ++res, x /= 2);
    return res;
}


int pow(int x){
    int res = 1;
    for(int i = 0; i < x; ++i, res *= 2);
    return res;
}

std::pair<int, int> two_least(std::pair<int, int>& p1, std::pair<int, int>& p2, const std::vector<int>& v){
    std::pair<int, int> res;
    if(p1.first == p1.second){
        if(v[p1.first] < v[p2.first])
            res = {p1.first, p2.first};
        else
            res = {p2.first, p1.first};
        return res;
    }
    if(v[p1.first] < v[p2.first]){
        res.first = p1.first;
        res.second = (v[p2.first] < v[p1.second] ? p2.first : p1.second);
    }
    else{
        res.first = p2.first;
        if(p1.first == p2.first)
            res.second = (v[p1.second] < v[p2.second] ? p1.second : p2.second);
        else
            res.second = (v[p1.first] < v[p2.second] ? p1.first : p2.second);
    }
    return res;
}

std::vector<std::vector<std::pair<int, int>>> make_sparse_table(const std::vector<int> &v){
    std::vector<std::vector<std::pair<int, int>>> table((log(int(v.size())))+1);
    table[0].resize(v.size());
    for(int j = 0; j < v.size(); ++j){
        table[0][j] = {j, j};
    }
    for(int i = 1; i < table.size(); ++i){
        table[i].resize(v.size() - pow(i) + 1);
        for(int j = 0; j < table[i].size(); ++j){
            table[i][j] = two_least(table[i-1][j], table[i-1][j+pow(i-1)], v);
        }
    }
    return move(table);
}
