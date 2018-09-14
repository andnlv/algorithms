//
//  main.cpp
//  Z
//
//  Created by Andrey Danilov on 03.12.15.
//  Copyright © 2015 Andrey Danilov. All rights reserved.
//

#include <iostream>
#include <stdio.h>
int main(int argc, const char * argv[]) {
    int a[18][18], n, m, i, j;
    scanf("%d", &n);
    scanf("%d", &m);
    for(i = 0; i < 18; ++i){
        a[i][0] = a[0][i] = 0;
        a[i][1] = a[1][i] = 0;
    }
    for(int i = 0; i < n+1; ++i) a[i][m+2] = 0;
    for(int i = 0; i < m+1; ++i) a[n+2][i] = 0;
    a[0][1] = 1;
    for(int k = 0; k < n + m-1; ++k){
        
        if(k < n){
            j = 2;
            i = k+2;
        }
        else{
            j = 3+k-n;
            i = n+1;
        }
        while(i > 1 && j < m+2){
            a[i][j] = a[i-2][j-1] + a[i-2][j+1] + a[i-1][j-2] + a[i+1][j-2];
            --i;
            ++j;
        }
    }
    printf("%d", a[n+1][m+1]);
    return 0;
}
