//
//  main.cpp
//  HelenProblem1
//
//  Created by Andrey Danilov on 11.04.16.
//  Copyright © 2016 Andrey Danilov. All rights reserved.
//

#include <iostream>
#include <vector>
using namespace std;
enum Color {white, grey, black};
struct Node{
    vector<int> tasks;
    Color color;
};

bool f(int n, vector<Node> &list, vector<int> &answer){
    list[n].color = grey;
    bool availability = true;
    for(auto i : list[n].tasks){
        if(list[i].color == white)
            availability = availability && f(i, list, answer);
        if(list[i].color == grey)
            availability = false;
    }
    answer.push_back(n);
    list[n].color = black;
    return availability;
}
int main(int argc, const char * argv[]) {
    int n;
    cin >> n;
    cin.get();
    vector<Node> list;
    Node node;
    node.color = white;
    for(int i = 1; i <= n; ++i){
        node.tasks.push_back(i);
    }
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
    
    vector<int> answer;
    if(f(0, list, answer)){
        for(int i = 0; i < answer.size()-1; ++i){
            cout << answer[i] << " ";
        }
    }
    else{
        cout << 0;
    }
    return 0;
}
