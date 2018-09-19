//
//  RandomTester.hpp
//  Aho-Corasik
//
//  Created by Andrey Danilov on 11.12.16.
//  Copyright © 2016 Andrey Danilov. All rights reserved.
//

#ifndef RandomTester_hpp
#define RandomTester_hpp

#include <vector>
#include <string>
#include <sstream>
#include "Algorithm.hpp"

using namespace std;

void randomTest(int n, int l1, int l2, int k, size_t randomSeed = random());

void check(stringstream &stream);

void compare(stringstream &stream);

void generate_random(stringstream& stream, int l1, int l2, int k, size_t seed = random());

string countAnswer(stringstream &stream);

#endif /* RandomTester_hpp */
