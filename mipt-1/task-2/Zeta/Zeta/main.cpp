//
//  main.cpp
//  Zeta
//
//  Created by Andrey Danilov on 04.12.15.
//  Copyright © 2015 Andrey Danilov. All rights reserved.
//

#include <iostream>

long divide(long *a, long size){
    long d1, d2;
    //printf("divide %d %d\n", a, size);
    if(size == 1) return *a;
    d1 = divide(a, size/2);
    d2 = divide(a + size/2, size - size/2);
    long i = size/2-1, j = size/2, minHeight = a[j], d = 0;
    //printf("size = %d\n", size);
    if(a[i] < a[j]) minHeight = a[i];
    while(true){
        //printf("thinking %d %d minHeight = %d\n", i, j, minHeight);
        while(j < size-1 && a[j+1] >= minHeight) ++j;
        while(i > 0 && a[i-1] >= minHeight) --i;
        if(d < (j-i+1)*minHeight)
            d = (j-i+1)*minHeight;
        if(i <= 0 && j >= size-1) break;
        if(i > 0 && (a[i-1] > a[j+1] || j >= size-1)){
            if(minHeight > a[i-1]) minHeight = a[i-1];
            --i;
        }
        else{
            if(minHeight > a[j+1]) minHeight = a[j+1];
            ++j;
        }
    };
    if(d < d1) d = d1;
    if(d < d2) d = d2;
    //printf("return %d\n", d);
    return d;
}
int main(int argc, const char * argv[]) {
    srand(int(time(NULL)));
    long minHeihgt, n, *a, d, k;
    long answer = 0, max;
    scanf("%lu", &k);
    a = new long[n];
    n = 4;
    for(int z = 0; z < k; ++z){
    answer = 0;
    for(int i = 0; i < n; ++i){
        //scanf("%d", a+i);
        a[i] = rand()%1000000001;
    }
    for(int i = 0; i < n; ++i){
        minHeihgt = a[i];
        max = 0;
        for(int j = i; j >= 0; --j){
            if(a[j] < minHeihgt) minHeihgt = a[j];
            d = minHeihgt*(i-j+1);
            if(max < d) max = d;
        }
        if(max > answer) answer = max;
    }
    //printf("%d", answer);
    if(answer != divide(a, n)){
        printf("answer1 = %lu, answer2 = %lu\n", answer, divide(a, n));
        for(int i = 0; i < n; ++i){
            printf("%lu ", a[i]);
        }
        printf("\n");
    }
    }
    return 0;
}
