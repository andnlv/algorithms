//
//  main.cpp
//  O
//
//  Created by Andrey Danilov on 03.12.15.
//  Copyright © 2015 Andrey Danilov. All rights reserved.
//

#include <iostream>
#include <stdio.h>
struct point{
    int d;
    int i;
};
void siftUpMin(point *heap, int i, int **index){
    point x = heap[i];
    while(x.d < heap[(i-1)/2].d && i){
        heap[i] = heap[(i-1)/2];
        index[0][heap[i].i] = i;
        i = (i-1)/2;
    }
    heap[i] = x;
    index[0][heap[i].i] = i;
}
void siftUpMax(point *heap, int i, int **index){
    point x = heap[i];
    while(x.d > heap[(i-1)/2].d && i){
        heap[i] = heap[(i-1)/2];
        index[1][heap[i].i] = i;
        i = (i-1)/2;
    }
    heap[i] = x;
    index[1][heap[i].i] = i;
}
void siftDownMin(point *heap, int i, int size, int **index){
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
            index[0][heap[i].i] = i;
            i = min;
            index[0][heap[i].i] = i;
            f = 1;
        }
    }
}
void siftDownMax(point *heap, int i, int size, int **index){
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
            index[1][heap[i].i] = i;
            i = min;
            index[1][heap[i].i] = i;
            f = 1;
        }
    }
}
void minPush(point *heap, int d, int &size, int i, int **index){
    heap[size].d = d;
    heap[size].i = i;
    index[0][i] = size;
    //printf("1index[%d] = %d\n", i, size);
    siftUpMin(heap, size, index);
}
void maxPush(point *heap, int d, int &size, int i, int **index){
    heap[size].d = d;
    heap[size].i = i;
    index[1][i] = size;
    //printf("1index[%d] = %d\n", i, size);
    siftUpMax(heap, size, index);
}
int minPop(point *heap, int &size, int **index){
    int d = heap->d;
    index[0][heap->i] = -1;
    //printf("2index[%d] = -1\n", heap->i);
    *heap = heap[size-1];
    if(size-1) index[0][heap->i] = 0;
    //printf("2index[%d] = 0\n", heap->i);
    siftDownMin(heap, 0, size-1, index);
    return d;
}
int maxPop(point *heap, int &size, int **index){
    int d = heap->d;
    index[1][heap->i] = -1;
    //printf("2index[%d] = -1\n", heap->i);
    *heap = heap[size-1];
    if(size-1) index[1][heap->i] = 0;
    //printf("2index[%d] = 0\n", heap->i);
    siftDownMax(heap, 0, size-1, index);
    return d;
}
void minClear(point *heap, int &size, int k, int **index){
    heap[k].d = 0;
    siftUpMin(heap, k, index);
    minPop(heap, size, index);
}
void maxClear(point *heap, int &size, int k, int **index){
    heap[k].d = 1000000001;
    siftUpMax(heap, k, index);
    maxPop(heap, size, index);
}
int extractMin(point *minHeap, point *maxHeap, int &size, int **index){
    int d = minHeap->d;
    int i = minHeap->i;
    maxClear(maxHeap, size, index[1][i], index);
    minPop(minHeap, size, index);
    return d;
}
int extractMax(point *maxHeap, point *minHeap, int &size, int **index){
    int d = maxHeap->d;
    int i = maxHeap->i;
    minClear(minHeap, size, index[0][i], index);
    maxPop(maxHeap, size, index);
    return d;
}
int main(int argc, const char * argv[]) {
    point *minHeap, *maxHeap;
    int size = 0, d, n, *index[2], m = 0;
    char s[12];
    scanf("%d", &n);
    minHeap = new point[n];
    maxHeap = new point[n];
    index[0] = new int[n];
    index[1] = new int[n];
    for(int i = 0; i < n; ++i){
        scanf("%s", s);
        switch (s[0]) {
            case 'i':
                scanf("%d", &d);
                minPush(minHeap, d, size, m, index);
                maxPush(maxHeap, d, size, m++, index);
                ++size;
                printf("ok\n");
                break;
            case 'e':
                if(!size){
                    printf("error\n");
                    break;
                }
                if(s[9] == 'i')
                    printf("%d\n", extractMin(minHeap, maxHeap, size, index));
                else
                    printf("%d\n", extractMax(maxHeap, minHeap, size, index));
                --size;
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







