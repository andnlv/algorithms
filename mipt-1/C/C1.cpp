//
//  C1.cpp
//  C
//
//  Created by Andrey Danilov on 26.11.15.
//  Copyright © 2015 Andrey Danilov. All rights reserved.
//

#include "C1.hpp"
int main(int argc, const char * argv[]) {
    Node *top[2], *min0 = 0, *min1 = 0;
    top[0] = top[1] = 0;
    int n, size = 0;
    char s[8];
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%s", s);
        switch (s[0]) {
            case 'e':
                int d;
                scanf("%d", &d);
                push(top, d, &min0);
                ++size;
                printf("ok\n");
                break;
            case 'd':
                if(!top[1]){
                    if(top[0]){
                        min1 = min0 = 0;
                        while(top[0])
                            push(top+1, pop(top), &min1);
                    }
                    else{
                        printf("error\n");
                        break;
                    }
                }
                printf("%d\n", pop(top+1, &min1));
                --size;
                break;
            case 'f':
                if(!top[1]){
                    if(top[0]){
                        min1 = min0 = 0;
                        while(top[0])
                            push(top+1, pop(top), &min1);
                    }
                    else{
                        printf("error\n");
                        break;
                    }
                }
                printf("%d\n", top[1]->d);
                break;
            case 'm':
                if(top[1] || top[0])
                    printf("%d\n", min0->d > min1->d ? min1->d : min0->d);
                else
                    printf("error\n");
                break;
            case 's':
                printf("%d\n", size);
                break;
            case 'c':
                clear(top+1, &min1);
                clear(top, &min0);
                printf("ok\n");
                size = 0;
                break;
        }
    }
