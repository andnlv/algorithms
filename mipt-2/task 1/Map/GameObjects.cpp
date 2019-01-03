//
//  GameObjects.cpp
//  Map
//
//  Created by Andrey Danilov on 19.03.16.
//  Copyright © 2016 Andrey Danilov. All rights reserved.
//

#include "GameObjects.hpp"

GameObject:: GameObject(size_t x, size_t y, size_t size){
    this->x = x;
    this->y = y;
    this->size = size;
}

bool collide(GameObject *o1, GameObject *o2){
    
    return  ((o1->x <= o2->x && o1->x + o1->size-1 >= o2->x) ||
             (o2->x <= o1->x && o2->x + o2->size-1 >= o1->x)) &&
            ((o1->y <= o2->y && o1->y + o1->size-1 >= o2->y) ||
             (o2->y <= o1->y && o2->y + o2->size-1 >= o1->y));
}


Creature:: Creature(size_t x, size_t y, int hitPoints)
:GameObject(x, y, 1), hitPoints(hitPoints) {};

Hero:: Hero(size_t x, size_t y, int hitPoints, std::string name)
:Creature(x, y, hitPoints), name(name) {};

char Hero:: symbol() const{
    return name[0];
}

void Hero:: print() const{
    std::cout << "Hero " << name << " at " << x << ", " << y << " with " << hitPoints << "hp.\n";
}

Monster:: Monster(size_t x, size_t y, int hitPoints)
:Creature(x, y, hitPoints){};

char Monster:: symbol() const{
    return 'M';
}

void Monster:: print() const{
    std::cout << "Monster at " << x << ", " << y << " with " << hitPoints << "hp.\n";
}

Terrain:: Terrain(size_t x, size_t y, size_t size)
:GameObject(x, y, size){};

Lake:: Lake(size_t x, size_t y, size_t size, int depth)
:Terrain(x, y, size), depth(depth) {};

char Lake:: symbol() const{
    return 'O';
}

void Lake:: print() const{
    std::cout << "Lake at " << x << ", " << y << " with " << depth << "depth.\n";
}

Forest:: Forest(size_t x, size_t y, size_t size)
:Terrain(x, y, size) {};

char Forest:: symbol() const{
    return 'T';
}

void Forest:: print() const{
    std::cout << "Forest at " << x << ", " << y << ".\n";
}

Mountain:: Mountain(size_t x, size_t y, size_t size, int height)
:Terrain(x, y, size), height(height) {};

char Mountain:: symbol() const{
    return '^';
}

void Mountain:: print() const{
    std::cout << "Mountain at " << x << ", " << y << " with " << height << "height.\n";
}
