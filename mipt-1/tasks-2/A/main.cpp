//
//  main.cpp
//  A
//
//  Created by Andrey Danilov on 25.11.15.
//  Copyright © 2015 Andrey Danilov. All rights reserved.
//

#include <iostream>
#include <stdio.h>
struct Node{
    int d;
    Node *prev;
    Node *prevMin;
};
void push(Node **top, int d, Node **min){
    Node *t = new Node;
    t->d = d;
    t-> prev = *top;
    if(!*min || d < (*min)->d){
        t->prevMin = *min;
        *min = t;
    }
    else
        t->prevMin = 0;
    *top = t;
}
int pop(Node **top, Node **min){
    int d = (*top)->d;
    Node *t = *top;
    if(t-> prevMin)
        *min = t->prevMin;
    *top = (*top)->prev;
    delete t;
    return d;
}
void clear(Node **top, Node **min){
    Node *t = *top;
    while(t){
        t = (*top)->prev;
        delete *top;
        *top = t;
    }
    *min = 0;
}
int size(Node *top){
    int i = 0;
    for(Node *t = top; t; t = t->prev) ++i;
    return i;
}
int main(int argc, const char * argv[]) {
    int n;
    char s[6];
    Node *top = 0, *min = 0;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%s", s);
        switch (s[2]) {
            case 's':
                int d;
                scanf("%d", &d);
                push(&top, d, &min);
                printf("ok\n");
                break;
            case 'p':
                if(top)
                    printf("%d\n", pop(&top, &min));
                else
                    printf("error\n");
                break;
            case 'c':
                if(top)
                    printf("%d\n", top->d);
                else
                    printf("error\n");
                break;
            case 'n':
                if(top)
                    printf("%d\n", min->d);
                else
                    printf("error\n");
                break;
            case 'z':
                printf("%d\n", size(top));
                break;
            case 'e':
                clear(&top, &min);
                printf("ok\n");
                break;
        }
    }
    return 0;
}
