//
//  main.cpp
//  Human
//
//  Created by Andrey Danilov on 15.03.16.
//  Copyright © 2016 Andrey Danilov. All rights reserved.
//

#include <iostream>
#include "Human.hpp"

int main(int argc, const char * argv[]) {
    Mister father((char *) "Ivan",(char *) "Ivanov");
    Miss mother((char *) "Maria",(char *) "Ivanova");
    Kid son((char *) "Andrey",(char *) "Ivanov");
    char mumName[24], dadName[24], sonName[24];
    father.getTitle(dadName);
    mother.getTitle(mumName);
    son.getTitle(sonName);
    std::cout << dadName << ", " << mumName << " and " << sonName << " are a family\n";
    return 0;
}
