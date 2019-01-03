//
//  People.hpp
//  University
//
//  Created by Andrey Danilov on 21.03.16.
//  Copyright © 2016 Andrey Danilov. All rights reserved.
//

#ifndef People_hpp
#define People_hpp
#include <string>

enum Profession {man, student, employee};

class Man{
protected:
    unsigned int id;
    std::string name;
public:
    Man(unsigned int id);
    unsigned int getId() const;
    virtual Profession occupation() const;
};

class Student : public Man{
public:
    Student(unsigned int id);
    static const int occupatin = student;
    virtual Profession occupation() const override;
};

class Employee : public Man{
public:
    Employee(unsigned int id);
    static const int occupatin = employee;
    virtual Profession occupation() const override;
};

#endif /* People_hpp */
