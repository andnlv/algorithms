//
//  main.cpp
//  F
//
//  Created by Andrey Danilov on 27.11.15.
//  Copyright © 2015 Andrey Danilov. All rights reserved.
//

#include <iostream>
#include <stdio.h>
struct Node{
    char d;
    Node *prev;
    Node *prevMin;
};
void push(Node **top, char d){
    Node *t = new Node;
    t->d = d;
    t-> prev = *top;
    *top = t;
}
int pop(Node **top){
    char d = (*top)->d;
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

int main(int argc, const char * argv[]) {
    char c;
    Node *top = 0;
    while(1){
        scanf("%c", &c);
        if(c == '\n') break;
        if(c == '(' || c == '{' || c == '[')
            push(&top, c);
        else if(c == ')'){
            if(!top || pop(&top) != '('){
                printf("no");
                return 0;
            }
        }
        else if(c == ']'){
            if(!top || pop(&top) != '['){
                printf("no");
                return 0;
            }
        }
        else if(c == '}')
            if(!top || pop(&top) != '{'){
                printf("no");
                return 0;
            }
    }
    if(top) printf("no");
    else printf("yes");
    return 0;
}
