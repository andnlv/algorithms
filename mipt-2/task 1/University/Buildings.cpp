//
//  Buildings.cpp
//  University
//
//  Created by Andrey Danilov on 21.03.16.
//  Copyright © 2016 Andrey Danilov. All rights reserved.
//

#include "Buildings.hpp"

bool Building:: permisson(const Man *man){
    return true;
}

bool Laborаtory:: permisson(const Man *man){
    if(man->occupation() == employee)
        return true;
    if(man->occupation() == student){
        for(auto x : permissionList){
            if(x == man->getId())
                return true;
        }
    }
    return false;
}

void Laborаtory:: givePermission(const Man *man){
    if(man->occupation()== student){
        permissionList.push_back(man->getId());
    }
}

bool EducationBuilding:: permisson(const Man *man){
    if(man->occupation()== student || man->occupation()== employee)
        return true;
    return false;
}