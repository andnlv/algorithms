//
//  main.cpp
//  U
//
//  Created by Andrey Danilov on 03.12.15.
//  Copyright © 2015 Andrey Danilov. All rights reserved.
//

#include <iostream>
#include <stdio.h>
int main(int argc, const char * argv[]) {
    int n, a[1000], b[1000], c[1000], d[1000], max, maxI = 0, counter = 0;
    scanf("%d", &n);
    for(int i = 0; i < n; ++i) c[i] = -1;
    for(int i = 0; i < n; ++i)
        scanf("%d", a+i);
    for(int i = 0; i < n; ++i){
        max = 0;
        for(int j = 0; j < i; ++j)
            if(b[j] > max && a[j] < a[i]){
                max = b[j];
                maxI = j;
            }
        b[i] = max + 1;
        if(max) c[i] = maxI;
    }
    max = 0;
    for(int i = 0; i < n; ++i){
        if(b[i] > max){
            max =b[i];
            maxI = i;
        }
    }
    /*for(int i = 0; i < n; ++i){
        printf("%d ", b[i]);
    }
    printf("\n");
    for(int i = 0; i < n; ++i){
        printf("%d ", c[i]);
    }
    printf("\n");*/
    int i = maxI;
    while(i >= 0){
        d[counter++] = a[i];
        i = c[i];
    }
    for(i = counter-1; i >= 0; --i)
        printf("%d ", d[i]);
    return 0;
}
