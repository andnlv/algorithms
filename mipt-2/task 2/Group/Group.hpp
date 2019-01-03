//
//  Group.hpp
//  Group
//
//  Created by Andrey Danilov on 07.04.16.
//  Copyright © 2016 Andrey Danilov. All rights reserved.
//

#ifndef Group_hpp
#define Group_hpp
#include <set>
#include <map>
#include <string>
#include <vector>

class Student{
private:
    std::map<std::string, int> marks;
    std::string name;
public:
    Student(std::string name);
    const std::string& getName() const;
    void mark(std::string subject, int value);
    bool operator< (const Student &s) const;
    bool operator== (const Student &s) const;
    friend class Group;
};

class Group{
private:
    std::set<Student> students;
    const static int minMark = 3;
public:
    void addStudent(const Student& s);
    void kickStudents(int k);
    std::vector<std::string> getLosers(std::string subject);
    Student* find(std::string);
};

#endif /* Group_hpp */
