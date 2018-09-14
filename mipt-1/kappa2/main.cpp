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
    //srand(int(time(NULL)));
    int s1[500], s2[500];
    int a[500][500], b[500][500][2], n1, n2, x, y, max;
    int answer[500], counter = 0;
    int maxLine[500];
    scanf("%d", &n1);
    for(int i = 0; i < n1; ++i){
        //s1[i] = i%4 + 1;
        //s1[i] = rand()%100;
        scanf("%d", s1 + i);
        //printf("%d ", s1[i]);
    }
    //printf("\n");
    scanf("%d", &n2);
    for(int i = 0; i < n2; ++i){
        //s2[i] = i%4;
        //s2[i] = rand()%100;
        scanf("%d", s2 + i);
        //printf("%d ", s2[i]);
    }
    //s2[99] = s1[99] = 4;
    for(int j = 0; j < n2; ++j){
        maxLine[j] = -1;
    }
    for(int i = 0; i < n1; ++i){
        for(int j = 0; j < n2; ++j){
            if(s1[i] == s2[j]){
                max = 0;
                b[i][j][0] = -1;
                b[i][j][1] = -1;
                /*for(int x = 0; x < i; ++x){
                    if(c1[x] >= 0 && c1[x] < j && s1[x] < s1[i] && max < a[x][c1[x]]){
                        max = a[x][c1[x]];
                        b[i][j][0] = x;
                        b[i][j][1] = c1[x];
                    }
                }*/
                for(y = 0; y < j; ++y){
                    if(maxLine[y] >= 0 && s2[j] > s2[y] && max < a[maxLine[y]][y]){
                        max = a[maxLine[y]][y];
                        b[i][j][0] = maxLine[y];
                        b[i][j][1] = y;
                    }
                }
                a[i][j] = max + 1;
                //printf("b[%d][%d] = (%d, %d)\n", i, j, b[i][j][0], b[i][j][1]);
            }
            else{
                a[i][j] = 0;
                b[i][j][0] = -1;
                b[i][j][1] = -1;
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
            printf("%d ", a[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    for(int i = 0; i < n2; ++i){
        printf("%d\n", maxLine[i]);
    }
    printf("\n");
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
        //printf("x = %d y = %d\n", x, y);
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
/*
 10
 7 7 7 7 1 2 3 4 5 6
 10
 7 7 7 7 1 2 3 4 5 6
 
 10
 1 7 7 7 7 2 3 4 5 6
 10
 1 7 7 7 7 2 3 4 5 6
 */