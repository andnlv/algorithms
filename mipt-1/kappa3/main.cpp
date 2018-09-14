//
//  main.cpp
//  kappa
//
//  Created by Andrey Danilov on 08.12.15.
//  Copyright © 2015 Andrey Danilov. All rights reserved.
//

#include <iostream>
#include <stdio.h>
int main(int argc, const char * argv[]) {
    int s1[500], s2[500];
    int a[500][500], b[500][500][2], n1, n2, x, y, max;
    int answer[500], counter = 0;
    int maxLine[500];
    scanf("%d", &n1);
    for(int i = 0; i < n1; ++i)
        scanf("%d", s1 + i);
    scanf("%d", &n2);
    for(int i = 0; i < n2; ++i)
        scanf("%d", s2 + i);
    for(int j = 0; j < n2; ++j)
        maxLine[j] = -1;
    for(int i = 0; i < n1; ++i){
        for(int j = 0; j < n2; ++j){
            b[i][j][0] = -1;
            b[i][j][1] = -1;
            a[i][j] = 0;
            if(s1[i] == s2[j]){
                max = 0;
                for(y = 0; y < j; ++y){
                    if(maxLine[y] >= 0 && s2[j] > s2[y] && max < a[maxLine[y]][y]){
                        max = a[maxLine[y]][y];
                        b[i][j][0] = maxLine[y];
                        b[i][j][1] = y;
                    }
                }
                a[i][j] = max + 1;
            }
        }
        for(int j = 0; j < n2; ++j){
            if(maxLine[j] == -1 || a[maxLine[j]][j] < a[i][j])
                maxLine[j] = i;
        }
    }
    x = 0;
    y = 0;
    for(int i = 0; i < n1; ++i){
        for(int j = 0; j < n2; ++j){
            if(a[i][j] > a[x][y]){
                x = i;
                y = j;
            }
        }
    }
    if(s1[x] != s2[y]){
        printf("0");
        return 0;
    }
    while(true){
        if(x == -1 && y == -1) break;
        answer[counter++] = s1[x];
        int x0 = x;
        x = b[x0][y][0];
        y = b[x0][y][1];
    }
    printf("%d\n", counter);
    for(int i = counter-1; i >= 0; --i){
        printf("%d ", answer[i]);
    }
    return 0;
}
