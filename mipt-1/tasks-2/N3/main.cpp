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
void siftUp(point *heap, int i, int *index){
    point x = heap[i];
    while(x.d < heap[(i-1)/2].d && i){
        heap[i] = heap[(i-1)/2];
        index[heap[i].i] = i;
        //printf("5index[%d] = %d\n", heap[i].i, i);
        i = (i-1)/2;
    }
    heap[i] = x;
    index[heap[i].i] = i;
    //printf("6index[%d] = %d\n", heap[i].i, i);
}
void siftDown(point *heap, int i, int size, int *index){
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
            index[heap[i].i] = i;
            //printf("3index[%d] = %d\n", heap[i].i, i);
            i = min;
            index[heap[i].i] = i;
            //printf("4index[%d] = %d\n", heap[i].i, i);
            f = 1;
        }
    }
}
void push(point *heap, int d, int &size, int i, int *index){
    heap[size].d = d;
    heap[size].i = i;
    index[i] = size;
    //printf("1index[%d] = %d\n", i, size);
    siftUp(heap, size++, index);
}
int pop(point *heap, int &size, int *index){
    int d = heap->d;
    index[heap->i] = -1;
    //printf("2index[%d] = -1\n", heap->i);
    *heap = heap[--size];
    if(size) index[heap->i] = 0;
    //printf("2index[%d] = 0\n", heap->i);
    siftDown(heap, 0, size, index);
    return d;
}
void clear(point *heap, int &size, int k, int *index){
    heap[k].d = 0;
    siftUp(heap, k, index);
    pop(heap, size, index);
}
void change(point *heap, int size, int k, int d, int *index){
    int d0 = heap[k].d;
    heap[k].d = d;
    if(d > d0) siftDown(heap, k, size, index);
    else siftUp(heap, k, index);
}
int main(int argc, const char * argv[]) {
    point *heap;
    int size = 0, n, m = 0, d, *index;
    scanf("%d", &n);
    char s[12];
    heap = new point[n];
    index = new int[n];
    for(int i = 0; i < n; ++i){
        scanf("%s", s);
        switch(s[0]){
            case 'i':
                scanf("%d", &d);
                push(heap, d, size, m++, index);
                printf("ok\n");
                break;
            case 'g':
                if(size) printf("%d\n", heap->d);
                else printf("error\n");
                break;
            case 'e':
                if(size) printf("%d\n", pop(heap, size, index));
                else printf("error\n");
                break;
            case 's':
                printf("%d\n", size);
                break;
            case 'p':
                for(int i = 0; i < m; ++i)
                    printf("%d ", heap[i].i);
                printf("\n");
                for(int i = 0; i < m; ++i)
                    printf("%d ", index[i]);
                printf("\n");
                for(int i = 0; i < m; ++i)
                    printf("%d ", heap[i].d);
                printf("\n");
                break;
            case 'd':
                scanf("%d", &d);
                --d;
                if(d < m) d = index[d];
                else d = -1;
                //printf("%d\n", d);
                if(d >= 0){
                    clear(heap, size, d, index);
                    printf("ok\n");
                }
                else
                    printf("error\n");
                break;
            case 'l':
            {
                bool f = 1;
                for(int i = 0; i < size; ++i){
                    if(index[heap[i].i] != i){
                        printf("%d %d\n", i, index[heap[i].i]);
                        f = 0;
                    }
                }
                for(int i = 0; i < size; ++i)
                    printf("%d ", index[heap[i].i]);
                printf("\n");
                if(f)
                    printf("ok\n");
                else
                    printf("ERROR\n");
            }
                break;
            default:
                if(s[1] == 'h'){
                    int i;
                    scanf("%d%d", &d, &i);
                    --d;
                    if(d < m) d = index[d];
                    else d = -1;
                    //printf("%d\n", d);
                    if(d >= 0){
                        change(heap, size, d, i, index);
                        printf("ok\n");
                    }
                    else
                        printf("error\n");
                }
                else{
                    for(int i = 0; i < m; ++i) index[i] = -1;
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
 
 100
 i 4
 ok
 i 3
 ok
 i 5
 ok
 i 2
 ok
 i 6
 ok
 i 1
 ok
 i 7
 ok
 l
 ok
 d 4
 ok
 l
 ok
 ch 3
 10
 ok
 l
 ok
 i 1
 ok
 i 1
 ok
 i 1
 ok
 i 1
 ok
 i 1
 ok
 i 1
 ok
 i 1
 ok
 l
 ok
 e
 1
 e
 1
 e
 1
 l
 ERROR
 p
 
 11 9 7 1 10 12 6 0 2 4 
 1 1 1 3 1 1 7 4 10 6
 */



