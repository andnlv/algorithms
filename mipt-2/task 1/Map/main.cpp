//
//  main.cpp
//  Map
//
//  Created by Andrey Danilov on 19.03.16.
//  Copyright © 2016 Andrey Danilov. All rights reserved.
//

#include <iostream>
#include "GameObjects.hpp"
#include "World.hpp"

using namespace std;
int main(int argc, const char * argv[]) {
    string command;
    World *map = nullptr;
    while(true){
        cout << "> ";
        cin >> command;
        switch (command[0]) {
            case 'm':
                if(command[1] == 'o' && map){
                    int x, y, newX, newY;
                    cin >> x >> y >> newX >> newY;
                    map->move(x, y, newX, newY);
                }
                else if(command[1] == 'a'){
                    delete map;
                    int x, y;
                    cin >> x >> y;
                    map = new World(x, y);
                }
                break;
            case 'q':
                delete map;
                cout << "Bye!\n";
                return 0;
            case 's':
                if(!map) break;
                map->show();
                break;
            case 'c':
                if(!map) break;
                cin >> command;
                if(command[0] == 'l'){
                    int x, y, depth, size;
                    cin >> command >> depth >> command >> x >> y >> command >> size;
                    GameObject *obj = new Lake(x, y, size, depth);
                    map->addObject(obj);
                }
                else if(command[0] == 'm' && command[2] == 'u'){
                    int x, y, height, size;
                    cin >> command >> height >> command >> x >> y >> command >> size;
                    GameObject *obj = new Mountain(x, y, size, height);
                    map->addObject(obj);
                }
                else if(command[0] == 'm' && command[2] == 'n'){
                    int x, y, hp;
                    cin >> command >> x >> y >> command >> hp;
                    GameObject *obj = new Monster(x, y, hp);
                    map->addObject(obj);
                }
                else if(command[0] == 'f'){
                    int x, y, size;
                    cin >> command >> x >> y >> command >> size;
                    GameObject *obj = new Forest(x, y, size);
                    map->addObject(obj);
                }
                else if(command[0] == 'h'){
                    int x, y, hp;
                    string name;
                    cin >> name >> command >> x >> y >> command >> hp;
                    GameObject *obj = new Hero(x, y, hp, name);
                    map->addObject(obj);
                }
                break;
            case 'd':
                if(!map) break;
                map->dump();
                break;
            case 'h':
                cout << "commands:\nmap (h) (w)\ncreate lake depth (d) at (x) (y) size (s)\ncreate mountain height (h) at (x) (y) size (s)\ncreate forest at (x) (y) size (s)\ncreate hero (name) at (x) (y) hp (hp)\ncreate monster at (x) (y) hp (hp)\nshow\ndump\nmove (x) (y) (newX) (newY)\nquit\n";
                break;
        }
    }
}
