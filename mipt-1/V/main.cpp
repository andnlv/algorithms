//
//  main.cpp
//  V
//
//  Created by Andrey Danilov on 03.12.15.
//  Copyright © 2015 Andrey Danilov. All rights reserved.
//

#include <iostream>
#include <stdio.h>
int max(int a, int b){
    if(a > b) return a;
    return b;
}
int main(int argc, const char * argv[]) {
    int a[101][10001], c[100], m[100], n, size, b[100], counter = 0;
    scanf("%d%d", &n, &size);
    for(int i = 0; i < n; ++i)
        scanf("%d", m+i);
    for(int i = 0; i < n; ++i)
        scanf("%d", c+i);
    for(int i = 0; i <= size; ++i) a[0][i] = 0;
    for(int i = 0; i <= n; ++i) a[i][0] = 0;
    for(int i = 1; i <= n; ++i){
        for(int j = 1; j <= size; ++j){
            a[i][j] = max(a[i-1][j], a[i][j-1]);
            if(j-m[i-1] >= 0) a[i][j] = max(a[i][j], a[i-1][j-m[i-1]] + c[i-1]);
        }
    }
    /*for(int i = 1; i <= n; ++i){
        for(int j = 1; j <= size; ++j) printf("%d ", a[i][j]);
        printf("\n");
    }*/
    int j = size;
    int i = n;
    while(i > 0 && j > 0){
        if(a[i][j] != a[i-1][j] && a[i][j] != a[i][j-1]){
            b[counter++] = i;
            j -= m[i-1];
            --i;
        }
        else if(a[i][j] == a[i-1][j])
            --i;
        else
            --j;
    }
    for(int i = counter-1; i >= 0; --i)
        printf("%d\n", b[i]);
    return 0;
}
/*
 4
 3
 1 2 3 4
 2 3 4 5*/