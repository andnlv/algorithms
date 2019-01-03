//
//  main.cpp
//  String
//
//  Created by Andrey Danilov on 10.03.16.
//  Copyright © 2016 Andrey Danilov. All rights reserved.
//

#include <iostream>
#include "String.hpp"
using namespace std;
int main(int argc, const char * argv[]) {
    String s1 = '0';
    s1 *= 10e6;
    cout << "Print something\n";
    cin >> s1;
    String s2 = "abcd";
    String s3 = '1' + s1 + "\n" + s2*2;
    cout << s3 << "\n";
    cout << s3.select(5, 3) + "\n";
    return 0;
}
