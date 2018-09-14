//
//  main.cpp
//  O2
//
//  Created by Andrey Danilov on 05.12.15.
//  Copyright © 2015 Andrey Danilov. All rights reserved.
//

#include <iostream>
#include <stdio.h>
struct point{
    int d;
    int n;
};
void siftUpMin(point *heap, point *heap2, int i){
    point x = heap[i];
    while(x.d < heap[(i-1)/2].d && i){
        heap[i] = heap[(i-1)/2];
        heap2[heap[i].n].n = i;
        i = (i-1)/2;
    }
    heap[i] = x;
    heap2[heap[i].n].n = i;
}
void siftUpMax(point *heap, point *heap2, int i){
    point x = heap[i];
    while(x.d > heap[(i-1)/2].d && i){
        heap[i] = heap[(i-1)/2];
        heap2[heap[i].n].n = i;
        i = (i-1)/2;
    }
    heap[i] = x;
    heap2[heap[i].n].n = i;
}
void siftDownMin(point *heap, point *heap2, int i, int size){
    bool f = 1;
    int min = i;
    point t;
    while(f){
        f = 0;
        if(2*i+1 < size && heap[min].d > heap[2*i+1].d) min = 2*i+1;
        if(2*i+2 < size && heap[min].d > heap[2*i+2].d) min = 2*i+2;
        if(i != min){
            t = heap[i];
            heap[i] = heap[min];
            heap[min] = t;
            heap2[heap[i].n].n = i;
            heap2[heap[min].n].n = min;
            i = min;
            f = 1;
        }
    }
}
void siftDownMax(point *heap, point *heap2, int i, int size){
    bool f = 1;
    int min = i;
    point t;
    while(f){
        f = 0;
        if(2*i+1 < size && heap[min].d < heap[2*i+1].d) min = 2*i+1;
        if(2*i+2 < size && heap[min].d < heap[2*i+2].d) min = 2*i+2;
        if(i != min){
            t = heap[i];
            heap[i] = heap[min];
            heap[min] = t;
            heap2[heap[i].n].n = i;
            heap2[heap[min].n].n = min;
            i = min;
            f = 1;
        }
    }
}
void push(point *minHeap, point *maxHeap, int &size, int d){
    minHeap[size].d = d;
    maxHeap[size].d = d;
    minHeap[size].n = maxHeap[size].n = size;
    siftUpMax(maxHeap, minHeap, size);
    siftUpMin(minHeap, maxHeap, size);
    ++size;
}
int extract_min(point *minHeap, point *maxHeap, int &size){
    int d = minHeap->d;
    int n = minHeap->n;
    --size;
    *minHeap = minHeap[size];
    maxHeap[minHeap->n].n = 0;
    siftDownMin(minHeap, maxHeap, 0, size);
    maxHeap[n] = maxHeap[size];
    minHeap[maxHeap[n].n].n = n;
    siftUpMax(maxHeap, minHeap, n);
    return d;
}
int extract_max(point *maxHeap, point *minHeap, int &size){
    int d = maxHeap->d;
    int n = maxHeap->n;
    --size;
    *maxHeap = maxHeap[size];
    minHeap[maxHeap->n].n = 0;
    siftDownMax(maxHeap, minHeap, 0, size);
    minHeap[n] = minHeap[size];
    maxHeap[minHeap[n].n].n = n;
    siftUpMin(minHeap, maxHeap, n);
    return d;
}
int main(int argc, const char * argv[]) {
    point *minHeap, *maxHeap;
    int size = 0, d, n;
    char s[12];
    scanf("%d", &n);
    minHeap = new point[n];
    maxHeap = new point[n];
    for(int i = 0; i < n; ++i){
        scanf("%s", s);
        switch (s[0]) {
            case 'i':
                scanf("%d", &d);
                push(minHeap, maxHeap, size, d);
                printf("ok\n");
                break;
            case 'e':
                if(!size){
                    printf("error\n");
                    break;
                }
                if(s[9] == 'i')
                    printf("%d\n", extract_min(minHeap, maxHeap, size));
                else
                    printf("%d\n", extract_max(maxHeap, minHeap, size));
                break;
            case 'g':
                if(!size){
                    printf("error\n");
                    break;
                }
                if(s[5] == 'i')
                    printf("%d\n", minHeap->d);
                else
                    printf("%d\n", maxHeap->d);
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
    delete [] maxHeap;
    delete [] minHeap;
    return 0;
}
