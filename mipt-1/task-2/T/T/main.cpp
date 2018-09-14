//
//  main.cpp
//  T
//
//  Created by Andrey Danilov on 02.12.15.
//  Copyright © 2015 Andrey Danilov. All rights reserved.
//
/*
10
1 3 4 2 10 5 6 8 9 7
10
10 5 6 8 9 7 1 3 4 2*/
#include <iostream>
#include <stdio.h>
int max(int a, int b){
    if(a > b) return a;
    return b;
}
int main(int argc, const char * argv[]) {
    int n1, n2, s1[1000], s2[1000], a[1001][1001];
    int b[1000], counter = 0;
    scanf("%d", &n1);
    for(int i = 0; i < n1; ++i)
        scanf("%d", s1+i);
    scanf("%d", &n2);
    for(int i = 0; i < n2; ++i)
        scanf("%d", s2+i);
    for(int i = 0; i <= n1; ++i) a[i][0] = 0;
    for(int j = 0; j <= n2; ++j) a[0][j] = 0;
    for(int i = 1; i <= n1; ++i){
        for(int j = 1; j <= n2; ++j){
            a[i][j] = max(a[i-1][j], a[i][j-1]);
            if(s1[i-1] == s2[j-1]) a[i][j] = max(a[i][j], a[i-1][j-1]+1);
        }
    }
    //for(int i = 1; i <= n1; ++i){
        //for(int j = 1; j <= n2; ++j) printf("%d ", a[i][j]);
        //printf("\n");
    //}
    int i = n1;
    int j = n2;
    while(i > 0 && j > 0){
        if(s1[i-1] == s2[j-1] && a[i-1][j-1]+1 >= a[i-1][j] && a[i-1][j-1]+1 >= a[i][j-1]){
            b[counter++] = s1[i-1];
            --i;
            --j;
        }
        else if(a[i-1][j] > a[i][j-1] || j <= 1) --i;
        else --j;
    }
    for(int i = counter-1; i >= 0; --i) printf("%d ", b[i]);
    return 0;
}



