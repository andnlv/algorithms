//
//  main.cpp
//  big_int
//
//  Created by Andrey Danilov on 05.03.16.
//  Copyright © 2016 Andrey Danilov. All rights reserved.
// 34563456

#include <iostream>
#include "Big_Int.hpp"
using namespace std;
int main(int argc, const char * argv[]) {
    BigInt a, b;
    cin >> a >> b;
    cout << a + b << "\n";
    cout <<a * b << "\n";
    cout <<a - b << "\n";
    cout <<a / b << "\n";
    cout <<a % b << "\n";
    return 0;
}
