//
//  People.cpp
//  University
//
//  Created by Andrey Danilov on 21.03.16.
//  Copyright © 2016 Andrey Danilov. All rights reserved.
//

#include "People.hpp"

Man:: Man(unsigned int id){
    this-> id = id;
}

unsigned int Man:: getId() const{
    return id;
}

Profession Man:: occupation() const{
    return man;
}

Student:: Student(unsigned int id)
:Man(id)
{};

Profession Student:: occupation() const{
    return student;
}

Employee:: Employee(unsigned int id)
:Man(id)
{};

Profession Employee:: occupation() const{
    return employee;
}