//
//  Group.cpp
//  Group
//
//  Created by Andrey Danilov on 07.04.16.
//  Copyright © 2016 Andrey Danilov. All rights reserved.
//

#include "Group.hpp"

Student::Student(std::string name){
    this->name = name;
}

const std::string& Student::getName() const{
    return name;
}

void Student::mark(std::string subject, int value){
    marks[subject] = value;
}

bool Student::operator< (const Student &s) const{
    return this->name < s.name;
}

bool Student::operator== (const Student &s) const{
    return this->name == s.name;
}

void Group::addStudent(const Student& s){
    students.insert(s);
}

void Group::kickStudents(int k){
    std::vector<std::set<Student>::iterator> studentsToKick;
    for(auto &i : students){
        int x = 0;
        for(auto j : i.marks){
            if(j.second >= minMark)
                ++x;
        }
        if(x < k){
            studentsToKick.push_back(students.find(i));
        }
    }
    for(auto i : studentsToKick){
        students.erase(i);
    }
}

std::vector<std::string> Group::getLosers(std::string subject){
    std::vector<std::string> result;
    for(auto &i: students){
        if(i.marks.count(subject) && i.marks.at(subject) < minMark)
            result.push_back(i.name);
    }
    return result;
}

Student* Group::find(std::string name){
    std::set<Student>::iterator s = students.find(Student(name));
    if(s == students.end()) return nullptr;
    return const_cast<Student*>(&*s);;
}
