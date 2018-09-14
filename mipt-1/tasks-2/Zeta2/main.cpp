//
//  main.cpp
//  Zeta2
//
//  Created by Andrey Danilov on 04.12.15.
//  Copyright © 2015 Andrey Danilov. All rights reserved.
//

#include <iostream>
#include <stdio.h>
long divide(long *a, long size){
    long d1, d2;
    //printf("divide %d %d\n", a, size);
    if(size == 1) return *a;
    d1 = divide(a, size/2);
    d2 = divide(a + size/2, size - size/2);
    long i = size/2-1, j = size/2, d = 0, minHeight = a[j];
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
    //srand(int(time(NULL)));
    long *a, n;
    scanf("%ld", &n);
    if(n == 0){
        printf("0");
        return 0;
    }
    a = new long[n];
    for(int i = 0; i < n; ++i){
        scanf("%ld", a+i);
        //a[i] = rand()%10;
        //printf("%d ", a[i]);
    }
    //printf("\n");
    printf("%ld", divide(a, n));
    delete [] a;
    return 0;
}
