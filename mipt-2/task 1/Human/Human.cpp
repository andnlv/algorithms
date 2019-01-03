//
//  Human.cpp
//  Human
//
//  Created by Andrey Danilov on 15.03.16.
//  Copyright © 2016 Andrey Danilov. All rights reserved.
//

#include "Human.hpp"

Human::Human (char* fName, char* sName){
    strcpy(firstName, fName);
    strcpy(secondName, sName);
}

void Mister:: getTitle(char *name) const{
    name[0] = 'M'; name[1] = 'r'; name[2] = '.'; name[3] = ' ';
    strcpy(name+4, secondName);
}

Mister:: Mister(char* fName, char* sName)
: Human(fName, sName)
{};

void Miss:: getTitle(char *name) const{
    name[0] = 'M'; name[1] = 's'; name[2] = '.'; name[3] = ' ';
    strcpy(name+4, secondName);
};

Miss:: Miss(char* fName, char* sName)
: Human(fName, sName)
{};

void Kid:: getTitle(char *name) const{
    strcpy(name, firstName);
}

Kid:: Kid(char* fName, char* sName)
: Human(fName, sName)
{};