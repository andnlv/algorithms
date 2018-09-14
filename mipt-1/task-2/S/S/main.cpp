//
//  main.cpp
//  S
//
//  Created by Andrey Danilov on 02.12.15.
//  Copyright © 2015 Andrey Danilov. All rights reserved.
//

#include <iostream>
#include <stdio.h>
int max(int a, int b){
    if(a > b) return a;
    return b;
}
int main(int argc, const char * argv[]) {
    int a[101][101], n, m, d, counter = 0;
    int b[100];
    scanf("%d%d", &n, &m);
    for(int i = 0; i <= n; ++i){
        for(int j = 0; j <= m; ++j){
            if(i && j) scanf("%d", &d);
            else d = 0;
            a[i][j] = d;
        }
    }
    for(int i = 1; i <= n; ++i){
        for(int j = 1; j <= m; ++j){
            a[i][j] = max(a[i-1][j], a[i][j-1]) + a[i][j];
        }
    }
    int i = n;
    int j = m;
    while(i != 1 || j != 1){
        if(i == 1){
            b[counter++] = 0;
            --j;
        }
        else if(j == 1){
            b[counter++] = 1;
            --i;
        }
        else if(a[i-1][j] > a[i][j-1]){
            b[counter++] = 1;
            --i;
        }
        else{
            b[counter++] = 0;
            --j;
        }
    }
    printf("%d\n", a[n][m]);
    for(int i = counter - 1; i >= 0; --i){
        if(b[i]) printf("D ");
        else printf("R ");
    }
    return 0;
}

/*
 5 5
 10 1 1 1 1
 10 10 1 1 1
 1 10 10 10 1
 1 1 1 10 1
 1 1 1 10 10

*/


