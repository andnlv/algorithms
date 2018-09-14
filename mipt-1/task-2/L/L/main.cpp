//
//  main.cpp
//  L
//
//  Created by Andrey Danilov on 30.11.15.
//  Copyright © 2015 Andrey Danilov. All rights reserved.
//

#include <iostream>
#include <stdio.h>
struct Node{
    unsigned int d;
    Node *prev;
};
void push(Node **begin, Node **end, int d){
    Node *t = new Node;
    t-> d = d;
    t-> prev = 0;
    if(*begin){
        (*end)-> prev = t;
        *end = t;
    }
    else{
        *end = *begin = t;
    }
}
int pop(Node **begin, Node **end){
    int d = (*begin)->d;
    Node *prev = (*begin)-> prev;
    delete *begin;
    *begin = prev;
    return d;
}
void clear(Node **front){
    Node *current = (*front), *next;
    while(current){
        next = current;
        current = current->prev;
        delete next;
    }
    *front = 0;
}
unsigned int Max(unsigned int a, unsigned int b){
    if(a > b) return a;
    return b;
}
int main(int argc, const char * argv[]) {
    Node *begin = 0, *end = 0;
    unsigned int n, k, d, max = 0, res = 0;
    scanf("%u%u", &n, &k);
    for(int i = 0; i < k; ++i){
        scanf("%u", &d);
        push(&begin, &end, d);
    }
    for(int i = 0; i < n - k; ++i){
        max = Max(max, pop(&begin, &end));
        scanf("%u", &d);
        res = Max(res, max + d);
        push(&begin, &end, d);
    }
    printf("%u", res);
    clear(&begin);
    return 0;
}







