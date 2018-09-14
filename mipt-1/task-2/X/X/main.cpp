//
//  main.cpp
//  X
//
//  Created by Andrey Danilov on 03.12.15.
//  Copyright © 2015 Andrey Danilov. All rights reserved.
//

#include <iostream>
#include <stdio.h>
int main(int argc, const char * argv[]) {
    int a[12][37];
    int n, k;
    a[0][0] = 1;
    a[0][1] = 1;
    a[0][2] = 0;
    a[0][3] = 1;
    scanf("%d%d", &k, &n);
    for(int i = 4; i <= k; ++i) a[0][i] = 0;
    for(int i = 1; i < n; ++i){
        a[i][0] = a[i-1][0];
        a[i][1] = a[i-1][0] + a[i-1][1];
        a[i][2] = a[i-1][1] + a[i-1][2];
        for(int j = 3; j <= k; ++j)
            a[i][j] = a[i-1][j] + a[i-1][j-1] + a[i-1][j-3];
    }
    printf("%d", a[n-1][k]);
    return 0;
}
