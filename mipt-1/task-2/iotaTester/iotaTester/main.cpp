//
//  main.cpp
//  iotaTester
//
//  Created by Andrey Danilov on 06.12.15.
//  Copyright © 2015 Andrey Danilov. All rights reserved.
//

#include <iostream>
int** countLetters(char *s, int l){
    int **n = new int*[l+1];
    for(int i = 0; i <= l; ++i){
        n[i] = new int[26];
    }
    for(int i = 0; i <= l; ++i){
        for(int j = 0; j < 26; ++j){
            n[i][j] = 0;
        }
    }
    for(int i = 1; i <= l; ++i){
        n[i][int(s[i-1])-97] = 1;
    }
    for(int i = 1; i <= l; ++i){
        for(int j = 0; j < 26; ++j){
            n[i][j] += n[i-1][j];
        }
    }
    return n;
}
bool compare(int **n, int **n1, int **n2, int i1, int i2){
    bool f = 1;
    for(int j = 0; j < 26; ++j)
        if(n1[i1][j] + n2[i2][j] != n[i1+i2][j]) f = 0;
    return f;
}
using namespace std;
int f(char *s, char *s0, char *s1) {
    int a[501][501], b[501][501], l, l0, l1;
    int **n, **n0, **n1;
    //scanf("%s", s);
    //scanf("%s", s0);
    //scanf("%s", s1);
    for(l = 0; s[l]; ++l);
    for(l0 = 0; s0[l0]; ++l0);
    for(l1 = 0; s1[l1]; ++l1);
    n = countLetters(s, l);
    n0 = countLetters(s0, l0);
    n1 = countLetters(s1, l1);
    a[0][0] = 0;
    for(int j = 1; j <= l1; ++j){
        if(compare(n, n0, n1, 0, j) && a[0][j-1] != -1){
            a[0][j] = 0;
            b[0][j] = 1;
        }
        else a[0][j] = -1;
    }
    for(int i = 1; i <= l0; ++i){
        if(compare(n, n0, n1, i, 0) && a[i-1][0] != -1){
            a[i][0] = 0;
            b[i][0] = 2;
        }
        else a[i][0] = -1;
    }
    for(int i = 1; i <= l0; ++i){
        for(int j = 1; j <= l1; ++j){
            if(compare(n, n0, n1, i, j) && (a[i-1][j] != -1 || a[i][j-1] != -1)){
                int x1 = 1000, x2 = 1000;
                if(a[i-1][j] != -1){
                    if(b[i-1][j] == 2 || b[i-1][j] == 3)
                        x1 = a[i-1][j];
                    else
                        x1 = a[i-1][j] + 1;
                }
                if(a[i][j-1] != -1){
                    if(b[i][j-1] == 1 || b[i][j-1] == 3)
                        x2 = a[i][j-1];
                    else
                        x2 = a[i][j-1] + 1;
                }
                if(x1 < x2){
                    a[i][j] = x1;
                    b[i][j] = 2;
                }
                else if(x1 > x2){
                    a[i][j] = x2;
                    b[i][j] = 1;
                }
                else{
                    a[i][j] = x1;
                    b[i][j] = 3;
                }
            }
            else{
                a[i][j] = -1;
            }
        }
    }
    /*for(int i = 0; i <= l0; ++i){
     for(int j = 0; j <= l1; ++j)
     printf("%2d ", a[i][j]);
     printf("   ");
     for(int j = 0; j <= l1; ++j)
     printf("%2d ", b[i][j]);
     printf("\n");
     }*/
    for(int i = 0; i < l; ++i){
        delete [] n[i];
    }
    delete [] n;
    for(int i = 0; i < l0; ++i){
        delete [] n0[i];
    }
    delete [] n0;
    for(int i = 0; i < l1; ++i){
        delete [] n1[i];
    }
    delete [] n1;
    return a[l0][l1];
}

int main(int argc, const char * argv[]) {
    srand(int(time(NULL)));
    int r, answer, k = 0, q, l0 = 0, l1 = 0;
    char s[1001], s0[501], s1[501];
    scanf("%d", &r);
    for(int i = 0; i < r; ++i){
        printf("%d\n", i);
        l0 = 0, l1 = 0;
        answer = 0;
        for(int i = 0; i < 1000; ++i){
            q = rand()%2;
            k = (k + q)%2;
            answer += q;
            if((k || l1 == 500) && l0 != 500){
                s[l0+l1] = s0[l0] = char(rand()%2+99);
                ++l0;
            }
            else{
                s[l0+l1] = s1[l1] = char(rand()%2+97);
                ++l1;
            }
        }
        if(s[0] == s0[0]) -- answer;
        s[l0+l1] = '\0';
        s0[l0] = '\0';
        s1[l1] = '\0';
        f(s, s0, s1);
    }
    /*for(int i = 0; i < l0; ++i){
        printf("%c", s0[i]);
    }
    printf("\n");
    for(int i = 0; i < l1; ++i){
        printf("%c", s1[i]);
    }
    printf("\n");
    for(int i = 0; i < l0+l1; ++i){
        printf("%c", s[i]);
    }
    printf("\n\n");*/
    return 0;
}
