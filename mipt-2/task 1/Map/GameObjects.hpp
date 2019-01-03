//
//  GameObjects.hpp
//  Map
//
//  Created by Andrey Danilov on 19.03.16.
//  Copyright © 2016 Andrey Danilov. All rights reserved.
//

#ifndef GameObjects_hpp
#define GameObjects_hpp
#include <iostream>
#include <string>
#include <vector>

class GameObject{
public:
    GameObject(size_t x, size_t y, size_t size);
    virtual char symbol() const = 0;
    virtual void print() const = 0;
    virtual ~GameObject(){};
protected:
    size_t x, y, size;
    friend bool collide(GameObject *o1, GameObject *o2);
    friend class World;
};

class Creature : public GameObject{
public:
    Creature(size_t x, size_t y, int hitPoints);
    //virtual ~Creature() = 0;
protected:
    int hitPoints;
};

class Hero : public Creature{
public:
    Hero(size_t x, size_t y, int hitPoints, std::string name);
    virtual ~Hero() {};
    char symbol() const;
    void print() const;
protected:
    std::string name;
};

class Monster : public Creature{
public:
    Monster(size_t x, size_t y, int hitPoints);
    virtual ~Monster() {};
    char symbol() const;
    void print() const;
};

class Terrain : public GameObject{
public:
    Terrain(size_t x, size_t y, size_t size);
    //virtual ~Terrain() = 0;
};

class Lake : public Terrain{
public:
    Lake(size_t x, size_t y, size_t size, int depth);
    virtual ~Lake() {};
    char symbol() const;
    void print() const;
protected:
    int depth;
};

class Forest : public Terrain{
public:
    Forest(size_t x, size_t y, size_t size);
    virtual ~Forest() {};
    char symbol() const;
    void print() const;
};

class Mountain : public Terrain{
public:
    Mountain(size_t x, size_t y, size_t size, int heitht);
    virtual ~Mountain() {};
    char symbol() const;
    void print() const;
protected:
    int height;
};
#endif /* GameObjects_hpp */
