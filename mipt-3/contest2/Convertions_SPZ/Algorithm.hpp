//
//  Algorithm.hpp
//  Convertions_SPZ
//
//  Created by Andrey Danilov on 16.12.16.
//  Copyright © 2016 Andrey Danilov. All rights reserved.
//

#ifndef Algorithm_hpp
#define Algorithm_hpp

#include <iostream>
#include <vector>
#include <set>
#include <sstream>

// сами алгоритмы преобразований

std::vector<int> s_to_p(const std::string& s);

std::string p_to_s(const std::vector<int> &p);

std::vector<int> s_to_z(const std::string& s);

std::string z_to_s(const std::vector<int> &z);

std::vector<int> z_to_p(const std::vector<int>& z);

std::vector<int> p_to_z(const std::vector<int> &p);

// полные функции с вводом - выводом

void s_to_p();

void p_to_s();

void s_to_z();

void z_to_s();

void z_to_p();

void p_to_z();

#endif /* Algorithm_hpp */
