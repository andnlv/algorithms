//
//  main.cpp
//  Y
//
//  Created by Andrey Danilov on 03.12.15.
//  Copyright © 2015 Andrey Danilov. All rights reserved.
//
/*3 3 3
 1000000000 1000000000 1000000000
 1000000000 1000000000 999999998
 1000000000 1000000000 999999997
 */
#include <iostream>
#include <stdio.h>
int max(int a, int b){
    if(a > b) return a;
    return b;
}
int main() {
    unsigned int n1, n2, n3, *s1, *s2, *s3, ***a;
    int b[1000], counter = 0;
    scanf("%u", &n1);
    scanf("%u", &n2);
    scanf("%u", &n3);
    s1 = new unsigned int[n1];
    s2 = new unsigned int[n2];
    s3 = new unsigned int[n3];
    a = new unsigned int**[n1+1];
    for(int i = 0; i <= n1; ++i){
        a[i] = new unsigned int*[n2+1];
        for(int j = 0; j <= n2; ++j){
            a[i][j] = new unsigned int[n3+1];
        }
    }
    for(int i = 0; i < n1; ++i)
        scanf("%u", s1+i);
    for(int i = 0; i < n2; ++i)
        scanf("%u", s2+i);
    for(int i = 0; i < n3; ++i)
        scanf("%u", s3+i);
    for(int i = 0; i <= n1; ++i) a[i][0][0] = 0;
    for(int j = 0; j <= n2; ++j) a[0][j][0] = 0;
    for(int k = 0; k <= n3; ++k) a[0][0][k] = 0;
    for(int i = 1; i <= n1; ++i){
        for(int j = 1; j <= n2; ++j){
            for(int k = 1; k <= n3; ++k){
                a[i][j][k] = max(a[i-1][j][k], a[i][j-1][k]);
                a[i][j][k] = max(a[i][j][k], a[i][j][k-1]);
                if(s1[i-1] == s2[j-1] && s1[i-1] == s3[k-1]) a[i][j][k] = max(a[i][j][k], a[i-1][j-1][k-1]+1);
            }
        }
    }
    /*for(int i = 1; i <= n1; ++i){
        for(int j = 1; j <= n2; ++j){
            for(int k = 1; k <= n3; ++k)
                printf("%d ", a[i][j][k]);
            printf("\n");
        }
        printf("\n");
    }*/
    int i = n1;
    int j = n2;
    int k = n3;
    while(i > 0 && j > 0 && k > 0){
        //printf("%d %d %d\n", i, j, k);
        if(s1[i-1] == s2[j-1] && s1[i-1] == s3[k-1] && a[i-1][j-1][k-1]+1 >= a[i-1][j][k] && a[i-1][j-1][k-1]+1 >= a[i][j-1][k] && a[i-1][j-1][k-1]+1 >= a[i][j][k-1]){
            b[counter++] = s1[i-1];
            --i;
            --j;
            --k;
        }
        else if((a[i-1][j][k] >= a[i][j-1][k] && a[i-1][j][k] >= a[i][j][k-1]) || (j <= 1 && k <= 1)) --i;
        else if((a[i][j-1][k] >= a[i-1][j][k] && a[i][j-1][k] >= a[i][j][k-1]) || (i <= 1 && k <= 1)) --j;
        else --k;
    }
    printf("%u\n", counter);
    for(int i = counter-1; i >= 0; --i) printf("%u ", b[i]);
    for(int i = 0; i <= n1; ++i){
        for(int j = 0; j <= n2; ++j){
            delete [] a[i][j];
        }
        delete [] a[i];
    }
    delete [] a;
    delete [] s1;
    delete [] s2;
    delete [] s3;
    return 0;
}
