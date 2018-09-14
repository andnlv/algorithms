//
//  main.cpp
//  K
//
//  Created by Andrey Danilov on 30.11.15.
//  Copyright © 2015 Andrey Danilov. All rights reserved.
//

#include <iostream>
#include <stdio.h>
struct Node{
    int d;
    Node *prev;
    Node *next;
};
void pushBack(Node **begin, Node **mid, Node **end, int d, int &size){
    Node *t = new Node;
    t-> d = d;
    t-> next = 0;
    t-> prev = *end;
    ++size;
    if(*begin){
        (*end)-> next = t;
        if(size%2) *mid = (*mid)-> next;
    }
    else
        *mid = *begin = t;
    *end = t;
}
void pushMid(Node **begin, Node **mid, Node **end, int d, int &size){
    Node *t = new Node;
    ++size;
    if(*begin){
        t-> d = d;
        t-> prev = *mid;
        t-> next = (*mid)-> next;
        if((*mid)-> next) (*mid)-> next-> prev = t;
        else *end = t;
        (*mid)-> next = t;
        if(size%2) *mid = (*mid)-> next;
    }
    else{
        t-> d = d;
        t-> next = t-> prev = 0;
        *end = *begin = *mid = t;
    }
}
int popFront(Node **begin, Node **mid, Node **end, int &size){
    int d = (*begin)-> d;
    Node *t = *begin;
    *begin = (*begin)-> next;
    if(*begin) (*begin)-> prev = 0;
    else *mid = *end = 0;
    --size;
    if(size%2) *mid = (*mid)-> next;
    delete t;
    return d;
}
int main(int argc, const char * argv[]) {
    Node *begin = 0, *mid = 0, *end = 0;
    int n, d, size = 0;
    char c;
    scanf("%d", &n);
    for(int i = 0; i < n; ++i){
        scanf("%c", &c);
        if(c == '+'){
            scanf("%d", &d);
            pushBack(&begin, &mid, &end, d, size);
        }
        else if(c == '*'){
            scanf("%d", &d);
            pushMid(&begin, &mid, &end, d, size);
        }
        else if(c == '-'){
            printf("%d\n", popFront(&begin, &mid, &end, size));
        }
        else if(c == '\n'){
            --i;
        }
    }
    return 0;
}
