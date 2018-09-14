//
//  main.cpp
//  B
//
//  Created by Andrey Danilov on 26.11.15.
//  Copyright © 2015 Andrey Danilov. All rights reserved.
//

#include <iostream>
#include <stdio.h>
struct Node{
    int d;
    Node *next;
};
void enqueue(Node **begin,  Node **end, int d){
    Node *t = new Node;
    t-> d = d;
    t-> next = 0;
    if(*end)
        (*end)-> next = t;
    else{
        *begin = t;
    }
    *end = t;
}
int dequeue(Node **begin, Node **end){
    int d = (*begin)-> d;
    if((*begin)-> next){
        Node *t = *begin;
        *begin = (*begin)-> next;
        delete t;
    }
    else{
        delete *begin;
        *begin = *end = 0;
    }
    return d;
}
int size(Node *begin){
    int i = 0;
    for(Node *t = begin; t; t = t->next) ++i;
    return i;
}
void clear(Node **begin, Node **end){
    Node *t = *begin;
    while(t){
        t = (*begin)->next;
        delete *begin;
        *begin = t;
    }
    *end = 0;
}
int main(int argc, const char * argv[]) {
    int n;
    char s[8];
    Node *begin = 0, *end = 0;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%s", s);
        switch (s[1]) {
            case 'n':
                int d;
                scanf("%d", &d);
                enqueue(&begin, &end, d);
                printf("ok\n");
                break;
            case 'e':
                if(begin)
                    printf("%d\n", dequeue(&begin, &end));
                else
                    printf("error\n");
                break;
            case 'r':
                if(begin)
                    printf("%d\n", begin->d);
                else
                    printf("error\n");
                break;
            case 'i':
                printf("%d\n", size(begin));
                break;
            case 'l':
                clear(&begin, &end);
                printf("ok\n");
                break;
        }
    }
    return 0;
}
