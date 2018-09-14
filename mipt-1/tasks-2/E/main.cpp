//
//  main.cpp
//  E
//
//  Created by Andrey Danilov on 27.11.15.
//  Copyright © 2015 Andrey Danilov. All rights reserved.
//

#include <iostream>
#include <stdio.h>
struct Node{
    Node *prev, *next;
    int d;
};
void pushFront(Node **begin, Node **end, int d){
    if(*begin){
        Node *t = new Node;
        t-> d = d;
        t-> next = *begin;
        t->prev = 0;
        (*begin)-> prev = t;
        *begin = t;
    }
    else{
        *begin = *end = new Node;
        (*begin)->d = d;
        (*begin)-> next = 0;
        (*begin)-> prev = 0;
    }
}
void pushBack(Node **begin, Node **end, int d){
    if(*end){
        Node *t = new Node;
        t-> d = d;
        t-> next = 0;
        t->prev = *end;
        (*end)-> next = t;
        *end = t;
    }
    else{
        *begin = *end = new Node;
        (*begin)->d = d;
        (*begin)-> next = 0;
        (*begin)-> prev = 0;
    }
}
int popFront(Node **begin, Node **end){
    int d = (*begin)->d;
    if((*begin)->next){
        Node *t = *begin;
        *begin = t->next;
        (*begin)->prev = 0;
        delete t;
    }
    else{
        delete *begin;
        *begin = *end = 0;
    }
    return d;
}
int popBack(Node **begin, Node **end){
    int d = (*end)->d;
    if((*end)->prev){
        Node *t = *end;
        *end = t->prev;
        (*end)->next = 0;
        delete t;
    }
    else{
        delete *end;
        *begin = *end = 0;
    }
    return d;
}
void clear(Node **begin, Node **end){
    while(*end != *begin){
        *begin = (*begin)-> next;
        delete (*begin)-> prev;
    }
    delete *end;
    *end = *begin = 0;
}

int main(int argc, const char * argv[]) {
    Node *begin = 0, *end = 0;
    int n, size = 0;
    char s[11];
    scanf("%d", &n);
    for(int i = 0; i < n; ++i){
        scanf("%s", s);
        if(s[1] == 'u' && s[5] == 'f'){
            int d;
            scanf("%d", &d);
            pushFront(&begin, &end, d);
            printf("ok\n");
            ++size;
        }
        else if(s[1] == 'u' && s[5] == 'b'){
            int d;
            scanf("%d", &d);
            pushBack(&begin, &end, d);
            printf("ok\n");
            ++size;
        }
        else if(s[1] == 'o' && s[4] == 'f'){
            if(begin){
                printf("%d\n", popFront(&begin, &end));
                --size;
            }
            else
                printf("error\n");
        }
        else if(s[1] == 'o' && s[4] == 'b'){
            if(begin){
                printf("%d\n", popBack(&begin, &end));
                --size;
            }
            else
                printf("error\n");
        }
        else if(s[0] == 'f'){
            if(begin)
                printf("%d\n", begin->d);
            else
                printf("error\n");
        }
        else if(s[0] == 'b'){
            if(begin)
                printf("%d\n", end->d);
            else
                printf("error\n");
        }
        else if(s[0] == 's'){
            printf("%d\n", size);
        }
        else if(s[0] == 'c'){
            clear(&begin, &end);
            printf("ok\n");
            size = 0;
        }
    }
    return 0;
}







