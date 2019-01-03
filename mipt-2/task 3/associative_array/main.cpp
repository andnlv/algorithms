//
//  main.cpp
//  associative_array
//
//  Created by Andrey Danilov on 17.05.16.
//  Copyright © 2016 Andrey Danilov. All rights reserved.
//

#include <iostream>
#include "HashTable1.hpp"
#include "HashTable2.hpp"
#include "HashTable3.hpp"
#include <algorithm>
#include <map>
using namespace HTWL;
//using namespace HTWOA;
//using namespace HTWС;
using namespace std;

int main(int argc, const char * argv[]) {
    HashTable<int, int> a;
    //string s;
    int s = 999999;
//    for(int i = 0; i < 1000; ++i)
//        s.push_back('a');
    size_t t2;
    size_t t = clock();
    //a.resize(4000000);
    for(int i = 0 ; i < 1000000; ++i){
        a[i] = s;
        //cout << i << "\n";
    }
    t2 = clock();
    cout << double(t2-t)/CLOCKS_PER_SEC << "\n";
    t = clock();
    map<int, int> b;
    for(int i = 0 ; i < 1000000; ++i){
        b[i] = s;
    }
    t2 = clock();
    cout << double(t2-t)/CLOCKS_PER_SEC << "\n";
    cout << a.size() << "\n";
    //a[2] = 32;
//    for(auto it = a.begin(); it != a.end(); ++it){
//                        cout << it->second << " ";
//                    }
//                    cout << "\n";
//    srand(int(time(NULL)));
//    HashTable<int, int> a;
//    
//    int command;
//    int key;
//    int value;
//    for(int i = 0; i < 10; ++i){
//        command = random()%4;
//        if(command == 0){
//            cout << "p: ";
//            for(auto it = a.end(); it != a.begin();){
//                --it;
//                cout << it->second << " ";
//            }
//            cout << "\n";
//            continue;
//        }
//        key = random()%10;
//        if(command == 1){
//            cout << "e: "<<key<<" "<<(a.erase(key) != a.end()) << "\n";
//            continue;
//        }
//        if(command == 2){
//            cout << "f: ";
//            cout << key;
//            cout << " ";
//            auto it = a.find(key);
//            if(it == a.end()){
//                cout << -1 << "\n";
//            }
//            else{
//                cout << a.find(key)->second << "\n";
//            }
//            continue;
//        }
//        value = random()%100;
//        if(command == 3){
//            cout << "i: " << key << " " << value << "\n";
//            a[key] = value;
//        }
//    }

    
//    char command;
//    int key;
//    int value;
//    while(true){
//        cin >> command;
//        if(command == 'q'){
//            return 0;
//        }
//        if(command == 'p'){
//            for(auto it = a.begin(); it != a.end(); ++it){
//                cout << it->second << " ";
//            }
//            cout << "\n";
//            continue;
//        }
//        cin >> key;
//        if(command == 'e'){
//            a.erase(key);
//            continue;
//        }
//        if(command == 'f'){
//            cout << a.find(key)->second;
//        }
//        cin >> value;
//        if(command == 'i'){
//            a[key] = value;
//        }
//    }
    return 0;
}
