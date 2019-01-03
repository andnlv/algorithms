//
//  main.cpp
//  University
//
//  Created by Andrey Danilov on 21.03.16.
//  Copyright © 2016 Andrey Danilov. All rights reserved.
//

#include <iostream>
#include "Buildings.hpp"
#include "People.hpp"

int main(int argc, const char * argv[]) {
    std::vector<Man*> peopleList;
    Building b;
    Laborаtory l;
    EducationBuilding eb;
    Man *man;
    std:: cout << "           b l eb\n";
    for(int i = 0; i < 5; ++i){
        if(i%3 == 0){
            std::cout << "man       ";
            man = new Man(i);
        }
        else if(i%3 == 1){
            man = new Student(i);
            std::cout << "student   ";
            
        }
        else{
            std::cout << "employee  ";
            man = new Employee(i);
        }
        peopleList.push_back(man);
        if(i != 1)
            l.givePermission(man);
        std::cout << " " <<  b.permisson(man) <<" "<< l.permisson(man) <<" "<< eb.permisson(man)<< "\n";
    }
    for(auto x : peopleList)
        delete x;
    return 0;
}
