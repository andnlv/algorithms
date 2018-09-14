//
//  main.cpp
//  kappa
//
//  Created by Andrey Danilov on 08.12.15.
//  Copyright © 2015 Andrey Danilov. All rights reserved.
//

#include <iostream>
#include <stdio.h>
void findPrev(int b[501][501], int &i, int &j){
    while(b[i][j] != 3 && i != 0 && j != 0){
        if(b[i][j] == 1) --j;
        else --i;
    }
}
int findMaxPrev(int a[501][501], int b[501][501], int i, int j){
    int max = 0;
    //printf("maxPrev %d %d\n", i, j);
    findPrev(b, i, j);
    while(i != 0 && j != 0){
        //printf("%d %d\n", i, j);
        if(a[i][j] > max) max = a[i][j];
        if(b[i][j] == 3){
            --i;
            --j;
        }
        findPrev(b, i, j);
    }
    return max;
}
int findMaxPrev2(int a[501][501], int b[501][501], int i, int j, int x, int s[500]){
    int max = 0;
    //printf("maxPrev %d %d\n", i, j);
    findPrev(b, i, j);
    while(i != 0 && j != 0){
        //printf("%d %d\n", i, j);
        if(x > s[i-1] && a[i][j] > max) max = a[i][j];
        if(b[i][j] == 3){
            --i;
            --j;
        }
        findPrev(b, i, j);
    }
    return max;
}
int main(int argc, const char * argv[]) {
    //srand(int(time(NULL)));
    int s1[500], s2[500];
    int a[501][501], b[501][501], n1, n2;
    int answer[500], counter = 0;
    scanf("%d", &n1);
    for(int i = 0; i < n1; ++i){
        //s1[i] = rand()%100;
        scanf("%d", s1 + i);
        //printf("%d ", s1[i]);
    }
    //printf("\n");
    scanf("%d", &n2);
    for(int i = 0; i < n2; ++i){
        //s2[i] = rand()%100;
        scanf("%d", s2 + i);
        //printf("%d ", s2[i]);
    }
    for(int i = 0; i <= n1; ++i){
        a[i][0] = 0;
        b[i][0] = 2;
    }
    for(int j = 1; j <= n2; ++j){
        a[0][j] = 0;
        b[0][j] = 1;
    }
    for(int i = 1; i <= n1; ++i){
        for(int j = 1; j <= n2; ++j){
            /*printf("i = %d, j = %d\n", i, j);
            for(int i = 1; i <= n1; ++i){
                for(int j = 1; j <= n2; ++j){
                    printf("%d ", a[i][j]);
                }
                printf("\n");
            }
            printf("\n");
            for(int i = 1; i <= n1; ++i){
                for(int j = 1; j <= n2; ++j){
                    printf("%d ", b[i][j]);
                }
                printf("\n");
            }*/
            int x1 = findMaxPrev(a, b, i-1, j);
            int x2 = findMaxPrev(a, b, i, j-1);
            if(x1 == x2){
                a[i][j] = x1;
                int p, q, x = i-1, y = j;
                findPrev(b, x, y);
                p = s1[x-1];
                x = i;
                y = j - 1;
                findPrev(b, x, y);
                q = s1[x-1];
                if(p < q)
                    b[i][j] = 2;
                else
                    b[i][j] = 1;
            }
            else if(x1 > x2){
                a[i][j] = x1;
                b[i][j] = 2;
            }
            else{
                a[i][j] = x2;
                b[i][j] = 1;
            }
            if(s1[i-1] == s2[j-1]){
                x1 = findMaxPrev2(a, b, i-1, j-1, s1[i-1], s1) + 1;
                if(x1  > a[i][j]){
                    b[i][j] = 3;
                    a[i][j] = x1;
                }
            }
        }
    }
    for(int i = 0; i <= n1; ++i){
        for(int j = 0; j <= n2; ++j){
            printf("%d ", a[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    for(int i = 0; i <= n1; ++i){
        for(int j = 0; j <= n2; ++j){
            printf("%d ", b[i][j]);
        }
        printf("\n");
    }
    printf("%d\n", a[n1][n2]);
    while(n1 != 0 && n2 != 0){
        if(b[n1][n2] == 3){
            answer[counter++] = s1[n1-1];
            --n1;
            --n2;
        }
        else if(b[n1][n2] == 2) --n1;
        else --n2;
    }
    for(int i = counter-1; i >= 0; --i){
        printf("%d ", answer[i]);
    }
    return 0;
}
/*
9
3
4
1
5
6
2
7
8
9
9
6
5
1
4
3
9
8
7
2
*/