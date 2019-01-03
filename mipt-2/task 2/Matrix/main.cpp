//
//  main.cpp
//  Matrix
//
//  Created by Andrey Danilov on 31.03.16.
//  Copyright © 2016 Andrey Danilov. All rights reserved.
//

#include <iostream>
#include "Matrix.cpp"
int main(int argc, const char * argv[]) {
    matrix<double> m;
    matrix<double> m2;
    std::cin >> m;
    m2 = power(m, 5);
    matrix<double> m3(m.reverse());
    matrix<double> m4(power(m3, 3));
    std::cout << m2*m4;
    m2.set_size(3, 2);
    m3.set_size(3, 2);
    m2 = {1, 0,
          0, 1,
          1, 0};
    m3 = {-2, 1,
          1, -2,
          -2, 1};
    std::cout << m2 + m3;
    return 0;
}
