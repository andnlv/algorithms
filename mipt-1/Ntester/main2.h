//
//  main2.h
//  Ntester
//
//  Created by Andrey Danilov on 02.12.15.
//  Copyright © 2015 Andrey Danilov. All rights reserved.
//

#ifndef main2_h
#define main2_h


#endif /* main2_h */
#include <iostream>
#include <stdio.h>
struct point2{
    int d;
    int i;
};
void siftUp(point2 *heap, int i){
    point2 x = heap[i];
    while(x.d < heap[(i-1)/2].d && i){
        heap[i] = heap[(i-1)/2];
        i = (i-1)/2;
    }
    heap[i] = x;
}
void siftDown(point2 *heap, int i, int size){
    bool f = 1;
    int min = i;
    point2 t;
    while(f){
        f = 0;
        if(2*i+1 < size && heap[min].d > heap[2*i+1].d) min = 2*i+1;
        if(2*i+2 < size && heap[min].d > heap[2*i+2].d) min = 2*i+2;
        if(i != min){
            t = heap[i];
            heap[i] = heap[min];
            heap[min] = t;
            i = min;
            f = 1;
        }
    }
}
void push(point2 *heap, int d, int &size, int i){
    heap[size].d = d;
    heap[size].i = i;
    siftUp(heap, size++);
}
int pop(point2 *heap, int &size){
    int d = heap->d;
    *heap = heap[--size];
    siftDown(heap, 0, size);
    return d;
}
int find(point2 *heap, int size, int k){
    for(int i = 0; i < size; ++i)
        if(heap[i].i == k)
            return i;
    return -1;
}
void clear(point2 *heap, int &size, int k){
    heap[k] = heap[--size];
    if(size == k) return;
    siftDown(heap, k, size);
    siftUp(heap, k);
}
void change(point2 *heap, int size, int k, int d){
    int d0 = heap[k].d;
    heap[k].d = d;
    if(d > d0) siftDown(heap, k, size);
    else siftUp(heap, k);
}
int main2(point2 *heap, int &size, int &m, int k, int d = 0, int i = 0) {
        switch(k){
            case 1:
                //scanf("%d", &d);
                push(heap, d, size, m++);
                //printf("ok\n");
                return -1;
                break;
            case 2:
                //if(size) printf("%d\n", heap->d);
                //else printf("error\n");
                if(size) return heap->d;
                else return -2;
                break;
            case 3:
                //if(size) printf("%d\n", pop(heap, size));
                //else printf("error\n");
                if(size) return pop(heap, size);
                else return -2;
                break;
            case 4:
                //printf("%d\n", size);
                return size;
                break;
            case 8:
                printf("\n");
                for(int i = 0; i < m; ++i)
                    printf("%d ", heap[i].i);
                printf("\n");
                for(int i = 0; i < size; ++i)
                    printf("%d ", heap[i].d);
                printf("\n");
                break;
            case 5:
                //scanf("%d", &d);
                d = find(heap, size, d);
                if(d >= 0){
                    clear(heap, size, d);
                    //printf("ok\n");
                    return -1;
                }
                else
                    return -2;
                    //printf("error\n");
                break;
            case 6:
                    d = find(heap, size, d);
                    if(d >= 0){
                        change(heap, size, d, i);
                        //printf("ok\n");
                        return -1;
                    }
                    else
                        return -2;
                        //printf("error\n");
            case 7:
                return -1;
                    //printf("ok\n");
                    size = 0;
        }
    return 0;
    
}
