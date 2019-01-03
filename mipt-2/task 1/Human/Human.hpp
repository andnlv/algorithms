//
//  Human.hpp
//  Human
//
//  Created by Andrey Danilov on 15.03.16.
//  Copyright © 2016 Andrey Danilov. All rights reserved.
//

#ifndef Human_hpp
#define Human_hpp
#include "string.h"

class Human{
protected:
    char    firstName[20],
            secondName[20];
public:
    virtual void getTitle(char *name) const = 0;
    Human(char* fName, char* sName);
};

class Mister : public Human{
public:
    void getTitle(char *name) const;
    Mister (char* fName, char* sName);
};

class Miss : Human{
public:
    void getTitle(char *name) const;
    Miss (char* fName, char* sName);
};

class Kid : Human{
public:
    void getTitle(char *name) const;
    Kid (char* fName, char* sName);
};


#endif /* Human_hpp */
