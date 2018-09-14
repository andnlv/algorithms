//
//  main.cpp
//  I
//
//  Created by Andrey Danilov on 28.11.15.
//  Copyright © 2015 Andrey Danilov. All rights reserved.
//

#include <iostream>
#include <stdio.h>
struct Node{
    int d;
    Node *prev;
};
void push(Node **top, int d){
    Node *t = new Node;
    t->d = d;
    t-> prev = *top;
    *top = t;
}
int pop(Node **top){
    int d = (*top)->d;
    Node *t = *top;
    *top = (*top)->prev;
    delete t;
    return d;
}
void clear(Node **top){
    Node *t = *top;
    while(t){
        t = (*top)->prev;
        delete *top;
        *top = t;
    }
}
int find(Node *top, int d){
    int i = 1;
    Node *p = top;
    for(; p && p-> d != d; p = p-> prev) ++i;
    if(p) return i;
    return 0;
}
using namespace std;
int main(int argc, const char * argv[]) {
    Node *p0 = 0, *p = 0, *t = 0;
    int a[2][4000], n, d, head = 1, counter = 0;
    scanf("%d\n", &n);
    for(int i = 0; i < n; ++i){
        scanf("%d", &d);
        push(&p0, d);
    }
    for(int i = 0; i < n; ++i)
        push(&p, pop(&p0));
    while(p || t){
        d = 0;
        n = find(p, head);
        if(!n){
            printf("0");
            return 0;
        }
        for(int i = 0; i < n; ++i)
            push(&t, pop(&p));
        a[0][counter] = 1;
        a[1][counter++] = n;
        n = head;
        for(Node *k = t; k && k->d == n; k = k->prev) ++n;
        n -= head;
        head += n;
        for(int i = 0; i < n; ++i) pop(&t);
        a[0][counter] = 2;
        a[1][counter++] = n;
    }
    for(int i = 0; i < counter; ++i) printf("%d %d\n", a[0][i], a[1][i]);
    return 0;
}
