//
//  main.cpp
//  N
//
//  Created by Andrey Danilov on 01.12.15.
//  Copyright © 2015 Andrey Danilov. All rights reserved.
//

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
    (*heap)-> n = 0;
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
    heap[data[i].n]->d = 0;
    siftUp(heap, data[i].n);
    pop(heap, size);
    
}
int main(int argc, const char * argv[]) {
    int size = 0, n, d, m = 0;
    point *data, **heap;
    char s[12];
    scanf("%d", &n);
    heap = new point* [n];
    data = new point [n];
    for(int i = 0; i < n; ++i) data[i].d = data[i].n = 0;
    for(int i = 0; i < n; ++i){
        scanf("%s", s);
        switch(s[0]){
            case 'i':
                scanf("%d", &d);
                push(heap, d, size, data, m++);
                printf("ok\n");
                break;
            case 'g':
                if(size) printf("%d\n", (*heap)-> d);
                else printf("error\n");
                break;
            case 'e':
                if(size) printf("%d\n", pop(heap, size));
                else printf("error\n");
                break;
            case 's':
                printf("%d\n", size);
                break;
            case 'p':
                for(int i = 0; i < m; ++i)
                    printf("%d ", data[i].d);
                printf("\n");
                for(int i = 0; i < m; ++i)
                    printf("%d ", heap[i]);
                printf("\n");
                for(int i = 0; i < size; ++i)
                    printf("%d ", heap[heap[i]-> n]-> d);
                printf("\n");
                break;
            case 'd':
                scanf("%d", &d);
                if(size && data[--d].d){
                    clear(heap, data, d, size);
                    printf("ok\n");
                }
                else
                    printf("error\n");
                break;
            default:
                if(s[1] == 'h'){
                    int i;
                    scanf("%d%d", &i, &d);
                    if(size && data[--i].d){
                        change(heap, d, size, data, i);
                        printf("ok\n");
                    }
                    else
                        printf("error\n");
                }
                else{
                    printf("ok\n");
                    size = 0;
                }
        }
    }
    delete [] heap;
    delete [] data;
    return 0;
}
/*
 100
 i 10
 i 9
 i 8
 i 7
 i 6
 i 5
 i 4
 i 3
 i 2
 i 1
 p
 g
 d 10
 p
 g
 s
 ch 10 100
 i 10
 p*/

/*
 100
 i 10
 ok
 i 9
 ok
 i 8
 ok
 i 7
 ok
 i 6
 ok
 i 5
 ok
 i 4
 ok
 i 3
 ok
 i 2
 ok
 i 1
 ok
 d 10
 ok
 i 10
 ok
 p
*/