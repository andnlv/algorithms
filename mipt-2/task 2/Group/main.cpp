//
//  main.cpp
//  Group
//
//  Created by Andrey Danilov on 07.04.16.
//  Copyright © 2016 Andrey Danilov. All rights reserved.
//

#include <iostream>
#include "Group.hpp"
int main(int argc, const char * argv[]) {
    Group g;
    g.addStudent(Student("Petrov Ivan"));
    g.addStudent(Student("Ivanov Petr"));
    g.addStudent(Student("Putin Vladimir"));
    g.find("Petrov Ivan")->mark("math", 4);
    g.find("Petrov Ivan")->mark("PE", 2);
    g.find("Petrov Ivan")->mark("coding", 5);
    g.find("Ivanov Petr")->mark("math", 5);
    g.find("Ivanov Petr")->mark("PE", 3);
    g.find("Ivanov Petr")->mark("coding", 3);
    g.find("Putin Vladimir")->mark("math", 2);
    g.find("Putin Vladimir")->mark("PE", 5);
    g.find("Putin Vladimir")->mark("coding", 2);
    g.kickStudents(2);
    std::vector<std::string> v = g.getLosers("PE");
    for(auto i : v)
        std::cout << i << "\n";
    return 0;
}
