//
//  main.cpp
//  M
//
//  Created by Andrey Danilov on 30.11.15.
//  Copyright © 2015 Andrey Danilov. All rights reserved.
//

#include <iostream>
#include <stdio.h>
void siftUp(int *heap, int i){
    int x = heap[i];
    while(x < heap[(i-1)/2] && i){
        heap[i] = heap[(i-1)/2];
        i = (i-1)/2;
    }
    heap[i] = x;
}
void siftDown(int *heap, int i, int size){
    bool f = 1;
    int t, min = i;
    while(f){
        f = 0;
        if(2*i+1 < size && heap[min] > heap[2*i+1]) min = 2*i+1;
        if(2*i+2 < size && heap[min] > heap[2*i+2]) min = 2*i+2;
        if(i != min){
            t = heap[i];
            heap[i] = heap[min];
            heap[min] = t;
            i = min;
            f = 1;
        }
    }
}
void push(int *heap, int d, int &size){
    heap[size] = d;
    siftUp(heap, size++);
}
int pop(int *heap, int &size){
    int d = *heap;
    *heap = heap[--size];
    siftDown(heap, 0, size);
    return d;
}
int main(int argc, const char * argv[]) {
    int *heap, n, size = 0, d;
    char s[12];
    scanf("%d", &n);
    heap = new int[n];
    for(int i = 0; i < n; ++i){
        scanf("%s", s);
        switch(s[0]){
            case 'i':
                scanf("%d", &d);
                push(heap, d, size);
                printf("ok\n");
                break;
            case 'g':
                if(size) printf("%d\n", *heap);
                else printf("error\n");
                break;
            case 'e':
                if(size) printf("%d\n", pop(heap, size));
                else printf("error\n");
                break;
            case 's':
                printf("%d\n", size);
                break;
            case 'c':
                printf("ok\n");
                size = 0;
                break;
        }
    }
    delete [] heap;
    return 0;
}

