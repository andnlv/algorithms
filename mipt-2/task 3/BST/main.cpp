//
//  main.cpp
//  BST
//
//  Created by Andrey Danilov on 09.05.16.
//  Copyright © 2016 Andrey Danilov. All rights reserved.
//

#include "BST.hpp"
int main(int argc, const char * argv[]) {
    cout    << "i <number> - insert\n"
            << "e <number> - erase. 0 : not found, 1 : done\n"
            << "p - print all\n"
            << "f <number> - find the least element bigger then <number>\n"
            << "o - exit\n\n";
    BST<int> tree;
    int x;
    char c;
    while(true){
        cin >> c;
        if(c == 'o')
            return 0;
        if(c != 'p')
            cin >> x;
        if(c == 'i')
            tree.insert(x);
        if(c == 'e')
            cout << tree.erase(x) << "\n";
        if(c == 'f')
            cout << tree.find(x)->data << "\n";
        if(c == 'p')
            tree.print();
    }
}
