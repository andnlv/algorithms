//
//  Shapes.hpp
//  Shapes
//
//  Created by Andrey Danilov on 24.03.16.
//  Copyright © 2016 Andrey Danilov. All rights reserved.
//

#ifndef Shapes_hpp
#define Shapes_hpp
#include <vector>
#include <initializer_list>
#include <math.h>
#include <algorithm>
struct Point{
    double x, y;
    Point(double x, double y);
};

class Segment{
private:
    const Point p1, p2;
public:
    Segment(const Point &p1, const Point &p2);
    Segment(double x, double y);
    double product(const Segment &s) const;
    std::vector<Point> findCrossing(const Segment &s) const;
    bool contain(const Point &p) const;
    double length() const;
    friend class Circle;
};

class Shape{
private:
    
public:
    virtual double size() const = 0;
    virtual bool onSide(const Point &p) const = 0;
    virtual bool inside(const Point &p) const = 0;
    std::vector<Point> findCrossing(const Segment &s) const;
};

class Circle : public Shape{
protected:
    Point center;
    double r;
public:
    Circle(const Point &p, double r);
    
    double size() const;
    bool onSide(const Point &p) const;
    bool inside(const Point &p) const;
    std::vector<Point> findCrossing(const Segment &s) const;};

class Polygon : public Shape{
protected:
    std::vector<Point> tops;
public:
    Polygon(std::initializer_list<Point> list);
    
    double size() const;
    bool onSide(const Point &p) const;
    bool inside(const Point &p) const;
    std::vector<Point> findCrossing(const Segment &s) const;};

class ConvexPolygon : public Polygon{
public:
    ConvexPolygon(std::initializer_list<Point> list);
};

class Rectangle : public ConvexPolygon{
public:
    Rectangle(std::initializer_list<Point> list);
};

class Square : public Rectangle{
public:
    Square(std::initializer_list<Point> list);
    Square(const Point &a, const Point &b);
};

class Triangle : public ConvexPolygon{
public:
    Triangle(std::initializer_list<Point>);
};

#endif /* Shapes_hpp */
