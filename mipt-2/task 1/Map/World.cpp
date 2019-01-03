//
//  World.cpp
//  Map
//
//  Created by Andrey Danilov on 19.03.16.
//  Copyright © 2016 Andrey Danilov. All rights reserved.
//

#include "World.hpp"

World:: World(size_t width, size_t height)
: height(height), width(width)
{
    map = new char[height*(width*2+1)+1];
    for(int i = 0; i < height; ++i){
        for(int j = 0; j < width; ++j){
            map[width*2*i + i + 2*j] = '.';
            map[width*2*i + i + 2*j + 1] = ' ';
        }
        map[width*2*i + i + 2*width] = '\n';
    }
    map[height*(width*2+1)] = '\0';
}

World:: ~World(){
    delete [] map;
    for(int i = 0; i < objects.size(); ++i){
        delete objects[i];
    }
}

void World:: show() const{
    std::cout << map;
}

void World:: addObject(GameObject *newObject){
    for(int i = 0; i < objects.size(); ++i){
        if(collide(newObject, objects[i])){
            delete objects[i];
            objects.erase(objects.begin() + i);
        }
    }
    objects.push_back(newObject);
    render();
}

void World:: render(){
    for(int i = 0; i < height; ++i){
        for(int j = 0; j < width; ++j){
            map[width*2*i + i + 2*j] = '.';
            map[width*2*i + i + 2*j + 1] = ' ';
        }
        map[width*2*i + i + 2*width] = '\n';
    }
    map[height*(width*2+1)] = '\0';
    for(int it = 0; it < objects.size(); ++it){
        for(size_t i = objects[it]->x; i < objects[it]->x + objects[it]->size && i < height; ++i){
            for(size_t j = objects[it]->y; j < objects[it]->y + objects[it]->size && j < width; ++j)
                map[width*2*i + i + 2*j] = objects[it]->symbol();
        }
    }
}

void World:: erase(size_t x, size_t y){
    for(int i = 0; i < objects.size(); ++i){
        if(objects[i]->x == x && objects[i]-> y == y){
            delete objects[i];
            objects.erase(objects.begin()+i);
        }
    }
}

void World:: move(size_t x, size_t y, size_t newX, size_t newY){
    GameObject *o = 0;
    for(int i = 0; i < objects.size(); ++i){
        if(objects[i]->x == x && objects[i]-> y == y){
            o = objects[i];
            objects.erase(objects.begin()+i);
        }
    }
    if(!o) return;
    o->x = newX;
    o->y = newY;
    addObject(o);
}

void World:: dump() const{
    for(int i = 0; i < objects.size(); ++i){
        objects[i]->print();
    }
}







