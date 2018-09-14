//
//  main.cpp
//  Ntester
//
//  Created by Andrey Danilov on 02.12.15.
//  Copyright © 2015 Andrey Danilov. All rights reserved.
//

#include <iostream>
#include "main1.h"
#include "main2.h"
void comp(int a1, int a2, point **heap, point *data, point2 *heap2, int size1, int size2, int m1, int m2, int *key){
    if(a1 != a2){
        printf("DIFFERENCE\n");
        a1 = main1(heap, data, size1, m1, 8);
        printf("---------\n");
        a2 = main2(heap2, size2, m2, 8);
        printf("---------\n");
        for(int i = 0; i < 20; ++i) printf("%d ", key[i]);
    }
}
int main(int argc, const char * argv[]) {
    srand(int(time(NULL)));
    int n, k, d, j;
    int size1 = 0, size2 = 0, m1 = 0, m2 = 1;
    int a1, a2;
    int key[20];
    point *heap[1000], data[1000];
    point2 heap2[1000];
    scanf("%d", &n);
    for(int i = 1; i <= n; ++i){
        k = rand()%6 + 1;
        if(i%20 == 0) k = 7;
        key[i%20] = k;
        if(k == 1){
            d = rand()%100;
            printf("insert %d ", d);
            a1 = main1(heap, data, size1, m1, k, d);
            a2 = main2(heap2, size2, m2, k, d);
            printf("%d %d\n", a1, a2);
            comp(a1, a2, heap, data, heap2, size1, size2, m1, m2, key);
            continue;
        }
        if(k < 5){
            a1 = main1(heap, data, size1, m1, k);
            a2 = main2(heap2, size2, m2, k);
            if(k == 2) printf("get_min ");
            if(k == 3) printf("extract_min ");
            if(k == 4) printf("size ");
            printf("%d %d\n", a1, a2);
            comp(a1, a2, heap, data, heap2, size1, size2, m1, m2, key);
            continue;
        }
        if(k == 5){
            d = rand()%m2 + 1;
            printf("delete %d ", d);
            a1 = main1(heap, data, size1, m1, k, d);
            a2 = main2(heap2, size2, m2, k, d);
            printf("%d %d\n", a1, a2);
            comp(a1, a2, heap, data, heap2, size1, size2, m1, m2, key);
            continue;
        }
        if(k == 6){
            d = rand()%m2 + 1;
            j = rand()%100;
            printf("change %d %d ", d, j);
            a1 = main1(heap, data, size1, m1, k, d, j);
            a2 = main2(heap2, size2, m2, k, d, j);
            printf("%d %d\n", a1, a2);
            comp(a1, a2, heap, data, heap2, size1, size2, m1, m2, key);
        }
        if(k == 7){
            a1 = main1(heap, data, size1, m1, k);
            a2 = main2(heap2, size2, m2, k);
            printf("clear %d %d\n", a1, a2);
            comp(a1, a2, heap, data, heap2, size1, size2, m1, m2, key);
        }
    }
    return 0;
}









