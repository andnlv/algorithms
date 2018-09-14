//
//  main.cpp
//  Ntester2
//
//  Created by Andrey Danilov on 03.12.15.
//  Copyright © 2015 Andrey Danilov. All rights reserved.
//

#include <iostream>
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
//-------------------------------------------------------------------------
void siftUp(point *heap, int i, int *index){
    point x = heap[i];
    while(x.d < heap[(i-1)/2].d && i){
        heap[i] = heap[(i-1)/2];
        index[heap[i].i] = i;
        i = (i-1)/2;
    }
    heap[i] = x;
    index[heap[i].i] = i;
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
            i = min;
            index[heap[i].i] = i;
            f = 1;
        }
    }
}
void push(point *heap, int d, int &size, int i, int *index){
    heap[size].d = d;
    heap[size].i = i;
    index[i] = size;
    siftUp(heap, size++, index);
}
int pop(point *heap, int &size, int *index){
    int d = heap->d;
    index[heap->i] = -1;
    *heap = heap[--size];
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
    point *heap1, *heap2;
    int size1 = 0, size2 = 0, n = 1, m = 1, d, *index;
    scanf("%d", &n);
    int s;
    heap1 = new point[n];
    heap2 = new point[n];
    index = new int[n];
    for(int i = 0; i < n; ++i){
        //scanf("%s", s);
        s = rand()%6;
        if(!(i%1000)){
            //size1 = 0;
            //size2 = 0;
            //m = 0;
        }
        switch(s){
            case 0:
                //scanf("%d", &d);
                d = rand()%20;
                //printf("push %d\n", d);
                push(heap1, d, size1, m);
                push(heap2, d, size2, m++, index);
                //printf("ok\n");
                break;
            case 1:
                //printf("get_min %d %d\n", heap1->d, heap2->d);
                if(size1 && heap1->d != heap2->d){
                    printf("ERROR\n");
                    scanf("%d", &s);
                    if(s){
                        printf("\n");
                        for(int i = 0; i < size1; ++i)
                            printf("%d ", heap1[i].i);
                        printf("\n");
                        for(int i = 0; i < size1; ++i)
                            printf("%d ", heap1[i].d);
                        printf("\n");
                        for(int i = 0; i < size2; ++i)
                            printf("%d ", heap2[i].i);
                        printf("\n");
                        for(int i = 0; i < size2; ++i)
                            printf("%d ", heap2[i].d);
                        printf("\n");

                    }
                }
                //else printf("error\n");
                break;
            case 2:
                {int a1 = size1 ? pop(heap1, size1) : -1;
                int a2 = size2 ? pop(heap2, size2, index) : -1;
                //printf("extract_min %d %d\n", a1, a2);
                    if(a1 != a2){
                        printf("ERROR\n");
                        scanf("%d", &s);
                        if(s){
                            printf("\n");
                            for(int i = 0; i < size1; ++i)
                                printf("%d ", heap1[i].i);
                            printf("\n");
                            for(int i = 0; i < size1; ++i)
                                printf("%d ", heap1[i].d);
                            printf("\n");
                            for(int i = 0; i < size2; ++i)
                                printf("%d ", heap2[i].i);
                            printf("\n");
                            for(int i = 0; i < size2; ++i)
                                printf("%d ", heap2[i].d);
                            printf("\n");
                            
                        }
                    }
                //else printf("error\n");
                break;}
            case 5:
                //printf("size %d %d\n", size1, size2);
                break;
            case 6:
                printf("\n");
                for(int i = 0; i < size1; ++i)
                    printf("%d ", heap1[i].i);
                printf("\n");
                for(int i = 0; i < size1; ++i)
                    printf("%d ", heap1[i].d);
                printf("\n");
                for(int i = 0; i < size2; ++i)
                    printf("%d ", heap2[i].i);
                printf("\n");
                for(int i = 0; i < size2; ++i)
                    printf("%d ", heap2[i].d);
                printf("\n");
                break;
            case 3:
                //scanf("%d", &d);
                int d1, d2;
                d = rand()%20;
                d1 = find(heap1, size1, d);
                if(d1 >= 0){
                    clear(heap1, size1, d1);
                    //printf("ok\n");
                }
                //else
                    //printf("error\n");
                d2 = index[d];
                if(d1 >= 0)
                    clear(heap2, size2, d1, index);
                break;
            //default:
                /*if(s == 4){
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
                }*/
        }
    }
    delete [] heap1;
    delete [] heap2;
    return 0;
}
