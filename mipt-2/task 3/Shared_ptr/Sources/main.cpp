//
//  main.cpp
//  Shared_ptr
//
//  Created by Andrey Danilov on 28.04.16.
//  Copyright © 2016 Andrey Danilov. All rights reserved.
//
#include "Shared_ptr.cpp"
#include <vector>

using namespace std;
int main(int argc, const char * argv[]) {
    Shared_ptr<int> a(create_ptr<int>(10));
    Shared_ptr<vector<Shared_ptr<int>>> v(create_ptr<vector<Shared_ptr<int>>>());
    Shared_ptr<int> b(a);
    v.get()-> push_back(a);
    v->push_back(b);
    Shared_ptr<int> c;
    c = b;
    a = c;
    return 0;
}
