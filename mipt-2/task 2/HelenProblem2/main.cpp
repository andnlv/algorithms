//
//  main.cpp
//  HelenProblem2
//
//  Created by Andrey Danilov on 11.04.16.
//  Copyright © 2016 Andrey Danilov. All rights reserved.
//

#include <iostream>
#include <vector>
#include <queue>
using namespace std;
enum Color {white, grey, black};
struct Node{
    int parent;
    vector<int> tasks;
    Color color;
};

bool f(int n, vector<Node> &list, queue<int> &quene, int end){
    if(n == end){
        while(list[n].parent != 0){
            cout << list[n].parent << " " << n << "\n";
            n = list[n].parent;
        }
        return true;
    }
    for(auto i : list[n].tasks){
        if(list[i].color == white){
            list[i].parent = n;
            list[i].color = grey;
            quene.push(i);
        }
    }
    list[n].color = black;
    if(quene.empty())
        return false;
    int i = quene.front();
    quene.pop();
    
    return f(i, list, quene, end);
}

int main(int argc, const char * argv[]) {
    int n;
    cin >> n;
    vector<Node> list;
    Node node;
    int begin;
    int end;
    cin >> begin >> end;
    cin.get();
    list.push_back(node);
    for(int i = 0; i < n; ++i){
        node.tasks.clear();
        node.color = white;
        char c;
        int tmp = -1;
        while(true){
            cin.get(c);
            if(c == '\n'){
                if(tmp >= 0)
                    node.tasks.push_back(tmp);
                break;
            }
            else if(c == ' '){
                if(tmp >= 0)
                    node.tasks.push_back(tmp);
                tmp = -1;
            }
            else{
                if(tmp >= 0)
                    tmp = tmp*10 + int(c - '0');
                else
                    tmp = int(c - '0');
            }
        }
        list.push_back(node);
    }
    
    queue<int> quene;
    list[begin].color = grey;
    list[begin].parent = 0;
    if(!f(begin, list, quene, end)){
        cout << "Impossible\n";
    }
    return 0;
}

