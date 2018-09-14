//
//  main.cpp
//  R
//
//  Created by Andrey Danilov on 02.12.15.
//  Copyright © 2015 Andrey Danilov. All rights reserved.
//3333311111111113311
//3333312222122213312
#include <iostream>
#include <stdio.h>
int min(int a, int b){
    if(a > b) return b;
    return a;
}
int main(int argc, const char * argv[]) {
    int a[1000001], n, i, next;
    a[1] = 0;
    int b[30], counter = 0;
    scanf("%d", &n);
    for(int i = 2; i <= n; ++i){
        a[i] = a[i-1];
        if(i%2 == 0) a[i] = min(a[i], a[i/2]);
        if(i%3 == 0) a[i] = min(a[i], a[i/3]);
        ++a[i];
    }
    i = n;
    while(i != 1){
        next = i - 1;
        if(i%2 == 0 && a[i/2] < a[next]) next = i/2;
        if(i%3 == 0 && a[i/3] < a[next]) next = i/3;
        if(next == i-1){
            b[counter++] = 1;
            i -= 1;
        }
        else if(next == i/3){
            b[counter++] = 3;
            i /= 3;
        }
        else if(next == i/2){
            b[counter++] = 2;
            i /= 2;
        }
    }
    //printf("%d\n", a[n]);
    for(int i = counter-1; i >= 0; --i) printf("%d", b[i]);
    return 0;
}
