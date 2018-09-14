//
//  main.cpp
//  D
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
int pop(Node **top, Node **min = 0){
    int d = (*top)->d;
    Node *t = *top;
    if(t-> prevMin && min)
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

int main(int argc, const char * argv[]) {
    int n, k, d;
    Node *top[2], *min0 = 0, *min1 = 0;
    top[0] = top[1] = 0;
    scanf("%d%d", &n, &k);
    for(int i = 1; i < k; ++i){
        scanf("%d", &d);
        push(top, d, &min0);
    }
    for(int i = 0; i < n - k + 1; ++i){
        scanf("%d", &d);
        push(top, d, &min0);
        //----
        if(min0){
            if(min1 && min0->d > min1->d)
                printf("%d\n", min1->d);
            else
                printf("%d\n", min0->d);
        }
        else
            printf("%d\n", min1->d);
        //----
        if(!top[1]){
            min1 = min0 = 0;
            while(top[0])
                push(top+1, pop(top), &min1);
        }
        pop(top+1, &min1);
        if(!top[1]) min1 = 0;
    }
    return 0;
}
