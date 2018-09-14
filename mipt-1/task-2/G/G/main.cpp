//
//  main.cpp
//  G
//
//  Created by Andrey Danilov on 27.11.15.
//  Copyright © 2015 Andrey Danilov. All rights reserved.
//

#include <iostream>
#include <stdio.h>
struct Node{
    int d;
    Node *prev;
    Node *prevMin;
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

int main(int argc, const char * argv[]) {
    char c;
    Node *top = 0;
    while(1){
        scanf("%c", &c);
        if(c == '\n') break;
        if(c == '+'){
            int a = pop(&top);
            int b = pop(&top);
            push(&top, a+b);
        }
        else if(c == '-'){
            int a = pop(&top);
            int b = pop(&top);
            push(&top, b-a);
        }
        else if(c == '*'){
            int a = pop(&top);
            int b = pop(&top);
            push(&top, a*b);
        }
        else if(c != ' ') push(&top, int(c) - 48);
    }
    printf("%d", pop(&top));
    return 0;
}















