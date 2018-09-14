//
//  main.cpp
//  Q
//
//  Created by Andrey Danilov on 02.12.15.
//  Copyright © 2015 Andrey Danilov. All rights reserved.
//

#include <iostream>
#include <stdio.h>
int main(int argc, const char * argv[]) {
    unsigned long long a[40], n;
    unsigned long long b2[40];
    unsigned long long b1[40];
    unsigned long long b0[40];
    a[0] = 2;
    a[1] = 4;
    b0[1] = 2;
    b1[1] = 1;
    b2[1] = 1;
    scanf("%llu", &n);
    for(int i = 2; i < n; ++i){
        b0[i] = a[i-1];
        b1[i] = b0[i-1];
        b2[i] = b1[i-1];
        a[i] = 2*a[i-1] - b2[i-1];
    };
    printf("%llu", a[n-1]);
    return 0;
}
