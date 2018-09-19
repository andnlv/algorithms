//
//  Algorithm.cpp
//  Aho-Corasik
//
//  Created by Andrey Danilov on 11.12.16.
//  Copyright © 2016 Andrey Danilov. All rights reserved.
//

#include "Algorithm.hpp"

void read_pattern(std::pair<std::vector<std::string>, std::vector<int>>& input, size_t &lenght, std::istream& in){
    std::string s;
    in >> s;
    lenght = s.length();
    std::vector<std::string> patterns;
    std::vector<int> distances;
    int subStringBegin = -1;
    std::string currentSubStr;
    for(int i = 0; i < s.length(); ++i){
        if(s[i] == '?'){
            if(subStringBegin != -1){
                patterns.push_back(currentSubStr);
                distances.push_back(subStringBegin);
                subStringBegin = -1;
                currentSubStr.clear();
            }
        }
        else{
            if(subStringBegin == -1)
                subStringBegin = i;
            currentSubStr.push_back(s[i]);
        }
    }
    if(subStringBegin != -1){
        patterns.push_back(currentSubStr);
        distances.push_back(subStringBegin);
    }
    input = {patterns, distances};
};

BorTree::BorTree(const std::vector<std::string>& patterns)
:patternsNumber((int) patterns.size()){
    data.push_back(vertex());
    data.back().parent = 0;
    for(int i = 0; i < patterns.size(); ++i)
        this->addString(patterns[i], i);
    countSufficsLinks();
    recountStringsEnds();
}

int BorTree::nextChar(int n, const char &c){
    std::map<char, int>::iterator it;
    if((it = data[n].change.find(c)) != data[n].change.end())
        return it->second;
    if(n == 0 && data[n].next.count(c) == 0)
        return data[n].change[c] = 0;
    if(data[n].next.count(c) == 0)
        return data[n].change[c] = nextChar(data[n].sufficsLink, c);
    return data[n].change[c] = data[n].next[c];
}

void BorTree::addString(const std::string &s, int n){
    int i = 0;
    int currentVertex = 0;
    std::map<char, int>::iterator it;
    while(i < s.length() && (it = data[currentVertex].next.find(s[i])) != data[currentVertex].next.end()){
        ++i;
        currentVertex = it->second;
    }
    for(int j = i; j < s.length(); ++j)
        currentVertex = addVertex(s[j], currentVertex);
    data[currentVertex].stringNumbers.push_back(n);
}

int BorTree::addVertex(char c, int prev){
    assert(data[prev].next.count(c) == 0);
    data.push_back(vertex());
    data.back().c = c;
    data.back().parent = prev;
    data.back().sufficsLink = -1;
    data[prev].next[c] = (int) data.size() - 1;
    return (int) data.size() - 1;
}

void BorTree::countSufficsLinks(){
    std::queue<int> bfsQueue;
    bfsQueue.push(0);
    while(!bfsQueue.empty()){
        int i = bfsQueue.front();
        bfsQueue.pop();
        for(auto a : data[i].next)
            bfsQueue.push(a.second);
        if(data[i].parent == 0)
            data[i].sufficsLink = 0;
        else
            data[i].sufficsLink = nextChar(data[data[i].parent].sufficsLink, data[i].c);
    }
}

void BorTree::recountStringsEnds(){
    std::queue<int> bfsQueue;
    bfsQueue.push(0);
    while(!bfsQueue.empty()){
        int i = bfsQueue.front();
        bfsQueue.pop();
        for(auto a : data[i].next)
            bfsQueue.push(a.second);
        std::vector<int> prevEnds = data[data[i].sufficsLink].stringNumbers;
        data[i].stringNumbers.insert(data[i].stringNumbers.end(), prevEnds.begin(), prevEnds.end());
    }
}

std::vector<int> BorTree::checkForString(const std::string &s, const std::vector<int> &begins, const std::vector<std::string> &strings){
    int current = 0;
    std::vector<int> entries(s.length(), 0);
    std::vector<size_t> l(begins.size());
    for(int i = 0; i < l.size(); ++i){
        l[i] = begins[i] + strings[i].length() - 1;
    }
    for(int i = 0; i < s.length(); ++i){
        current = nextChar(current, s[i]);
        for(auto j : data[current].stringNumbers)
            if(i - l[j] < entries.size())
                ++entries[i-l[j]];
    }
    return entries;
}


std::string algorithm(std::istream &in){
    std::string answer;
    std::pair<std::vector<std::string>, std::vector<int>> patterns;
    size_t patternLength, strLength;
    read_pattern(patterns, patternLength, in);
    BorTree borTree(patterns.first);
    std::vector<int> entries;
    std::string str;
    in >> str;
    strLength = str.length();
    entries = borTree.checkForString(str, patterns.second, patterns.first);
    if(patterns.first.size() == 0){
        for(int i = 0; i <= strLength - patternLength; ++i)
            answer +=  std::to_string(i) + " ";
        return answer;
    }
    for(int i = 0; i <= int(entries.size()) - int(patternLength); ++i){
        if(entries[i] == patterns.first.size())
            answer += std::to_string(i) + " ";
    }
    return answer;
}
