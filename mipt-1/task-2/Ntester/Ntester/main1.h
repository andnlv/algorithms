//
//  main1.h
//  Ntester
//
//  Created by Andrey Danilov on 02.12.15.
//  Copyright © 2015 Andrey Danilov. All rights reserved.
//

#ifndef main1_h
#define main1_h


#endif /* main1_h */
#include <iostream>
#include <stdio.h>
struct point{
    int d;
    int n;
};
void siftUp(point **heap, int i){
    point *x = heap[i];
    while(i && x->d < heap[(i-1)/2]->d){
        heap[i] = heap[(i-1)/2];
        heap[i]-> n = i;
        i = (i-1)/2;
    }
    heap[i] = x;
    heap[i]-> n = i;
}
void siftDown(point **heap, int i, int size){
    bool f = 1;
    int min = i;
    point *t;
    while(f){
        f = 0;
        if(2*i+1 < size && heap[min]->d > heap[2*i+1]->d) min = 2*i+1;
        if(2*i+2 < size && heap[min]->d > heap[2*i+2]->d) min = 2*i+2;
        if(i != min){
            t = heap[i];
            heap[i] = heap[min];
            heap[min] = t;
            heap[i]-> n = i;
            heap[min]-> n = min;
            i = min;
            f = 1;
        }
    }
}
void push(point **heap, int d, int &size, point *data, int n){
    data[n].d = d;
    heap[size] = data + n;
    data[n].n = size;
    siftUp(heap, size);
    ++size;
}
int pop(point **heap, int &size){
    int d = (*heap)->d;
    (**heap).d = 0;
    *heap = heap[--size];
    siftDown(heap, 0, size);
    return d;
}
void change(point **heap, int d, int &size, point *data, int i){
    int d0 = data[i].d;
    data[i].d = d;
    if(d < d0)
        siftUp(heap, data[i].n);
    else if(d > d0)
        siftDown(heap, data[i].n, size);
}
void clear(point **heap, point *data, int i, int &size){
    data[i].d = 0;
    heap[data[i].n] = heap[--size];
    siftDown(heap, data[i].n, size);
    siftUp(heap, data[i].n);
}
int main1(point **heap, point *data, int &size, int &m, int k, int i = 0, int d = 0) {
        switch(k){
            case 1:
                //scanf("%d", &d);
                push(heap, d, size, data, m++);
                //printf("ok\n");
                return -1;
                break;
            case 2:
                //if(size) printf("%d\n", (*heap)-> d);
                //else printf("error\n");
                if(size) return (*heap)-> d;
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
                for(int i = 0; i < m; ++i)
                    printf("%d ", data[i].d);
                printf("\n");
                for(int i = 0; i < size; ++i)
                    printf("%d ", heap[heap[i]-> n]-> d);
                printf("\n");
                break;
            case 5:
                //scanf("%d", &d);
                if(size && data[--d].d){
                    clear(heap, data, d, size);
                    //printf("ok\n");
                    return -1;
                }
                else
                    return -2;
                    //printf("error\n");
                break;
            case 6:
                    //scanf("%d%d", &i, &d);
                    if(size && data[--i].d){
                        change(heap, d, size, data, i);
                        //printf("ok\n");
                        return -1;
                    }
                    else
                        return -2;
                        //printf("error\n");
            case 7:
                    return -1;
                    printf("ok\n");
                    size = 0;
        }
    return 0;
}






