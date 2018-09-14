//
//  main.cpp
//  J
//
//  Created by Andrey Danilov on 29.11.15.
//  Copyright © 2015 Andrey Danilov. All rights reserved.
//

#include <iostream>
#include <stdio.h>
int main(int argc, const char * argv[]) {
    char c;
    int l = 0;
    int a = 0;
    while(true){
        scanf("%c", &c);
        if(c == '\n') break;
        if(c == '(') ++l;
        else{
            if(l) --l;
            else ++a;
        }
    }
    printf("%d", a + l);
    return 0;
}
