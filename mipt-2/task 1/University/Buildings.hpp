//
//  Buildings.hpp
//  University
//
//  Created by Andrey Danilov on 21.03.16.
//  Copyright © 2016 Andrey Danilov. All rights reserved.
//

#ifndef Buildings_hpp
#define Buildings_hpp
#include <vector>
#include "People.hpp"

class Building{
public:
    virtual bool permisson(const Man *man);
};

class Laborаtory : public Building{
public:
    virtual bool permisson(const Man *man) override;
    void givePermission(const Man *man);
private:
    std::vector<unsigned int> permissionList;
};

class EducationBuilding : public Building{
public:
    virtual bool permisson(const Man *man) override;
};



#endif /* Buildings_hpp */
