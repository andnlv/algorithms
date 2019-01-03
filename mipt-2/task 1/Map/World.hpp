//
//  World.hpp
//  Map
//
//  Created by Andrey Danilov on 19.03.16.
//  Copyright © 2016 Andrey Danilov. All rights reserved.
//

#ifndef World_hpp
#define World_hpp
#include <vector>
#include "GameObjects.hpp"
#include <iostream>

class World{
public:
    World(size_t width, size_t height);
    ~World();
    void show() const;
    void addObject(GameObject* newObject);
    void erase(size_t x, size_t y);
    void move(size_t x, size_t y, size_t newX, size_t newY);
    void dump() const;
private:
    void render();
    const size_t width, height;
    
    std::vector<GameObject *> objects;
    char* map;
    
    World(const World&) = delete;
    void operator= (const World&) = delete;
};



#endif /* World_hpp */
