//
//  main.cpp
//  Shapes
//
//  Created by Andrey Danilov on 24.03.16.
//  Copyright © 2016 Andrey Danilov. All rights reserved.
//

#include <iostream>
#include "Shapes.hpp"
using namespace std;
int main(int argc, const char * argv[]) {
    cout.setf(ios_base::fixed);
    ConvexPolygon cp({Point(-1, -1), Point(1, 1), Point(0, 3), Point(-10, 0)});
    cout << "size " << cp.size() << "\n";
    
    Rectangle r({Point(0, 0), Point(4, 0), Point(4, 2), Point(0, 2)});
    cout << "crossings:\n";
    vector<Point> v = r.findCrossing(Segment(Point(-2, 2), Point(4, -1)));
    for(auto &i : v)
        cout << i.x << " " << i.y << "\n";
    Square s({Point(-1, -1), Point(1.5, -0.5), Point(1, 2), Point(-1.5, 1.5)});
    v = s.findCrossing(Segment(Point(0, 2), Point(0, -2)));
    for(auto &i : v)
        cout << i.x << " " << i.y << "\n";
    Circle c(Point(0, 0), 5);
    v = c.findCrossing(Segment(Point(0, 6), Point(1, -10)));
        for(auto &i : v)
            cout << i.x << " " << i.y << "\n";
    return 0;
}
