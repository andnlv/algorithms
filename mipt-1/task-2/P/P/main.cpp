//
//  main.cpp
//  P
//
//  Created by Andrey Danilov on 03.12.15.
//  Copyright © 2015 Andrey Danilov. All rights reserved.
//

#include <iostream>
#include <stdio.h>
struct point{
    int t;
    int l;
};
void siftUp(int *heap, int i){
    int x = heap[i];
    while(x < heap[(i-1)/2] && i){
        heap[i] = heap[(i-1)/2];
        i = (i-1)/2;
    }
    heap[i] = x;
}
void siftUp(point *heap, int i){
    point x = heap[i];
    while(x.t < heap[(i-1)/2].t && i){
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
void siftDown(point *heap, int i, int size){
    bool f = 1;
    int min = i;
    point t;
    while(f){
        f = 0;
        if(2*i+1 < size && heap[min].t > heap[2*i+1].t) min = 2*i+1;
        if(2*i+2 < size && heap[min].t > heap[2*i+2].t) min = 2*i+2;
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
void push(point *heap, point d, int &size){
    heap[size] = d;
    siftUp(heap, size++);
}
int pop(int *heap, int &size){
    int d = *heap;
    *heap = heap[--size];
    siftDown(heap, 0, size);
    return d;
}
point pop(point *heap, int &size){
    point d = *heap;
    *heap = heap[--size];
    siftDown(heap, 0, size);
    return d;
}
int main(int argc, const char * argv[]) {
    point *heap1, x;
    int *heap2, n, size1 = 0, size2 = 0, max = 0;
    scanf("%d", &n);
    heap1 = new point[n];
    heap2 = new int[n];
    for(int i = 0; i < n; ++i){
        scanf("%d%d", &(x.t), &(x.l));
        push(heap1, x, size1);
    }
    while(size1){
        x = pop(heap1, size1);
        //printf("%d", d);
        while(size2 && *heap2 <= x.t){
            pop(heap2, size2);
        }
        push(heap2, x.t+x.l, size2);
        if(size2 > max) max = size2;
    }
    printf("%d", max);
    delete [] heap1;
    delete [] heap2;
    return 0;
}












