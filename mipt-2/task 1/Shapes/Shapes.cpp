//
//  Shapes.cpp
//  Shapes
//
//  Created by Andrey Danilov on 24.03.16.
//  Copyright © 2016 Andrey Danilov. All rights reserved.
//

#include "Shapes.hpp"
#include <iostream>
using namespace std;
//#include <assert.h>
void assert(bool a){
    if(!a) printf("Wrong input\n");
}
bool cmp(double a, double b){
    return a == b || fabs(a-b) < 10e-10;
}

Point::Point(double x, double y){
    this->x = x;
    this->y = y;
}

Segment::Segment(const Point &p1, const Point &p2)
: p1(p1), p2(p2) {};

Segment::Segment(double x, double y)
: p1(0, 0), p2(x, y) {};

double Segment::product(const Segment &s) const{
    return (p2.x - p1.x)*(s.p2.y - s.p1.y) - (p2.y - p1.y)*(s.p2.x - s.p1.x);
            
}

std::vector<Point> Segment::findCrossing(const Segment &s) const{
    
    std::vector<Point> result;
    double k1 = (cmp(p1.y, p2.y) ? 1E100 :(p1.x-p2.x)/(p1.y-p2.y));
    double k2 = (cmp(s.p1.y, s.p2.y) ? 1E100 : (s.p1.x-s.p2.x)/(s.p1.y-s.p2.y));
    if(cmp(k1, k2)){
        if(contain(s.p1))
            result.push_back(s.p1);
        if(contain(s.p2))
            result.push_back(s.p2);
        if (s.contain(p1))
            result.push_back(p1);
        if(s.contain(p2))
            result.push_back(p2);
    }
    else{
        Point p = Point((k2*p1.x + k1*k2*s.p1.y - k1*s.p1.x - k1*k2*p1.y)/(k2-k1), (k1*p1.y + s.p1.x - k2*s.p1.y - p1.x)/(k1-k2));
        if(contain(p) && s.contain(p))
        result.push_back(p);
    }
    return result;
}

bool Segment::contain(const Point &p) const{
    if(cmp(p1.y, p2.y)){
        return cmp(p.y, p1.y) && (p1.x - p.x)*(p2.x - p.x) <= 0;
    }
    return cmp((p1.x - p2.x)/(p1.y - p2.y), (p.x - p1.x)/(p.y - p1.y)) &&
       (p1.x - p.x)*(p2.x - p.x) <= 0 && (p1.y - p.y)*(p2.y - p.y) <= 0;
}

double Segment::length() const{
    return sqrt((p2.x - p1.x)*(p2.x - p1.x) + (p2.y - p1.y)*(p2.y - p1.y));
}

Circle:: Circle(const Point &p, double r)
: center(p), r(r){};

double Circle::size() const{
    return r*r*M_PI;
}

bool Circle::onSide(const Point &p) const{
    return cmp((center.x-p.x)*(center.x-p.x) + (center.y-p.y)*(center.y-p.y), r*r);
}

bool Circle::inside(const Point &p) const{
    return (center.x-p.x)*(center.x-p.x) + (center.y-p.y)*(center.y-p.y) <= r*r;
}

std::vector<Point> Circle::findCrossing(const Segment &s) const{
    std::vector<Point> result;
    double a = s.p2.y - s.p1.y;
    double b = s.p1.x - s.p2.x;
    double c = -s.p1.x*s.p2.y-s.p1.y*s.p2.x+center.x*(s.p1.y-s.p2.y)-center.y*(s.p1.x-s.p2.x);
    double x0 = a*c/(a*a+b*b);
    double y0 = b*c/(a*a+b*b);
    
    if(cmp((center.x-x0)*(center.x-x0)+(center.y-y0)*(center.y-y0), r*r)){
        if(s.contain(Point(center.x + x0, center.y + y0)))
            result.push_back(Point(center.x + x0, center.y + y0));
    }
    else if((center.x-x0)*(center.x-x0)+(center.y-y0)*(center.y-y0) < r*r){
        
        double d = sqrt(r*r/(a*a+b*b)-c*c/(a*a+b*b)/(a*a+b*b));
        double x1 = x0 + d*b;
        double x2 = x0 - d*b;
        double y1 = y0 - d*a;
        double y2 = y0 + d*a;
        if(s.contain(Point(x1, y1)))
           result.push_back(Point(x1, y1));
        if(s.contain(Point(x2, y2)))
            result.push_back(Point(x2, y2));
    }
    return result;
}

Polygon::Polygon(std::initializer_list<Point> list){
    
    for(const auto &p : list){
        bool correct = true;
        for(int i = 1; i+1 < tops.size(); ++i){
            cout << "1\n";
            Segment s1(tops[i], tops[i-1]), s2(*(tops.end()-1), p);
            correct = s1.findCrossing(s2).size() == 0;
        }
        assert(correct);
        tops.push_back(p);
    }
    
    bool correct = true;
    for(int i = 1; i+2 < tops.size(); ++i){
        correct = Segment(tops[i], tops[i+1]).findCrossing(Segment(*tops.begin(), tops.back())).size() == 0;
    }
    assert(correct);
    if(size() < 0)
        std::reverse(tops.begin(), tops.end());
};

double Polygon:: size() const{
    double size = 0;
    for(auto i = tops.begin()+1; i != tops.end(); ++i){
        size += Segment(i->x, i->y).product(Segment((i-1)->x, (i-1)->y));
    }
    size += Segment(tops.begin()->x, tops.begin()->y).product(Segment(tops.back().x, tops.back().y));
    return size/2;
}

bool Polygon::onSide(const Point &p) const{
    for (auto i = tops.begin()+1; i != tops.end(); ++i) {
        if(Segment(*(i-1), *i).contain(p))
            return true;
    }
    if (Segment(*tops.begin(), tops.back()).contain(p))
        return true;
    return false;
}

bool Polygon::inside(const Point &p) const{
    double angle = 0;
    for (auto i = tops.begin()+1; i != tops.end(); ++i) {
        angle += asin(Segment(p, *i).product(Segment(p, *(i-1)))/Segment(p, *i).length()/Segment(p, *(i-1)).length());
    }
    angle += asin(Segment(p, tops[0]).product(Segment(p, tops.back()))/Segment(p, tops[0]).length()/Segment(p, tops.back()).length());
    if(angle < 1)
        return false;
    else
        return true;
}

std::vector<Point> Polygon:: findCrossing(const Segment &s) const{
    std::vector<Point> result, r0;
    for(auto i = tops.begin()+1; i != tops.end(); ++i){
        r0 = s.findCrossing(Segment(*i, *(i-1)));
        if(r0.size() > 0){
            result.push_back(r0[0]);
        }
    }
    r0 = s.findCrossing(Segment(tops[0], tops.back()));
    if(r0.size() > 0) result.push_back(r0[0]);
    return result;
}

ConvexPolygon::ConvexPolygon(std::initializer_list<Point> list)
: Polygon(list) {
    Segment s1(*(tops.end()-2), *(tops.end()-1)), s2(*(tops.end()-1), tops[0]);
    bool correct = (s1.product(s2) < 0);
    if(correct) correct = Segment(*(tops.end()-1), tops[0]).product(Segment(tops[0], tops[1])) < 0;
    for(auto i = tops.begin()+2; i != tops.end() && correct; ++i){
        correct = (Segment(*(i-2), *(i-1)).product(Segment(*(i-1), *i)) < 0);
    }
    assert(correct);
}

Rectangle:: Rectangle(std::initializer_list<Point> list)
: ConvexPolygon(list){
    
    assert(tops.size() == 4);
    assert(cmp(Segment(tops[0], tops[1]).product(Segment(tops[0], tops[3])), -Segment(tops[0], tops[1]).length()*Segment(tops[0], tops[3]).length()));
    assert(cmp(Segment(tops[1], tops[2]).product(Segment(tops[1], tops[0])), -Segment(tops[1], tops[2]).length()*Segment(tops[1], tops[0]).length()));
    assert(cmp(Segment(tops[2], tops[3]).product(Segment(tops[2], tops[1])), -Segment(tops[2], tops[3]).length()*Segment(tops[2], tops[1]).length()));
};

Square:: Square(std::initializer_list<Point> list)
: Rectangle(list){
    assert(cmp(Segment(tops[0], tops[1]).length(),Segment(tops[0], tops[3]).length()));
}

Square:: Square(const Point &a, const Point &b)
: Rectangle({a, Point((a.x+b.x + b.y-a.y)/2, (a.y+b.y + a.x-b.x)/2), b, Point((a.x+b.x + a.y-b.y)/2, (a.y+b.y + b.x-a.x)/2)}){}

Triangle::Triangle(std::initializer_list<Point> list)
:ConvexPolygon(list){
    assert(tops.size() == 3);
    assert(size() != 0);
}





















