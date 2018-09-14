#include <iostream>
#include <stdio.h>

int main1(int s1[500], int s2[500], int n1, int n2) {
    //int s1[500], s2[500];
    int a[500][500], b[500][500][2], x, y, max;
    int answer[500], counter = 0;
    int maxLine[500];
    for(int j = 0; j < n2; ++j){
        maxLine[j] = -1;
    }
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
        return 0;
    }
    while(true){
        if(x == -1 && y == -1) break;
        answer[counter++] = s1[x];
        int x0 = x;
        x = b[x0][y][0];
        y = b[x0][y][1];
    }
    return counter;
}

int main2(int s1[500], int s2[500], int n1, int n2) {
    //int s1[500], s2[500];
    int a[500][500], b[500][500][2], x, y, max;
    int answer[500], counter = 0;
    int c1[500];
    for(int i = 0; i < n1; ++i){
        c1[i] = -1;
        x = s1[i];
        y = 1;
        for(int j = 0; j < i; ++j){
            if(s1[j] == x) ++y;
        }
        for(int j = 0; j < n2 && y; ++j){
            if(s1[i] == s2[j]){
                c1[i] = j;
                --y;
            }
        }
    }
    for(int i = 0; i < n1; ++i){
        for(int j = 0; j < n2; ++j){
            b[i][j][0] = -1;
            b[i][j][1] = -1;
            a[i][j] = 0;
            if(s1[i] == s2[j]){
                max = 0;
                for(int x = 0; x < i; ++x){
                    for(int y = 0; y < j; ++y){
                        if(a[x][y] > max && s1[x] < s1[i]){
                            max = a[x][y];
                            b[i][j][0] = x;
                            b[i][j][1] = y;
                        }
                    }
                }
                /*for(int x = 0; x < i; ++x){
                    if(c1[x] > 0 && c1[x] < j && s1[x] < s1[i] && max < a[x][c1[x]]){
                        max = a[x][c1[x]];
                        b[i][j][0] = x;
                        b[i][j][1] = c1[x];
                    }
                }*/
                a[i][j] = max + 1;
            }
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
        return 0;
    }
    while(true){
        if(x == -1 && y == -1) break;
        answer[counter++] = s1[x];
        int x0 = x;
        x = b[x0][y][0];
        y = b[x0][y][1];
    }
    return counter;
}

int main(){
    srand(int(time(NULL)));
    int s1[500], s2[500], n1, n2, n, x1, x2;
    scanf("%d", &n);
    n1 = 100;
    n2 = 100;
    for(int i = 0; i < n; ++i){
        for(int i = 0; i < n1; ++i)
            s1[i] = rand()%4;
        for(int i = 0; i < n2; ++i)
            s2[i] = rand()%4;
        x1 = main1(s1, s2, n1, n2);
        x2 = main2(s1, s2, n1, n2);
        if(main1(s1, s2, n1, n2) != main2(s1, s2, n1, n2)){
            printf("%d\n", n1);
            for(int i = 0; i < n1; ++i)
                printf("%d ", s1[i]);
            printf("\n%d\n", n2);
            for(int i = 0; i < n2; ++i)
                printf("%d ", s2[i]);
            printf("\n");
            printf("%d %d\n\n", x1, x2);
        }
    }
}


