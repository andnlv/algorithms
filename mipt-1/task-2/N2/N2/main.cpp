//
//  main.cpp
//  N2
//
//  Created by Andrey Danilov on 01.12.15.
//  Copyright © 2015 Andrey Danilov. All rights reserved.
//

#include <iostream>
#include <stdio.h>
struct point{
    int d;
    int i;
};
void siftUp(point *heap, int i){
    point x = heap[i];
    while(x.d < heap[(i-1)/2].d && i){
        heap[i] = heap[(i-1)/2];
        i = (i-1)/2;
    }
    heap[i] = x;
}
void siftDown(point *heap, int i, int size){
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
            i = min;
            f = 1;
        }
    }
}
void push(point *heap, int d, int &size, int i){
    heap[size].d = d;
    heap[size].i = i;
    siftUp(heap, size++);
}
int pop(point *heap, int &size){
    int d = heap->d;
    *heap = heap[--size];
    siftDown(heap, 0, size);
    return d;
}
int find(point *heap, int size, int k){
    for(int i = 0; i < size; ++i)
        if(heap[i].i == k)
            return i;
    return -1;
}
void clear(point *heap, int &size, int k){
    heap[k].d = 0;
    siftUp(heap, k);
    pop(heap, size);
}
void change(point *heap, int size, int k, int d){
    int d0 = heap[k].d;
    heap[k].d = d;
    if(d > d0) siftDown(heap, k, size);
    else siftUp(heap, k);
}
int main(int argc, const char * argv[]) {
    point *heap;
    int size = 0, n, m = 1, d;
    scanf("%d", &n);
    char s[12];
    heap = new point[n];
    for(int i = 0; i < n; ++i){
        scanf("%s", s);
        switch(s[0]){
            case 'i':
                scanf("%d", &d);
                push(heap, d, size, m++);
                printf("ok\n");
                break;
            case 'g':
                if(size) printf("%d\n", heap->d);
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
                printf("\n");
                for(int i = 0; i < size; ++i)
                    printf("%d ", heap[i].i);
                printf("\n");
                for(int i = 0; i < size; ++i)
                    printf("%d ", heap[i].d);
                printf("\n");
                break;
            case 'd':
                scanf("%d", &d);
                d = find(heap, size, d);
                if(d >= 0){
                    clear(heap, size, d);
                    printf("ok\n");
                }
                else
                    printf("error\n");
                break;
            default:
                if(s[1] == 'h'){
                    int i;
                    scanf("%d%d", &d, &i);
                    d = find(heap, size, d);
                    if(d >= 0){
                        change(heap, size, d, i);
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
    return 0;

}

/*

 20
 insert 4
 insert 3
 insert 2
 change 3 5
 extract_min
 change 1 1
 get_min
 delete 1
 get_min
 size
 clear
 change 3 10
 insert 1
 change 4 10
 insert 2
 extract_min
 delete 4
 size
 delete 5
 get_min


*/



