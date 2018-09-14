//
//  main.cpp
//  W
//
//  Created by Andrey Danilov on 03.12.15.
//  Copyright © 2015 Andrey Danilov. All rights reserved.
//

#include <iostream>
#include <stdio.h>
int main(int argc, const char * argv[]) {
    float a[500][3000], s;
    int q, n;
    a[0][0] = a[0][1] = a[0][2] = a[0][3] = a[0][4] = a[0][5] = 1./6;
    scanf("%d%d", &n, &q);
    if(n > q || n*6 < q){
        printf("0.000000");
        return 0;
    }
    for(int i = 1; i < n; ++i){
        for(int j = i; j < 6*i+6 && j < q; ++j){
            s = 0;
            for(int k = 1; k <= 6; ++k){
                if(j - k >= 0) s += a[i-1][j-k];
            }
            a[i][j] = s/6;
        }
    }
    printf("%f", a[n-1][q-1]);
    return 0;
}
